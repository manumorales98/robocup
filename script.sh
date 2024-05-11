#!/bin/bash

# Nombre del ejecutable
EJECUTABLE="./player"

# Valor de texto que deseas pasar como parámetro al main
EquipoA="AstonBirras"

Portero="Portero"
Jugador="Jugador"

Puerto=8001

# Inicializamos los porteros
gnome-terminal -- bash -c "$EJECUTABLE $EquipoA $Portero $Puerto; exec bash"
Puerto=8002

# Loop para abrir 10 terminales y ejecutar el ejecutable en cada una
for (( i=1; i<=10; i++ ))
do
    # Comando para abrir una nueva terminal y ejecutar el ejecutable con el valor de texto como parámetro
    ((Puerto++))
    gnome-terminal -- bash -c "$EJECUTABLE $EquipoA $Jugador $Puerto; exec bash"
    
done
