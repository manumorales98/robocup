#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <iostream>
#include "estructuras.h"

using namespace std;


// Obtiene los datos del jugador (dorsal y lado del campo) y del estado del partido y los guarda en una estructura de tipo Datos_Partido
Datos_Partido getPlayer (const string &mensaje, const string &equipo);

// Devuelve el mensaje para colocar al jugador que sea en su posicion en el momento del inicio del partido. 
// Se le pasa por parámetro la estructura del jugador.
string colocar_init (const Datos_Partido &datos);

// Devuelve una estructura de tipo balón con la distancia y direccion del balon respecto al jugador => "(see 655 ....  ((b) Distance Direction) .....)"
Ball check_ball (const string &mensaje, const Datos_Partido &datos);

// Devuelve una estructura de tipo Porteria con lo que ve el jugador  => "(see 655 ....  ((f g r b) 58 7) ((g r) 57.4 0) ((f g r t) 58 -7) ...)"
Porteria check_porteria (const string &mensaje, const Datos_Partido &datos);

// Devuelve True si el mensaje es de tipo see (lo que ve el jugador)
bool check_see (const string &mensaje);

// Comprueba si el mensaje see del jugador está viendo la bola. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_ball (const string &mensaje);

// Comprueba si el mensaje see del jugador está viendo la porteria. Si la ve, devuelve un true. Siempre le pasamos un mensaje de see como parametro.
bool check_see_porteria (const string &mensaje, const Datos_Partido &datos);

// Funcion que devuelve una string con el tipo de mensaje recibido
string check_message_type (const string &mensaje);

// Muestra los valores de los datos del partido por pantalla
void cout_datos (const Datos_Partido &datos);

// Actualiza el estado del partido cada vez que se recibe un mensaje de tipo "hear"
string check_estado (const string &mensaje);

// Funcion que mira cual es nuestro compañero mas cercano y lo guarda en datos
// Tambien guarda los datos de todos los jugadores que veo cerca con dorsal en la estructura Jugadores_Vistos de datos
Datos_Partido check_mas_cercano (const string &mensaje, Datos_Partido datos);

// Devuelve el mensaje para dar un pase al compañero de mayor dorsal de los que tenga cerca
string pase_cercano (const Datos_Partido &datos);

// Actualiza los flags que ve cada jugador al recibir un mensaje de tipo see
Datos_Partido check_flags (const Datos_Partido &datos, const string &mensaje);

// Comprueba si el jugador está en su zona de juego. Si lo está devuelve true, si no lo está, false
bool en_zona (const Datos_Partido &datos);

// Devuelve un true si soy el jugador más cercano al balón de los que veo y por lo tanto debo ser yo quien va al balón
bool voy_balon (const Datos_Partido & Datos);

// Devuelve un true si veo a un compañero con un dorsal mayor que el mio
bool veo_mayor (const Datos_Partido &datos);

#endif // FUNCIONES_H