#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include "strings.h"
#include "colocar_init.h"

using namespace std;

// Coloca al jugador que sea en su posicion en el momento del inicio del partido. Se le pasa por parámetro el primer mensaje que responde el server.
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
