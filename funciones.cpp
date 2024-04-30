#include <vector>
#include <iostream>
#include "funciones_strings.h"
#include "funciones.h"

using namespace std;


// Obtiene los datos del jugador (dorsal y lado del campo) y del estado del partido y los guarda en una estructura de tipo Datos_Partido
Datos_Partido getPlayer (const string &mensaje, const string &equipo){
    Datos_Partido datos;
    
    vector<string> aux = separador(mensaje); // {"init r 1 before_kick_off"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"init", "r", "1", "before_kick_off"}

    if (vectorDatos.at(0) != "init"){
        throw runtime_error ("Error: No se puede ejecutar getPlayer porque no es un mensaje init");
    }

    datos.jugador.lado_campo = vectorDatos.at(1);
    datos.jugador.dorsal = vectorDatos.at(2);
    datos.estado = vectorDatos.at(3);
    datos.jugador.equipo = equipo;

    return datos;
}



// Devuelve el mensaje para colocar al jugador que sea en su posicion en el momento del inicio del partido. 
// Se le pasa por parámetro la estructura del jugador.
string colocar_init (const Datos_Partido &datos){
    string resultado; // String que contendrá el mensaje que hay que enviar al server para colocar el jugador que sea

    // Ahora defino el string resultado con las coordenadas de cada uno de los 11 jugadores (se usa como referencia el campo izquierdo, coord. relativas)
    if (datos.jugador.dorsal == "1")
        resultado = "(move -51 0)"; // La coordenada del portero es la (-51,0) 
    else if (datos.jugador.dorsal == "2")
        resultado = "(move -35 -28)";
    else if (datos.jugador.dorsal == "3")
        resultado = "(move -42 -14)";
    else if (datos.jugador.dorsal == "4")
        resultado = "(move -42 14)";
    else if (datos.jugador.dorsal == "5")
        resultado = "(move -35 28)";
    else if (datos.jugador.dorsal == "6")
        resultado = "(move -30 11)";
    else if (datos.jugador.dorsal == "7")
        resultado = "(move -7 20)";
    else if (datos.jugador.dorsal == "8")
        resultado = "(move -30 -11)";
    else if (datos.jugador.dorsal == "9" && (datos.estado_anterior == "half_time" || datos.estado.find("goal_l") != -1)){ 
        if (datos.jugador.lado_campo == "r") 
            resultado = "(move -0.1 0)"; 
        else 
            resultado = "(move -10 0)";
    }
    else if (datos.jugador.dorsal == "9" && (datos.estado == "before_kick_off" || datos.estado.find("goal_r") != -1)){ 
        if (datos.jugador.lado_campo == "l") 
            resultado = "(move -0.1 0)"; 
        else 
            resultado = "(move -10 0)";
    }
    else if (datos.jugador.dorsal == "10")
        resultado = "(move -15 0)";
    else if (datos.jugador.dorsal == "11")
        resultado = "(move -7 -20)";
    else {
        throw runtime_error ("Error: No se puede ejecutar colocar_init porque el dorsal del jugador no es un dorsal válido: " + datos.jugador.dorsal);
    }

    return resultado; // Devuelvo mensaje que enviaré al servidor
}

// Actualiza el estado del partido cada vez que se recibe un mensaje de tipo "hear"
string check_estado (const string &mensaje){ // (hear 0 referee kick_off_l)
    vector<string> aux = separador(mensaje); // {"hear 0 referee kick_off_l"}
    auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "0", "referee", "kick_off_l"}

    if (vectorDatos.at(0) != "hear"){
        throw runtime_error ("Error: No se puede ejecutar check_estado porque el mensaje recibido no es de tipo hear");
    }

    return vectorDatos.at(3);
}


// Devuelve una estructura de tipo balón con la distancia y direccion del balon respecto al jugador => "(see 655 ....  ((b) Distance Direction) .....)"
Ball check_ball (const string &mensaje, const Datos_Partido &datos){ // "(see 655 ....  ((b) 95 46) .....)"
    Ball miBalon = datos.balon;

    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.at(0).find("see") == -1){
        throw runtime_error("Error: No se ha recibido por parametro en check_ball un mensaje de tipo see");
    }

    if (aux.size() == 1){ // Nos aseguramos de que es el mensaje que esperamos recibir
        aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
        for (int i = 0; i<aux.size(); i++){
            if (aux.at(i).find("(b)") != -1){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(b)", "95", "46"}
                miBalon.distancia = vectorDatos.at(1);
                miBalon.direccion = vectorDatos.at(2);
                return miBalon;
            }
        }
    }
    return miBalon;
} 


