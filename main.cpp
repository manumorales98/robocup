#include <iostream>

using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>
#include "strings.h"
#include "colocar_init.h"
#include <random>

int main(int argc, char* argv[])
{
    // El main recibe como parametro el nombre del equipo
    string miEquipo = argv[1];

    // Aqui creo un generador de numeros randomizados para que cada vez que ejecute el main salga un puerto distinto para cada jugador
    random_device rd;
    mt19937 gen(rd());

    // Defino el rango de los valores que me valdrian para el puerto (6000 - 10000)
    std::uniform_int_distribution<> distribucion(6000, 10000);
    
    // Generar el número aleatorio
    int puerto_aleatorio = distribucion(gen);

    // Mi puerto de recepción de datos desde el servidor y desde el que envío datos al servidor
    MinimalSocket::Port this_socket_port = puerto_aleatorio;

    //MinimalSocket::Port this_socket_port = 5555;

    cout << "Creating a UDP socket" << endl;

    MinimalSocket::udp::Udp<true> udp_socket(this_socket_port, MinimalSocket::AddressFamily::IP_V6);

    cout << "Socket created" << endl;

    bool success = udp_socket.open();

    if (!success)
    {
        cout << "Error opening socket" << endl;
        return 1;
    }

    // send a message to another udp
    MinimalSocket::Address other_recipient_udp = MinimalSocket::Address{"127.0.0.1", 6000};
    udp_socket.sendTo("(init "+miEquipo+"(version 19))", other_recipient_udp);
    cout << "Message sent" << endl;

    // receive a message from another udp reaching this one
    std::size_t message_max_size = 1000;
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

    // send a message to the udp server - move players, etc. etc.
    if (received_message_content != "(error no_more_team_or_player_or_goalie)"){ // Si no recibimos un error por parte del servidor
        string mensaje_init = colocar_init(received_message_content); // Colocamos los 22 jugadores en el campo con la funcion colocar_init
        udp_socket.sendTo(mensaje_init, server_upd);
    }


    while (true)
    {
        auto received_message = udp_socket.receive(message_max_size);
        std::string received_message_content = received_message->received_message;
        //cout << received_message_content << endl;

        // PROCESS THE DATA AND SEND A COMMAND TO THE SERVER

        
    }

    return 0;
}