#include <vector>
#include <iostream>
#include "funciones_strings.h"

using namespace std;

// Función que utilizaremos para decodificar los mensajes que recibamos del servidor.
// Crea un vector que contiene una string para cada elemento entre un parentesis ( y ) de la string original
// Ejemplos: 
// "(hola)(que)(tal)" ---> {"hola", "que", "tal"}
// "hola(que)(tal)" -----> {"que", "tal"}
// "((hola)(que))(tal)" -> {"(hola)(que)", "tal"}  OJO!! En este caso como hay anidados convierte todo lo primero a una string y habría que usar con el primer elemento del vector de 
//                                                 nuevo la función separador para adquirir lo siguiente:  "(hola)(que)" -----> {"hola", "que"}
vector<string> separador (string const &frase){ 
    vector<string> resultado;
    int contador = 0;
    string palabra = "";
    
    for (unsigned int i = 0; i < frase.length(); i++){
        if (frase.at(i) == '('){
            contador ++;
        }
        if (frase.at(i) == ')'){
            contador --;
            if (contador == 0){
                palabra.resize(palabra.size()-1); // Para no añadir el ) al final de cada palabra
                resultado.push_back(palabra);
                palabra.clear();
            }
        }
        if (contador >= 1){
            palabra += frase.at(i+1);
        }
    }
    return resultado;
}



// Funcion que crea un vector de strings a partir de una string separándola por ' '
// Ejemplo:
// "Hola que tal" ---> {"Hola", "que", "tal"}
vector<string> vectorpalabras(string const &ejercicio){
  vector<string> resultado;
  string aux=ejercicio;

  int pos=aux.find(' ');
    if(pos!=-1)
      resultado.push_back(aux.substr(0,pos));


  for(int i=0;i<ejercicio.size();i++){
    if(ejercicio.at(i)==' '){
      aux=ejercicio.substr(i+1,ejercicio.size());
      pos=aux.find(' ');
      if(pos!=-1)
        resultado.push_back(aux.substr(0,pos));
    }
  }
  
  resultado.push_back(aux);
  return resultado;
}
