#!/bin/bash

# Nombre del ejecutable
EJECUTABLE="./player"

# Valor de texto que deseas pasar como parámetro al main
EquipoA="AstonBirras"
EquipoB="AstonBirrasB"

# Loop para abrir 10 terminales y ejecutar el ejecutable en cada una
for (( i=1; i<=11; i++ ))
do
    # Comando para abrir una nueva terminal y ejecutar el ejecutable con el valor de texto como parámetro
    gnome-terminal -- bash -c "$EJECUTABLE $EquipoA; exec bash"
    gnome-terminal -- bash -c "$EJECUTABLE $EquipoB; exec bash"
    
done
