#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <iostream>
#include "estructuras.h"

using namespace std;


// Obtiene los datos del jugador (dorsal y lado del campo) y los guarda en una estructura de tipo Player
Player getPlayer (const string &mensaje);

// Coloca al jugador que sea en su posicion en el momento del inicio del partido. Se le pasa por parámetro el primer mensaje que responde el server.
//string colocar_init (const string &primerMensaje);

// Comprueba si ha comenzado el partido o la segunda parte. Si comenzó devuelve True, sino False.
//bool check_init (const string &mensaje);

// Recoge los datos del servidor, los organiza y se lo envía a una función que los checkea y devuelve un True si se cumple el criterio de la función
//bool recogerDatos (const string &mensaje, std::function<bool (vector<string> const&)> const & fLambdaCheck);

#endif // FUNCIONES_H