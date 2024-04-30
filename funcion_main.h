#ifndef FUNCION_MAIN_H
#define FUNCION_MAIN_H

#include <vector>
#include <iostream>
#include "estructuras.h"
#include "funciones.h"


// Funcion que devuelve los datos del partido actualizados cuando se recibe un mensaje del servidor en el main. 
Datos_Partido funcion_main_recepcion (const string &mensaje, const Datos_Partido &datos);

// Funcion que según el estado del partido (viendo los datos) nos dice qué mensaje queremos enviar al servidor
string funcion_main_envio (const Datos_Partido &datos);





#endif