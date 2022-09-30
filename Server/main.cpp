#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	TcpSocket socket;
	IpAddress ip = IpAddress::getLocalAddress();

	char connectionType, mode;
	char buffer[1000];
	size_t received;

	cout << "Enter (s) for Server, Enter (c) for client: " << endl;
	cin >> connectionType;

	if (connectionType == 's') {
		TcpListener listener;
		listener.listen(2000);
		cout << "================\n";
		listener.accept(socket);
		socket.send("Mensagem Enviada com sucesso", 30);

	}
	else if(connectionType == 'c') {
		socket.connect(ip, 2000);
		string message;
		cout << "Digite a mensagem a ser enviada: ";
		getchar();
		getline(cin, message);
		socket.send(message.c_str(), message.length() + 1);
	}

	socket.receive(buffer, sizeof(buffer), received);

	cout << buffer << endl;


}

