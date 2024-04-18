#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include "separador.h"
#include "colocar_init.h"

using namespace std;

string colocar_init (const string &primerMensaje){
    vector<string> aux = separador(primerMensaje); // {"init r 1 before_kick_off"}

    auto vectorDatos = vectorpalabras(aux.at(0)); // {"init", "r", "1", "before_kick_off"}

    string resultado;

    if (vectorDatos.at(1) == "r" && vectorDatos.at(2) == "1")
        resultado = "(move 51 0)";

    return resultado;

}
