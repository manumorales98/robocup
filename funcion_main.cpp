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
    }


    if (tipo_mensaje == "see") { // Si el mensaje es de tipo see
        // Actualizamos los datos del jugador mas cercano que veamos de nuestro equipo
        resultado = check_mas_cercano(mensaje, resultado);

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
    if (datos.estado.find("goal") != -1 || datos.estado_anterior == "half_time"){
        resultado = colocar_init(datos); // Colocamos al jugador en su posicion inicial
        return resultado;
    }

    // Si estamos en el momento en que uno de los dos equipos tiene que sacar de medio y somos el 9 de ese equipo
    if ((datos.estado == "kick_off_l" && datos.jugador.dorsal == "9" && datos.jugador.lado_campo == "l") || 
        (datos.estado == "kick_off_r" && datos.jugador.dorsal == "9" && datos.jugador.lado_campo == "r")){ 
        if (datos.estado_anterior == "before_kick_off" || datos.estado_anterior == "half_time"){ // Si es principio de partido o segunda parte
            resultado = "(kick 33 180)"; // Sacamos hacia atras porque el balon lo tenemos delante y miramos hacia el 
        } else{ // Después de un gol el jugador está mirando hacia atras, entonces sacamos recto
            resultado = "(kick 45 0)"; 
        }
        return resultado;
    }

    // Si estamos viendo el balon, pero no estamos lo suficientemente orientados a el
    if (datos.balon.direccion != "-999" && (stof(datos.balon.direccion) < -15 || stof(datos.balon.direccion) > 15)){ 
        resultado = "(turn " + datos.balon.direccion + ")"; // Nos orientamos hacia el balón
        return resultado;
    }
    // Si no estamos viendo el balon
    if (datos.balon.direccion == "-999"){
        resultado = "(turn 80)"; // Giramos 80º respecto al cuerpo del jugador
        return resultado;
    }
    // Si vemos el balón y estamos ya orientados a el, no es necesario girar

    // Si el balón ya está en juego y ya estamos orientados hacia el balón
    if (datos.estado == "play_on"){
        // Si no estamos lo suficientemente cerca del balón como para chutar
        if (stof(datos.balon.distancia) >= 1 && datos.jugador.dorsal != "1") { 
            resultado = "(dash 100 0)"; // Corremos recto hacia el balón (porque ya nos hemos orientado antes)
            return resultado;
        }
        // Si somos el portero y tenemos el balon cerca
        if (datos.jugador.dorsal == "1" && stof(datos.balon.distancia) < 2){
            resultado = "(catch " + datos.balon.direccion + ")";
            return resultado;
        }
        // Si estamos cerca del balón y orientados de tal forma que vemos la porteria y la porteria esta cerca
        if (stof(datos.balon.distancia) < 1 && datos.porteria.direccion_centro_porteria != "-999" && stof(datos.porteria.distancia_centro_porteria) < 45){
            resultado = "(kick 100 " + datos.porteria.direccion_centro_porteria + ")"; // Tiramos a puerta a toda potencia
            return resultado;
        }

        // Si estamos cerca del balon y o bien no veo la porteria o bien la veo pero esta muy lejos
        if (stof(datos.balon.distancia) < 1 && (datos.porteria.direccion_centro_porteria == "-999" || stof(datos.porteria.distancia_centro_porteria) >= 45)){
            resultado = pase_cercano(datos);
            return resultado;
        }
               
        return resultado;
    }

    return resultado;
}







