#include <iostream>

using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>
<<<<<<< HEAD
#include "strings.h"
=======
#include "funciones_strings.h"
>>>>>>> 9fad1ea (Tarea 2 (No chutan))
#include "funciones.h"
#include <random>
#include "tictoc.h"
#include <chrono>
#include <thread>



int main(int argc, char* argv[])
{   
    // check if the number of arguments is correct
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <team-name>" << endl;
        return 1;
    }

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

<<<<<<< HEAD
    // send a message to the udp server - move players, etc. etc.
    Player player;
    player = getPlayer(received_message_content);




    if (received_message_content != "(error no_more_team_or_player_or_goalie)"){ // Si no recibimos un error por parte del servidor
        string mensaje_init = colocar_init(received_message_content); // Colocamos los 22 jugadores en el campo con la funcion colocar_init
        udp_socket.sendTo(mensaje_init, server_upd);
    }

    bool enJuego = false; // Booleano que valdrá true si el partido está en juego

=======
    // Creamos la estructura del jugador
    auto miPlayer = getPlayer(received_message_content);

    // Colocamos al jugador en su posición inicial
    if (received_message_content != "(error no_more_team_or_player_or_goalie)"){ // Si no recibimos un error por parte del servidor
        udp_socket.sendTo(colocar_init(miPlayer), server_upd); // Colocamos al jugador en el campo
    } else cout << "ERROR: Este equipo está completo" << endl;

    bool enJuego = false; // Booleano que valdrá true si el partido está en juego

    Ball balon; // Creamos una estructura para el balon

    Porteria miPorteria; // Creamos la estructura para la porteria en la que queramos marcar
    if (miPlayer.lado_campo == "r")
        miPorteria.lado_porteria = "l";
    else
        miPorteria.lado_porteria = "r";


    TicToc clock; // Creo un reloj para realizar temporizaciones
    TicToc clock2; // Creo un reloj para realizar temporizaciones
    TicToc clock3; // Creo un reloj para realizar temporizaciones
