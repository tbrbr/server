#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>

using namespace sf;
using namespace std;


void recieveData(UdpSocket & socket, IpAddress & ip, char data[], unsigned short port){
    
    sf::IpAddress sender;
    size_t received;
    if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
    {
        cout << "erro ao receber dados" << endl;
    }
    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;

}

void SendData(UdpSocket & socket, const char * message, IpAddress & ip, unsigned short port){
    
    if (socket.send(message, strlen(message) + 1, ip, port) != sf::Socket::Done)
    {
        std::cout << "Falha na comunicação com o servidor" << std::endl;
    }
}

int main()
{   
    UdpSocket socket;
    IpAddress ip = IpAddress::getLocalAddress();


// bind the socket to a port
    if (socket.bind(2000) != sf::Socket::Done)
    {
        cout << "Error" << endl;
    }

    char data[1024];

    recieveData(socket, ip, data, 2000);
    std::cout << data << std::endl;
    SendData(socket, "insanoviu", ip, 2001);
}