// Muestra los valores de los datos del partido por pantalla
void cout_datos (Datos_Partido const &datos){
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "DORSAL: " + datos.jugador.dorsal << endl;
    cout << "LADO: " + datos.jugador.lado_campo << endl;
    cout << "ESTADO: " + datos.estado << endl;
    cout << "DIRECCION BALON: " + datos.balon.direccion << endl;
    cout << "DISTANCIA BALON: " + datos.balon.distancia << endl;
    cout << "DIRECCION CENTRO PORTERIA: " + datos.porteria.direccion_centro_porteria << endl;
    cout << "DISTANCIA CENTRO PORTERIA: " +datos.porteria.distancia_centro_porteria << endl;
    cout << "DIRECCION PALO ARRIBA: " + datos.porteria.direccion_palo_arriba << endl;
    cout << "DISTANCIA PALO ARRIBA: " + datos.porteria.distancia_palo_arriba << endl;
    cout << "DIRECCION PALO ABAJO: " + datos.porteria.direccion_palo_abajo << endl;
    cout << "DISTANCIA PALO ABAJO: " + datos.porteria.distancia_palo_abajo << endl;
    cout << "DISTANCIA COMPAÑERO MAS CERCANO: " + datos.jugador_cercano.distancia << endl;
    cout << "DIRECCION COMPAÑERO MAS CERCANO: " + datos.jugador_cercano.direccion << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
}

// Funcion que devuelve una string con el tipo de mensaje recibido
string check_message_type (const string &mensaje){ // "(see 655 ....  ((b) 95 46) .....)"
    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    aux = vectorpalabras(aux.at(0)); // {"see", "655", .., "((b) 95 46)", ....."}

    return aux.at(0); // "see"

}

// Devuelve True si el mensaje es de tipo see (lo que ve el jugador)
bool check_see (const string &mensaje){ 
    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}
    if (aux.size() == 1 && (aux.at(0).find("see") != -1))
        return true;
    else 
        return false;
}

// Comprueba si el mensaje see del jugador está viendo la bola. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_ball (const string &mensaje){
    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.at(0).find("see") == -1){
        throw runtime_error("Error: No se ha recibido por parametro en check_see_ball un mensaje de tipo see");
    }

    aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
    
    for (int i = 0; i<aux.size(); i++){
        if (aux.at(i).find("(b)") != -1){ // Si encuentra la (b) es que estamos viendo el balon
            return true; // Devolvemos un true
        }
    }
    
    return false; // Si no la encontro devolvemos un false
}

// Comprueba si el mensaje see del jugador está viendo la porteria. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_porteria (const string &mensaje, const Datos_Partido &datos){
    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.at(0).find("see") == -1){
        throw runtime_error("Error: No se ha recibido por parametro en check_see_porteria un mensaje de tipo see");
    }

    aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
    
    for (int i = 0; i<aux.size(); i++){
        if (aux.at(i).find("(g r)") != -1 && datos.jugador.lado_campo == "l"){ // Si encuentra la porteria derecha y jugamos en la izquierda
            return true; // Devolvemos un true
        }

        if (aux.at(i).find("(g l)") != -1 && datos.jugador.lado_campo == "r"){ // Si encuentra la porteria izquierda y jugamos en la derecha
            return true; // Devolvemos un true
        }
    }
    
    return false; // Si no la encontro devolvemos un false
}



