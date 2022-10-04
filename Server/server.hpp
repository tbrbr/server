#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <vector>
#include <thread>
#include <SFML/Network.hpp>

using namespace sf;
class ServerNetwork{
    TcpListener listener;
    std::vector<TcpSocket *> client_array;
    unsigned short listen_port;

public:
    ServerNetwork(unsigned short);
    void ConnectClients(std::vector <TcpSocket *> *);
    void DisconnectClient(TcpSocket *, size_t position);
    void ManagePackets();
    void Run();

};

ServerNetwork::ServerNetwork(unsigned short port):listen_port(port){
    logl("Chat server started");
}

void ServerNetwork::ConnectClients(std::vector <TcpSocket *> * client_array){

    while(true){

        logl("Listening connction");
        if(listener.listen(listen_port) != Socket::Done){
            logl("Could not listen");
        }

        TcpSocket * new_client = new TcpSocket();

        if(listener.accept(*new_client) == Socket::Done){
            new_client->setBlocking(false);
            client_array->push_back(new_client);
            logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size());

        }
        else{
            logl("Could not accept clients");
        }
    }
}

void ServerNetwork::DisconnectClient(TcpSocket * socket_pointer, size_t position){
    delete(socket_pointer);
    client_array.erase(client_array.begin() + position);
    logl("Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << "disconected");
}



void ServerNetwork::ManagePackets(){
    while(true){
        for(size_t iterator = 0; iterator < client_array.size(); iterator++){
            TcpSocket * client = client_array[iterator];

            Packet received_packet;
            if(client->receive(received_packet) == Socket::Disconnected){
                DisconnectClient(client, iterator);
                break;
            }

            std::string received_message;
            received_packet >> received_message;
            logl(received_message);

        }
    }
}

void ServerNetwork::Run(){
    std::thread connetion_thread(&ServerNetwork::ConnectClients, this, &client_array);
    ManagePackets();

}
#endif // SERVER_HPP_INCLUDED
