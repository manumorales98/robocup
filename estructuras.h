#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <vector>


using namespace std;

// Los valores -999 son valores que interpretamos como que no estamos viendo algo

// Representa al jugador
struct Player {
    Player (string input_dorsal = "", string input_lado_campo = "", string input_equipo = "") : 
    dorsal(input_dorsal), lado_campo(input_lado_campo), equipo(input_equipo) {}

    string dorsal = dorsal;
    string lado_campo = lado_campo;
    string equipo = equipo;
};

// Representa al balon
struct Ball {
    Ball (string input_distancia = "-999", string input_direccion = "-999") : distancia(input_distancia), direccion(input_direccion) {}

    string distancia = distancia; // Distancia del balon respecto al cuerpo del jugador teniendo en cuenta la cabeza
    string direccion = direccion; // Direccion (grados) del balon del balon respecto al cuerpo del jugador teniendo en cuenta la cabeza
};

// Representa una porteria
struct Porteria{
    Porteria (string input_distancia_centro_porteria = "-999", string input_direccion_centro_porteria = "-999", string input_distancia_palo_arriba = "-999",
    string input_direccion_palo_arriba = "-999", string input_distancia_palo_abajo = "-999", string input_direccion_palo_abajo = "-999"):
    distancia_centro_porteria (input_distancia_centro_porteria), direccion_centro_porteria (input_direccion_centro_porteria), 
    distancia_palo_arriba (input_distancia_palo_arriba), direccion_palo_arriba(input_direccion_palo_arriba),
    distancia_palo_abajo (input_distancia_palo_abajo), direccion_palo_abajo (input_direccion_palo_abajo) {}

    string distancia_centro_porteria;
    string direccion_centro_porteria;
    string distancia_palo_arriba;
    string direccion_palo_arriba;
    string distancia_palo_abajo;
    string direccion_palo_abajo;
};

// Representa al compañero de nuestro equipo mas cercano a nosotros
struct Jugador_Cercano{
    Jugador_Cercano (string input_distancia = "-999", string input_direccion = "-999") : distancia(input_distancia), direccion(input_direccion) {}
    string distancia; // Distancia de nuestro compañero mas cercano respecto a nosotros
    string direccion; // Direccion de nuestri compañero mas cercano respecto a nosotros
};


// Estructura con los datos generales del partido
struct Datos_Partido{
    Player jugador;
    Porteria porteria;
    Ball balon;
    string estado; // Estado del partido en el momento actual ("before_kick_off", "kick_off_l", "play_on", "half_time", "kick_off_r", "play_on", "time_over")
    // Si hay goles estado = "goal_l_3" si por ejemplo el equipo l metio el 3er gol. Despues pasaria a valer "kick_off_r".
    // Si el equipo izquierdo hace falta: estado = "free_kick_fault_l". Despues pasaria a valer "free_kick_r" y el derecho tendria que sacar
    // Cuando la coge el portero recibimos un mensaje "(hear 593 referee goalie_catch_ball_l)" y despues un "(hear 593 referee free_kick_l)"
    // En el estado de free_kick hay que sacar. Sino saca solo y en ese momento el estado es (hear 1035 referee drop_ball)
    // y finamente volvemos a play_on
    string estado_anterior; // Estado anterior al actual
    Jugador_Cercano jugador_cercano; 
};



#endif