// Devuelve una estructura de tipo Porteria con lo que ve el jugador  => "(see 655 ....  ((f g r b) 58 7) ((g r) 57.4 0) ((f g r t) 58 -7) ...)"
Porteria check_porteria (const string &mensaje, const Datos_Partido &datos){ // "(see 655 ....  ((b) 95 46) .....)"
    Porteria miPorteria = datos.porteria;

    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.at(0).find("see") == -1){
        throw runtime_error("Error: No se ha recibido por parametro en check_ball un mensaje de tipo see");
    }

    if (aux.size() == 1 && (aux.at(0).find("see") != -1)){ // Nos aseguramos de que es el mensaje que esperamos recibir
        aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
        for (int i = 0; i<aux.size(); i++){
            if (aux.at(i).find("(f g r b)") != -1 && datos.jugador.lado_campo == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "r", "b)", "58", "7"}
                miPorteria.distancia_palo_abajo = vectorDatos.at(4);
                miPorteria.direccion_palo_abajo = vectorDatos.at(5);
            }
            if (aux.at(i).find("(g r)") != -1 && datos.jugador.lado_campo == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(g", "r)", "57.4", "0"}
                miPorteria.distancia_centro_porteria = vectorDatos.at(2);
                miPorteria.direccion_centro_porteria = vectorDatos.at(3);
            }
            if (aux.at(i).find("(f g r t)") != -1 && datos.jugador.lado_campo == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "r", "t)", "58", "-7"}
                miPorteria.distancia_palo_arriba = vectorDatos.at(4);
                miPorteria.direccion_palo_arriba = vectorDatos.at(5);
                return miPorteria;
            }

            // Lo mismo para la porteria izquierda
            if (aux.at(i).find("(f g l b)") != -1 && datos.jugador.lado_campo == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "l", "b)", "58", "7"}
                miPorteria.distancia_palo_abajo = vectorDatos.at(4);
                miPorteria.direccion_palo_abajo = vectorDatos.at(5);
            }
            if (aux.at(i).find("(g l)") != -1 && datos.jugador.lado_campo == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(g", "l)", "57.4", "0"}
                miPorteria.distancia_centro_porteria = vectorDatos.at(2);
                miPorteria.direccion_centro_porteria = vectorDatos.at(3);
            }
            if (aux.at(i).find("(f g l t)") != -1 && datos.jugador.lado_campo == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "l", "t)", "58", "-7"}
                miPorteria.distancia_palo_arriba = vectorDatos.at(4);
                miPorteria.direccion_palo_arriba = vectorDatos.at(5);
                return miPorteria;
            }
            
        }
    }
    return miPorteria;
} 


// Funcion que mira cual es nuestro compañero mas cercano y lo guarda en datos
Datos_Partido check_mas_cercano (const string &mensaje, Datos_Partido datos){ 
    //"(see 15 ... ((p "AstonBirras") 81.5 -15) ...)"
    //"(see 15 ... ((p "AstonBirras" 9) 33.1 -2 -0 0 158 158) ... )"
    //"(see 15 ... ((p "AstonBirras" 1 goalie) 11 2 -0 0 178 178) ... )"
    // {{15, -14}, {48, 24}, {14, -74}}
    vector<vector<string>> vector_posiciones_cercanos; // Vector donde guardamos vectores con distancia y direccion de los compañeros que vemos

    vector<string> aux = separador(mensaje); // {"see 15 ... ((p "AstonBirras" 1 goalie) 11 2 -0 0 178 178) ..."}
    aux = separador(aux.at(0)); // { ..., "(p "AstonBirras" 1 goalie) 11 2 -0 0 178 178)", ...}

    vector<string> vectorDatos;

    Datos_Partido resultado = datos;

    for (auto elem: aux){
        // Miramos si encontramos a algun compañero de nuestro equipo y los vamos guardando en el vector_posiciones_cercanos
        if (elem.find(datos.jugador.equipo) != -1){ // elem = "(p "AstonBirras" 1 goalie) 11 2 -0 0 178 178)"
            vectorDatos = vectorpalabras(elem); // vectorDatos = {"(p", "AstonBirras", "1", "goalie)", "11", "2", "-0", "0", "178", "178"}
            if (vectorDatos.size() == 4){ // {"(p", "AstonBirras)", "81.5", "-15"}
                vector_posiciones_cercanos.push_back({vectorDatos.at(2), vectorDatos.at(3)});
            }
            else if (vectorDatos.size() == 9) { // {"(p", "AstonBirras", "9)", "33.1", "-2", "-0", "0", "158", "158"}
                vector_posiciones_cercanos.push_back({vectorDatos.at(3), vectorDatos.at(4)});
            }
        }
    }

    // Ahora miramos si hemos guardado a compañeros en el vector_posiciones_cercanos, o si está vacio (no vemos a nadie de nuestro equipo)
    if (vector_posiciones_cercanos.size() == 0){ // Si no hemos visto a ningun compañero
        resultado.jugador_cercano.direccion = "-999";
        resultado.jugador_cercano.distancia = "-999";
        return resultado;
    }
    else { // Si hemos visto al menos a un compañero, recorremos sus posiciones y nos quedamos con la distancia y direccion al mas cercano
        string distanciaMin = vector_posiciones_cercanos.at(0).at(0); // Distancia al primer jugador que guardamos en el vector
        for (auto elem: vector_posiciones_cercanos){
            if (stof(elem.at(0)) <= stof(distanciaMin)){
                distanciaMin = elem.at(0);
                resultado.jugador_cercano.distancia = elem.at(0);
                resultado.jugador_cercano.direccion = elem.at(1);
            }
        }
        return resultado;
    }
}

// Devuelve el mensaje para dar un pase al compañero más cercano 
string pase_cercano (Datos_Partido datos){
    return ("(kick 20 " + datos.jugador_cercano.direccion + ")");
}




