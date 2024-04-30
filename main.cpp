#include <iostream>

using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>
#include "funciones_strings.h"
#include "funciones.h"
#include "funcion_main.h"
#include "tictoc.h"
#include <chrono>
#include <thread>


int main(int argc, char* argv[])
{   
    // check if the number of arguments is correct
    if (argc != 4)
    {
        throw runtime_error("Error: Nombre del equipo sin especificar al llamar a main");
    }

    // El main recibe como parametro el nombre del equipo
    string miEquipo = argv[1];

    // El main recibe como segundo dato el tipo de jugador
    string tipo_jugador = argv[2];

    // El main recibe el puerto
    string puerto = argv[3];

    // Mi puerto de recepción de datos desde el servidor y desde el que envío datos al servidor
    MinimalSocket::Port this_socket_port = stoi(puerto);

    //MinimalSocket::Port this_socket_port = 5555;

    cout << "Creating a UDP socket" << endl;

    MinimalSocket::udp::Udp<true> udp_socket(this_socket_port, MinimalSocket::AddressFamily::IP_V6);

    cout << "Socket created" << endl;

    bool success = udp_socket.open();

    if (!success)
    {
        throw runtime_error("Error: Problema abriendo el socket");
    }

    // send a message to another udp
    MinimalSocket::Address other_recipient_udp = MinimalSocket::Address{"127.0.0.1", 6000};
    if (tipo_jugador == "Jugador"){
        udp_socket.sendTo("(init "+miEquipo+"(version 19))", other_recipient_udp);
    }
    if (tipo_jugador == "Portero"){
        udp_socket.sendTo("(init "+miEquipo+"(version 19) (goalie))", other_recipient_udp);
    }
    cout << "Message sent" << endl;

    // receive a message from another udp reaching this one
    std::size_t message_max_size = 5000;
    cout << "Waiting for a message" << endl;
    auto received_message = udp_socket.receive(message_max_size);
    // check the sender address
    MinimalSocket::Address other_sender_udp = received_message->sender;
    // access the received message
    // resized to the nunber of bytes
    // actually received
    std::string received_message_content = received_message->received_message;
    cout << received_message_content << endl;

    // update upd port to provided by the other udp
    MinimalSocket::Address server_upd = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()};


    Datos_Partido datos; // Estructura con los datos del balón, porteria y jugador
    datos = getPlayer(received_message_content, miEquipo); // Actualizamos los datos del jugador y del estado del partido


    // Colocamos al jugador en su posición inicial
    if (received_message_content != "(error no_more_team_or_player_or_goalie)"){ // Si no recibimos un error por parte del servidor
        udp_socket.sendTo(colocar_init(datos), server_upd); // Colocamos al jugador en el campo
    } else throw runtime_error("Error: El equipo esta completo. No se pueden añadir mas");
    

    // Inicializamos el temporizador
    TicToc clock;
    clock.tic();

    while (true){

        do{
            received_message = udp_socket.receive(message_max_size);
            received_message_content = received_message->received_message;
        
            try
            {
                datos = funcion_main_recepcion(received_message_content, datos);

            }
            catch (const std::exception &e)
            {
                cout << e.what() << endl;
            }
        } while (received_message_content.find("(see") == -1);


        // Le enviamos al servidor lo que debe hacer el jugador dependiendo del valor de los datos
        udp_socket.sendTo(funcion_main_envio(datos), server_upd);

        //cout << "time: " << clock.toc() << "ms" << endl;
        clock.tic();

        

    }

    return 0;
}