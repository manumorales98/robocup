#ifndef FUNCIONES_STRINGS_H
#define FUNCIONES_STRINGS_H

#include <vector>
#include <iostream>

using namespace std;


// Función que utilizaremos para decodificar los mensajes que recibamos del servidor.
// Crea un vector que contiene una string para cada elemento entre un parentesis ( y ) de la string original
// Ejemplos: 
// "(hola)(que)(tal)" ---> {"hola", "que", "tal"}
// "hola(que)(tal)" -----> {"que", "tal"}
// "((hola)(que))(tal)" -> {"(hola)(que)", "tal"}  OJO!! En este caso como hay anidados convierte todo lo primero a una string y habría que usar con el primer elemento del vector de 
//                                                 nuevo la función separador para adquirir lo siguiente:  "(hola)(que)" -----> {"hola", "que"}
vector<string> separador (string const &frase);

// Funcion que crea un vector de strings a partir de una string separándola por ' '
// Ejemplo:
// "Hola que tal" ---> {"Hola", "que", "tal"}
vector<string> vectorpalabras(string const &ejercicio);

#endif