#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <vector>


using namespace std;

// Los valores -999 son valores irreales que se asignan al inicializar algunos campos para saber que no son valores reales todavía

// Representa al jugador
struct Player {
    Player (string input_dorsal = "", string input_lado_campo = "") : dorsal(input_dorsal), lado_campo(input_lado_campo) {}

    string dorsal = dorsal;
    string lado_campo = lado_campo;
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
    string input_direccion_palo_arriba = "-999", string input_distancia_palo_abajo = "-999", string input_direccion_palo_abajo = "-999",
    string input_lado_porteria = "-999"):
    distancia_centro_porteria (input_distancia_centro_porteria), direccion_centro_porteria (input_direccion_centro_porteria), 
    distancia_palo_arriba (input_distancia_palo_arriba), direccion_palo_arriba(input_direccion_palo_arriba),
    distancia_palo_abajo (input_distancia_palo_abajo), direccion_palo_abajo (input_direccion_palo_abajo), lado_porteria (input_lado_porteria) {}

    string distancia_centro_porteria;
    string direccion_centro_porteria;
    string distancia_palo_arriba;
    string direccion_palo_arriba;
    string distancia_palo_abajo;
    string direccion_palo_abajo;
    string lado_porteria; // Luego hay que asignarle "r" o "l" segun que porteria sea
};

#endif

