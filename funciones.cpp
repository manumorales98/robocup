#include <vector>
#include <iostream>
<<<<<<< HEAD
#include "strings.h"
=======
#include "funciones_strings.h"
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
#include "funciones.h"

using namespace std;


// Obtiene los datos del jugador (dorsal y lado del campo) y los guarda en una estructura de tipo Player
Player getPlayer (const string &mensaje){
    Player miPlayer;
    
    vector<string> aux = separador(mensaje); // {"init r 1 before_kick_off"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"init", "r", "1", "before_kick_off"}

    miPlayer.lado_campo = vectorDatos.at(1);
    miPlayer.dorsal = vectorDatos.at(2);

    return miPlayer;
}



<<<<<<< HEAD


/*// Coloca al jugador que sea en su posicion en el momento del inicio del partido. Se le pasa por parámetro el primer mensaje que responde el server.
string colocar_init (const string &primerMensaje){
    vector<string> aux = separador(primerMensaje); // {"init r 1 before_kick_off"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"init", "r", "1", "before_kick_off"}

    string resultado; // String que contendrá el mensaje que hay que enviar al server para colocar el jugador que sea

    // Ahora defino el string resultado con las coordenadas de cada uno de los 11 jugadores (se usa como referencia el campo izquierdo, coord. relativas)
    if (vectorDatos.at(2) == "1")
        resultado = "(move -51 0)"; // La coordenada del portero es la (-51,0) 
    else if (vectorDatos.at(2) == "2")
        resultado = "(move -35 -28)";
    else if (vectorDatos.at(2) == "3")
        resultado = "(move -42 -14)";
    else if (vectorDatos.at(2) == "4")
        resultado = "(move -42 14)";
    else if (vectorDatos.at(2) == "5")
        resultado = "(move -35 28)";
    else if (vectorDatos.at(2) == "6")
        resultado = "(move -25 11)";
    else if (vectorDatos.at(2) == "7")
        resultado = "(move -8 20)";
    else if (vectorDatos.at(2) == "8")
        resultado = "(move -25 -11)";
    // Aunque los dos 9 tengan las mismas coordenadas, el del equipo que no saque empieza automáticamente mas atrás (debe estar fuera de la galleta)
    else if (vectorDatos.at(2) == "9")  
        resultado = "(move -5 0)"; 
    else if (vectorDatos.at(2) == "10")
        resultado = "(move -15 0)";
    else if (vectorDatos.at(2) == "11")
=======
// Devuelve el mensaje para colocar al jugador que sea en su posicion en el momento del inicio del partido. 
// Se le pasa por parámetro la estructura del jugador.
string colocar_init (const Player &miPlayer){
    string resultado; // String que contendrá el mensaje que hay que enviar al server para colocar el jugador que sea

    // Ahora defino el string resultado con las coordenadas de cada uno de los 11 jugadores (se usa como referencia el campo izquierdo, coord. relativas)
    if (miPlayer.dorsal == "1")
        resultado = "(move -51 0)"; // La coordenada del portero es la (-51,0) 
    else if (miPlayer.dorsal == "2")
        resultado = "(move -35 -28)";
    else if (miPlayer.dorsal == "3")
        resultado = "(move -42 -14)";
    else if (miPlayer.dorsal == "4")
        resultado = "(move -42 14)";
    else if (miPlayer.dorsal == "5")
        resultado = "(move -35 28)";
    else if (miPlayer.dorsal == "6")
        resultado = "(move -25 11)";
    else if (miPlayer.dorsal == "7")
        resultado = "(move -8 20)";
    else if (miPlayer.dorsal == "8")
        resultado = "(move -25 -11)";
    // Aunque los dos 9 tengan las mismas coordenadas, el del equipo que no saque empieza automáticamente mas atrás (debe estar fuera de la galleta)
    else if (miPlayer.dorsal == "9")  
        resultado = "(move -0.1 0)"; 
    else if (miPlayer.dorsal == "10")
        resultado = "(move -15 0)";
    else if (miPlayer.dorsal == "11")
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
        resultado = "(move -8 -20)";

    return resultado; // Devuelvo mensaje que enviaré al servidor
}

<<<<<<< HEAD



=======
// Comprueba si ha comenzado el partido  o la segunda parte. Si comenzó devuelve True, sino False.
bool check_init (const string &mensaje){ // (hear 0 referee kick_off_l)
    vector<string> aux = separador(mensaje); // {"hear 0 referee kick_off_l"}

    if (aux.size() == 1){ 
        auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "0", "referee", "kick_off_l"}
        if (vectorDatos.at(0) == "hear" && vectorDatos.size() == 4) {
            if (vectorDatos.at(2) == "referee" && (vectorDatos.at(3) == "kick_off_l" || vectorDatos.at(3) == "kick_off_r"))
                return true;
            else return false;
        }   
        else 
            return false;
    } 
    else 
        return false;
}


// Comprueba si ha acabado la primera parte o el partido. Si acabó devuelve True, sino False.
bool check_stop (const string &mensaje){ // (hear 3000 referee half_time)
    vector<string> aux = separador(mensaje); // {"hear 3000 referee half_time"}

    if (aux.size() == 1){ 
        auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "3000", "referee", "half_time"}
        if (vectorDatos.at(0) == "hear" && vectorDatos.size() == 4) {
            if (vectorDatos.at(2) == "referee" && (vectorDatos.at(3) == "half_time" || vectorDatos.at(3) == "time_over"))
                return true;
            else return false;
        }   
        else 
            return false;
    } 
    else 
        return false;
}


// Devuelve una estructura de tipo balón con la distancia y direccion del balon respecto al jugador => "(see 655 ....  ((b) Distance Direction) .....)"
Ball check_ball (const string &mensaje, const Ball &balon){ // "(see 655 ....  ((b) 95 46) .....)"
    Ball miBalon = balon;

    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.size() == 1 && (aux.at(0).find("see") != -1)){ // Nos aseguramos de que es el mensaje que esperamos recibir
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

// Orienta al jugador al inicio del partido para que empiece mirando al balon
string orientar_init (const Player &miPlayer){
    string mensaje;
    if (miPlayer.lado_campo == "r"){
        mensaje = ("(turn 180)");
    }

    if (miPlayer.lado_campo == "r" && miPlayer.dorsal == "11")
        mensaje = ("(turn -120)");

    if (miPlayer.lado_campo == "r" && miPlayer.dorsal == "7")
        mensaje = ("(turn 120)");

    if (miPlayer.lado_campo == "l" && miPlayer.dorsal == "11")
        mensaje = ("(turn 60)");

    if (miPlayer.lado_campo == "l" && miPlayer.dorsal == "7")
        mensaje = ("(turn -60)");

    return mensaje;
}

// Devuelve una estructura de tipo Porteria con lo que ve el jugador  => "(see 655 ....  ((f g r b) 58 7) ((g r) 57.4 0) ((f g r t) 58 -7) ...)"
Porteria check_porteria (const string &mensaje, const Porteria &porteria){ // "(see 655 ....  ((b) 95 46) .....)"
    Porteria miPorteria = porteria;

    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    if (aux.size() == 1 && (aux.at(0).find("see") != -1)){ // Nos aseguramos de que es el mensaje que esperamos recibir
        aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
        for (int i = 0; i<aux.size(); i++){
            if (aux.at(i).find("(f g r b)") != -1 && miPorteria.lado_porteria == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "r", "b)", "58", "7"}
                miPorteria.distancia_palo_abajo = vectorDatos.at(4);
                miPorteria.direccion_palo_abajo = vectorDatos.at(5);
            }
            if (aux.at(i).find("(g r)") != -1 && miPorteria.lado_porteria == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(g", "r)", "57.4", "0"}
                miPorteria.distancia_centro_porteria = vectorDatos.at(2);
                miPorteria.direccion_centro_porteria = vectorDatos.at(3);
            }
            if (aux.at(i).find("(f g r t)") != -1 && miPorteria.lado_porteria == "r"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "r", "t)", "58", "-7"}
                miPorteria.distancia_palo_arriba = vectorDatos.at(4);
                miPorteria.direccion_palo_arriba = vectorDatos.at(5);
                return miPorteria;
            }

            // Lo mismo para la porteria izquierda
            if (aux.at(i).find("(f g l b)") != -1 && miPorteria.lado_porteria == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "l", "b)", "58", "7"}
                miPorteria.distancia_palo_abajo = vectorDatos.at(4);
                miPorteria.direccion_palo_abajo = vectorDatos.at(5);
            }
            if (aux.at(i).find("(g l)") != -1 && miPorteria.lado_porteria == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(g", "l)", "57.4", "0"}
                miPorteria.distancia_centro_porteria = vectorDatos.at(2);
                miPorteria.direccion_centro_porteria = vectorDatos.at(3);
            }
            if (aux.at(i).find("(f g l t)") != -1 && miPorteria.lado_porteria == "l"){
                auto vectorDatos = vectorpalabras(aux.at(i));// {"(f", "g", "l", "t)", "58", "-7"}
                miPorteria.distancia_palo_arriba = vectorDatos.at(4);
                miPorteria.direccion_palo_arriba = vectorDatos.at(5);
                return miPorteria;
            }
            
        }
    }
    return miPorteria;
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

    aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
    
    for (int i = 0; i<aux.size(); i++){
        if (aux.at(i).find("(b)") != -1){ // Si encuentra la (b) es que estamos viendo el balon
            return true; // Devolvemos un true
        }
    }
    
    return false; // Si no la encontro devolvemos un false
}

// Comprueba si el mensaje see del jugador está viendo la porteria. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_porteria (const string &mensaje, const Player &jugador){
    vector<string> aux = separador(mensaje); // {"see 655 ....  ((b) 95 46) ....."}

    aux = separador(aux.at(0)); // {"...., "(b) 95 46", ....."}
    
    for (int i = 0; i<aux.size(); i++){
        if (aux.at(i).find("(g r)") != -1 && jugador.lado_campo == "l"){ // Si encuentra la porteria derecha y jugamos en la izquierda
            return true; // Devolvemos un true
        }

        if (aux.at(i).find("(g l)") != -1 && jugador.lado_campo == "r"){ // Si encuentra la porteria izquierda y jugamos en la derecha
            return true; // Devolvemos un true
        }
    }
    
    return false; // Si no la encontro devolvemos un false
}




/*
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
// Recoge los datos del servidor, los organiza y se lo envía a una función que los checkea y devuelve un True si se cumple el criterio de la función
bool recogerDatos (const string &mensaje, std::function<bool (vector<string> const&)> const & fLambdaCheck){
    vector<string> aux = separador(mensaje); // {"hear 0 referee kick_off_l"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "0", "referee", "kick_off_l"}

    return fLambdaCheck (vectorDatos);
<<<<<<< HEAD
}




  

=======
}*/


/*
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
// Comprueba si ha comenzado el partido  o la segunda parte. Si comenzó devuelve True, sino False.
bool check_init (const string &mensaje){ // (hear 0 referee kick_off_l)
    const auto fLambda = [] (const vector<string> &miVector) {
        if (miVector.size() == 4) {
            if (miVector.at(2) == "referee" && (miVector.at(3) == "kick_off_l" || miVector.at(3) == "kick_off_r"))
                return true;
        }   
        else 
            return false;
    };
    return recogerDatos(mensaje, fLambda); 
<<<<<<< HEAD
}



// Comprueba si ha acabado la primera parte o el partido. Si acabó devuelve True, sino False.
/*bool check_stop (const string &mensaje){ // (hear 3000 referee half_time)
=======
}*/



/*
// Comprueba si ha acabado la primera parte o el partido. Si acabó devuelve True, sino False.
bool check_stop (const string &mensaje){ // (hear 3000 referee half_time)
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
    vector<string> aux = separador(mensaje); // {"hear 3000 referee half_time"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "3000", "referee", "half_time"}

    if (vectorDatos )
    
<<<<<<< HEAD
}*/
=======
}

*/
>>>>>>> 9fad1ea (Tarea 2 (No chutan))

