#include <vector>
#include <iostream>
#include "funcion_main.h"

using namespace std;


// Funcion que devuelve los datos del partido actualizados cuando se recibe un mensaje del servidor en el main. 
Datos_Partido funcion_main_recepcion (const string &mensaje, const Datos_Partido &datos){
    string tipo_mensaje = check_message_type (mensaje); // Comprobamos qué tipo de mensaje hemos recibido

    Datos_Partido resultado = datos; // Estructura que vamos a devolver

    if (tipo_mensaje == "hear"){ // Si es un mensaje sonoro
        resultado.estado_anterior = resultado.estado;
        resultado.estado = check_estado(mensaje);
        if (resultado.estado.find("goal_"+resultado.jugador.lado_campo) != -1) { // Si hemos marcado gol, tiramos hacia el palo contrario de la porteria
            resultado.dir_ultimo_tiro = -resultado.dir_ultimo_tiro;
        } 
    }


    if (tipo_mensaje == "see") { // Si el mensaje es de tipo see
        // Actualizamos los datos del jugador mas cercano que veamos de nuestro equipo
        resultado = check_mas_cercano(mensaje, resultado);

        // Actualizamos los datos de los 4 flags que ve el jugador (si no ve uno valdrá -999)
        resultado = check_flags (resultado, mensaje);

        if (check_see_ball(mensaje)){ // Si el jugador está viendo la bola
            resultado.balon = check_ball(mensaje, resultado); // Actualizamos posicion del balon respecto al jugador
        } 
        else { // Si el jugador no está viendo la bola => Valores a -999 que significa que no la vemos
            resultado.balon.direccion = "-999";
            resultado.balon.distancia = "-999";
        }
        if (check_see_porteria(mensaje, resultado)){ // Si el jugador está viendo la porteria rival
            resultado.porteria = check_porteria(mensaje, resultado); //Actualizamos posicion de la porteria rival respecto al jugador
        }  
        else { // Si el jugador no está viendo la porteria rival => Valores a -999 que significa que no la vemos
            resultado.porteria.distancia_centro_porteria= "-999";
            resultado.porteria.direccion_centro_porteria = "-999";
            resultado.porteria.distancia_palo_arriba = "-999";
            resultado.porteria.direccion_palo_arriba = "-999";
            resultado.porteria.distancia_palo_abajo = "-999";
            resultado.porteria.direccion_palo_abajo = "-999";

        }
    }

    return resultado;
}


