#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <iostream>
#include "estructuras.h"

using namespace std;


// Obtiene los datos del jugador (dorsal y lado del campo) y los guarda en una estructura de tipo Player
Player getPlayer (const string &mensaje);

// Devuelve el mensaje para colocar al jugador que sea en su posicion en el momento del inicio del partido. 
// Se le pasa por parámetro la estructura del jugador.
string colocar_init (const Player &miPlayer);

// Comprueba si ha comenzado el partido o la segunda parte. Si comenzó devuelve True, sino False.
bool check_init (const string &mensaje);

// Comprueba si ha acabado la primera parte o el partido. Si acabó devuelve True, sino False.
bool check_stop (const string &mensaje);

// Devuelve una estructura de tipo balón con la distancia y direccion del balon respecto al jugador => "(see 655 ....  ((b) Distance Direction) .....)"
Ball check_ball (const string &mensaje, const Ball &balon);

// Orienta al jugador al inicio del partido para que empiece mirando al balon
string orientar_init (const Player &miPlayer);

// Devuelve una estructura de tipo Porteria con lo que ve el jugador  => "(see 655 ....  ((f g r b) 58 7) ((g r) 57.4 0) ((f g r t) 58 -7) ...)"
Porteria check_porteria (const string &mensaje, const Porteria &porteria);

// Devuelve True si el mensaje es de tipo see (lo que ve el jugador)
bool check_see (const string &mensaje);

// Comprueba si el mensaje see del jugador está viendo la bola. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_ball (const string &mensaje);

// Comprueba si el mensaje see del jugador está viendo la porteria. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_porteria (const string &mensaje, const Player &jugador);

// Recoge los datos del servidor, los organiza y se lo envía a una función que los checkea y devuelve un True si se cumple el criterio de la función
//bool recogerDatos (const string &mensaje, std::function<bool (vector<string> const&)> const & fLambdaCheck);

#endif // FUNCIONES_H