>>>>>>> 9fad1ea (Tarea 2 (No chutan))

    while (true)
    {   
        auto received_message = udp_socket.receive(message_max_size);
        std::string received_message_content = received_message->received_message;
        //cout << received_message_content << endl;
        if (enJuego == false){ // Si no se está jugando (juego parado)
            if (check_init(received_message_content)){ // Comprobamos si el árbitro pitó el saque
                enJuego = true; // Empezó el partido o la segunda parte (juego en marcha)
                cout << "EMPEZO EL PARTIDO" << endl;
            }
        }



        if (enJuego == false){ // Si no se está jugando (juego parado)
            if (check_init(received_message_content)){ // Comprobamos si el árbitro pitó el saque
                enJuego = true; // Empezó el partido o la segunda parte (juego en marcha)
                cout << "EMPEZÓ EL PARTIDO O LA SEGUNDA PARTE" << endl;
                udp_socket.sendTo("(kick 40 180)", server_upd);
                
                // Orientamos al jugador para que mire hacia el saque en el mediocampo
                udp_socket.sendTo(orientar_init(miPlayer), server_upd);
                cout << "Jugador orientado correctamente hacia el balón" << endl;
            }
        }

        if (enJuego == true) { // Comprobamos si se está jugando
            if (check_stop(received_message_content)){ // Comprobamos que el arbitro pitó el descanso o el final
                enJuego = false; // Descanso o final
                cout << "DESCANSO O FINAL DEL PARTIDO" << endl;
            }

            if (enJuego == true && miPlayer.dorsal != "1"){ // Si estamos seguros de que esta en juego
                while (!check_see(received_message_content)){ // Espero a recibir un see (mientras el mensaje recibido no sea un see...)
                    received_message = udp_socket.receive(message_max_size); // Recibo otro mensaje del servidor
                    received_message_content = received_message->received_message; // Accedo al contenido del mensaje
                }

                // Compruebo si se está viendo el balón.
                if (check_see_ball (received_message_content)){ // Si se está viendo, me oriento hacia el balón
                    balon = check_ball(received_message_content, balon); // Actualizo la posicion del balon


                    cout<< "DISTANCIA AL BALON: " << balon.distancia << endl;

                    // Compruebo si estoy lo suficientemente cerca del balón para tirar
                    if (stof(balon.distancia) < 0.6) { // Si estoy lo suficientemente cerca del balón para chutar 
                        while (!check_see_porteria(received_message_content, miPlayer)){ // Mientras no vea la porteria rival y no reciba un see
                            udp_socket.sendTo("(turn 40)", server_upd); // Giro 80º a ver si en la siguiente iteración la veo ya

                            // Le doy tiempo al servidor para que genere otro mensaje (100 ms)
                            clock3.tic(); // Inicio la temporización
                            while (clock3.toc() < 150)
                                this_thread::sleep_for(chrono::milliseconds(1));

                            received_message = udp_socket.receive(message_max_size); // Recibo otro mensaje del servidor
                            received_message_content = received_message->received_message; // Accedo al contenido del mensaje

                            cout << "GIRO BUSCANDO PORTERIA" << endl;
                        }

                        // Una vez que ya vea la porteria saldre del bucle anterior y aqui actualizo su posicion
                        miPorteria = check_porteria(received_message_content, miPorteria); // Actualizo los datos de la porteria rival

                        udp_socket.sendTo("turn " + miPorteria.direccion_centro_porteria + ")", server_upd); // Me oriento al centro de la porteria rival

                        cout << "GIRO HACIA LA PORTERIA" << endl;

                        // Le doy tiempo al servidor para que genere otro mensaje (300 ms)
                        clock2.tic(); // Inicio la temporización
                        while (clock2.toc() < 300)
                            this_thread::sleep_for(chrono::milliseconds(1));

                        received_message = udp_socket.receive(message_max_size); // Recibo otro mensaje del servidor

                        // Una vez orientado hacia la porteria tiro recto hacia ella
                        udp_socket.sendTo("kick 100 0)", server_upd); 

                        cout << "DISPARO A PORTERIA" << endl;
                    }

                    else { // Si no estoy lo suficientemente cerca del balon
                        udp_socket.sendTo("(turn " + balon.direccion + ")", server_upd); // Me giro en la direccion del balon para verlo de frente

                        // Le doy tiempo al servidor para que genere otro mensaje (150 ms)
                        clock.tic(); // Inicio la temporización
                        while (clock.toc() < 150)
                            this_thread::sleep_for(chrono::milliseconds(1));

                        // Ahora recibo un mensaje cualquiera que me da igual (solo para poder enviar otro comando después al servidor)
                        received_message = udp_socket.receive(message_max_size); // Recibo otro mensaje del servidor

                        // Ahora ya puedo enviar la orden de correr
                        udp_socket.sendTo("(dash 80 0)", server_upd); // Corro en linea recta

                        cout << "DASH" << endl;
                    }


                    
                }
                else { // Si no se está viendo 
                    udp_socket.sendTo("(turn 80)", server_upd); // Giro 80º a ver si en la siguiente iteración lo veo ya
                }






                /*balon = check_ball(received_message_content, balon); // Si puedo actualizo la posicion del balon
                porteriaIzq = check_porteria (received_message_content, porteriaIzq); // Si puedo actualizo la posicion de la porteria izquierda
                porteriaDer = check_porteria (received_message_content, porteriaDer); // Si puedo actualizo la posicion de la porteria derecha
            

                if (stof(balon.distancia) > 0.001) { // Si estamos todavía lejos del balón
                    udp_socket.sendTo("(turn " + balon.direccion + ")", server_upd); // Nos orientamos hacia el balón
                    received_message = udp_socket.receive(message_max_size); // Recibimos un mensaje cualquiera para poder volver a enviar una orden al servidor
                    udp_socket.sendTo("(dash 100 0)" , server_upd); // Corremos recto hacia el balón con 70 de velocidad y 0 de angulo
                } 

                if (stof(balon.distancia) < 0.001) { // Si estamos ya cerca del balón
                    cout << "VOY A TIRAR" << endl;
                    string angulo_chute; // Direccion con la que tirar a porteria
                    if (miPlayer.lado_campo == "l") {
                        angulo_chute = to_string ((stof(porteriaDer.direccion_centro_porteria) + stof(porteriaDer.direccion_palo_arriba)) / 2);
                    }
                    if (miPlayer.lado_campo == "r") {
                        angulo_chute = to_string ((stof(porteriaIzq.direccion_centro_porteria) + stof(porteriaIzq.direccion_palo_arriba)) / 2);
                    }
                    
                    udp_socket.sendTo("(turn " + angulo_chute + ")", server_upd); // Nos orientamos hacia la porteria
                    received_message = udp_socket.receive(message_max_size); // Recibimos un mensaje cualquiera para poder volver a enviar una orden al servidor
                    udp_socket.sendTo("(kick 100 0)", server_upd); // Tiramos recto a toda potencia
                }*/
            }
        }



        // PROCESS THE DATA AND SEND A COMMAND TO THE SERVER

        
    }

    return 0;
}