// Funcion que según el estado del partido (viendo los datos) nos dice qué mensaje queremos enviar al servidor
string funcion_main_envio (const Datos_Partido &datos){
    string resultado;

    // Si hubo gol de algún equipo
    if (datos.estado.find("goal_l") != -1 || datos.estado.find("goal_r") != -1 || datos.estado_anterior == "half_time"){
        resultado = colocar_init(datos); // Colocamos al jugador en su posicion inicial
        return resultado;
    }

    // Si estamos en el momento en que uno de los dos equipos tiene que sacar de medio y somos el 9 de ese equipo
    if ((datos.estado == "kick_off_l" && datos.jugador.dorsal == "11" && datos.jugador.lado_campo == "l") || 
        (datos.estado == "kick_off_r" && datos.jugador.dorsal == "11" && datos.jugador.lado_campo == "r")){ 
        if (datos.estado_anterior == "before_kick_off" || datos.estado_anterior == "half_time"){ // Si es principio de partido o segunda parte
            resultado = "(kick 45 180)"; // Sacamos hacia atras porque el balon lo tenemos delante y miramos hacia el 
        } else{ // Después de un gol el jugador está mirando hacia atras, entonces sacamos recto
            resultado = "(kick 60 0)"; 
        }
        return resultado;
    }

    // Si estamos viendo el balon, pero no estamos lo suficientemente orientados a el
    /*if (datos.balon.direccion != "-999" && (stof(datos.balon.direccion) < -15 || stof(datos.balon.direccion) > 15)){ 
        resultado = "(turn " + datos.balon.direccion + ")"; // Nos orientamos hacia el balón
        return resultado;
    }*/
    // Si no estamos viendo el balon
    if (datos.balon.direccion == "-999"){
        resultado = "(turn 80)"; // Giramos 80º respecto al cuerpo del jugador
        return resultado;
    }
    // Si vemos el balón y estamos ya orientados a el, no es necesario girar

    // Si hay un tiro libre y el portero tiene el balon (su distancia a el es muy baja), será porque es saque de puerta o porque lo agarro, entonces
    // hacemos un despeje a campo contrario
    if (datos.estado.find("free_kick_") != -1 && datos.jugador.dorsal == "1" && stod(datos.balon.distancia) < 1){
        resultado = "(kick 100 " + datos.porteria.direccion_centro_porteria + ")";
        return resultado;
    }

    // Si el balón ya está en juego y ya estamos orientados hacia el balón, o si hay un saque de banda para nuestro equipo o un corner o falta o penalti
    if (datos.estado == "play_on" || 
       (datos.estado == "kick_in_l" && datos.jugador.lado_campo =="l") || (datos.estado == "kick_in_r" && datos.jugador.lado_campo =="r") ||
       (datos.estado == "corner_kick_l" && datos.jugador.lado_campo =="l") || (datos.estado == "corner_kick_r" && datos.jugador.lado_campo =="r") ||
       (datos.estado == "free_kick_l" && datos.jugador.lado_campo =="l") || (datos.estado == "free_kick_r" && datos.jugador.lado_campo =="r") ||
       (datos.estado == "penalty_kick_l" && datos.jugador.lado_campo =="l") || (datos.estado == "penalty_kick_r" && datos.jugador.lado_campo =="r")){
        // Comprobamos si el jugador está en su zona de juego
        if (en_zona(datos)){

            // Si no estamos lo suficientemente cerca del balón como para chutar y somos quien tiene que ir a por el balon
            if (stof(datos.balon.distancia) >= 1 && stof(datos.balon.distancia) < 25 && voy_balon(datos)) { 
                resultado = "(dash 100 "+datos.balon.direccion+")"; // Corremos recto hacia el balón (porque ya nos hemos orientado antes)
                return resultado;
            }
            // Si no estamos lo suficientemente cerca del balón como para chutar y estamos a una distancia muy lejana del balon
            if (stof(datos.balon.distancia) >= 45 && datos.jugador.dorsal != "1") { 
                resultado = "(dash 100 "+datos.balon.direccion+")"; // Corremos recto hacia el balón para adelantar lineas (porque ya nos hemos orientado antes)
                return resultado;
            }

            // Si somos el portero estaremos siempre quietos en el centro de la porteria salvo cuando el balon este muy cerca 
            if (datos.jugador.dorsal == "1" && stof(datos.balon.distancia) < 5 && stof(datos.balon.distancia) > 1){
                resultado = "(dash 100 "+datos.balon.direccion+")"; // Corremos recto hacia el balón para adelantar lineas (porque ya nos hemos orientado antes)
                return resultado;
            }

        }
        // Si no está en su zona de juego
        else {
            resultado = "(dash 100 180)"; // Corremos 180º hacia atras para volver a nuestra zona
            return resultado;
        }
        
        // Si somos el portero y tenemos el balon cerca
        if (datos.jugador.dorsal == "1" && stof(datos.balon.distancia) < 1){
            resultado = "(catch " + datos.balon.direccion + ")";
            return resultado;
        }
        // Si estamos cerca del balón y orientados de tal forma que vemos la porteria y la porteria esta cerca
        if (stof(datos.balon.distancia) < 1 && datos.porteria.direccion_centro_porteria != "-999" && stof(datos.porteria.distancia_centro_porteria) < 35){
            resultado = "(kick 100 " + to_string(stof(datos.porteria.direccion_centro_porteria)+datos.dir_ultimo_tiro) + ")"; // Tiramos a puerta a toda potencia
            return resultado;
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Si estamos cerca del balon y veo un numero mas grande que yo -> se la paso

        // Si estamos cerca del balon y no veo un numero mas grande que yo, pero veo la porteria contraria -> corro hacia la porteria contraria

        // Si estamos cerca del balon y no veo un numero mas grande que yo y tampoco la porteria contraria -> se la paso al de mayor numero que vea

        // Si estamos cerca del balon y no veo a nadie, pero veo la porteria contraria -> corro hacia la porteria contraria

        // Si estamos cerca del balon y no veo a nadie y tampoco la porteria contraria -> (kick 70 180) pase hacia atras

        if (stof(datos.balon.distancia) < 1){ // Si estamos cerca del balon
            if (veo_mayor(datos)){ // Si veo un numero mas grande que yo
                resultado = pase_cercano(datos); // Se la paso al mayor 
                return resultado;
            }
            else { // Si no veo un numero mas grande que yo (o no veo a nadie)
                if (datos.porteria.distancia_centro_porteria != "-999"){ // Si veo la porteria contraria
                    resultado = "(kick 25 " + datos.porteria.direccion_centro_porteria + ")"; // Conduzco hacia la porteria contraria
                    return resultado;

                }
                else{ // Si no veo la porteria contraria
                    resultado = pase_cercano(datos); // Se la paso a quien vea de mayor numero o giro hasta ver la porteria contraria
                    return resultado;
                }

            }
        }

    }

    return resultado;
}







