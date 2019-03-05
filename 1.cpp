#include<iostream>
#include<SFML/Network.hpp>
#include<unistd.h>
int main()
{
	sf::IpAddress IP;	
	/*
	 * sf::IpAddress IP = sf::IpAddress::getLocalAddress(); // ServIP
	 * std::cout << IP << ' ' << sf::IpAddress::getPublicAddress() << std::endl;
	 */
	std::string IP_name;
	sf::TcpSocket socket;
	char buffer[2000];
	std::string text;
	char con = 0, mode = 0 ;
	//size_t received;
	std::cout << "Enter (s) for server, Enter (c) for client " << std::endl;
	std::cin >> con;
	
	sf::Packet packet;

	if(con == 's')
	{
		//Server
		sf::IpAddress IP = sf::IpAddress::getLocalAddress(); // ServIP
		std::cout << IP << std::endl;
		
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);

		std::cout <<  "Con. to Client" << std::endl;
		packet << "Con. to Server";
		mode = 's';
		socket.send(packet);
		packet.clear();
	}
	else if(con == 'c')
	{
		//Client
		std::cout << "Enter IP:";
		std::cin >> IP_name;
		IP = IP_name;
		socket.connect(IP, 2000);

		mode = 'r';
		socket.receive(packet);
		packet >> buffer;
		std::cout << buffer << std::endl;
		packet.clear();
	}
	std::getline(std::cin,text);
	bool done = false;
	while(!done)
		if(mode == 's')
		{
			std::getline(std::cin,text);
			packet << text;	
			socket.send(packet);
			usleep(500);
			mode = 'r';
			packet.clear();
			socket.receive(packet);
			packet.clear();
		}
		else if (mode == 'r')
		{
			socket.receive(packet);
			usleep(500);
			packet >> buffer;
			std::cout << "Received: " << buffer << std::endl;
			mode = 's';
			packet.clear();
			packet << true;
			socket.send(packet);
			packet.clear();
		}
	return 0;
}
