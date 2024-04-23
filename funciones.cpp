#include <vector>
#include <iostream>
#include "strings.h"
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
        resultado = "(move -8 -20)";

    return resultado; // Devuelvo mensaje que enviaré al servidor
}




// Recoge los datos del servidor, los organiza y se lo envía a una función que los checkea y devuelve un True si se cumple el criterio de la función
bool recogerDatos (const string &mensaje, std::function<bool (vector<string> const&)> const & fLambdaCheck){
    vector<string> aux = separador(mensaje); // {"hear 0 referee kick_off_l"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "0", "referee", "kick_off_l"}

    return fLambdaCheck (vectorDatos);
}




  

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
}



// Comprueba si ha acabado la primera parte o el partido. Si acabó devuelve True, sino False.
/*bool check_stop (const string &mensaje){ // (hear 3000 referee half_time)
    vector<string> aux = separador(mensaje); // {"hear 3000 referee half_time"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"hear", "3000", "referee", "half_time"}

    if (vectorDatos )
    
}*/

