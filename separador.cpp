#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include "separador.h"

using namespace std;


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