#include "Engine.h"



Application::Application() : /*scene("defaultScene"),*/ game_on(true)
{

}


Application::~Application()
{
}

void Application::initServer()
{
	network_udp = new NetworkManager();
	if (network_udp->init(SERVER, "", 4242) != 0)
	{
		delete network_udp;
		network_udp = nullptr;
		std::cout << "ERROR SERVEUR" << std::endl;
	}
}

void	Application::runApp()
{
	Packet	packet;
	Client	*cur_client;

	if (!network_udp)
	  return ;
	while (game_on)
	{
		if (network_udp->getSizeReceiveList() > 0)
		{
			packet = network_udp->getReceivePacket();
			//std::cout << "got packet" << std::endl;
			cur_client = getClient(packet);
			if (!cur_client->getRoom())
				handleRoomCommand(packet, cur_client);
			else
				handleGameCommand(packet, cur_client);
		}
	}
}

Client	*Application::getClient(Packet const &packet)
{
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it)->isSame(packet.dest))
			return (*it);
	}
	clients.push_back(new Client(packet.dest));
	return (clients.back());
}

void	Application::handleRoomCommand(Packet &packet, Client *client)
{
	size_t	ind = 1;
	char		*name;
	char		*pass;
	char		*user;

	if (packet.data.data[0] == 1)// join room
	{
	  std::cout << "join room" << std::endl;
	  ind = 3;
		pass = packet.data.data + ind;
		findNextString(packet.data.data, ind);
		user = packet.data.data + ind;
		client->setName(user);
		if (*((short*)(packet.data.data + 1)) < rooms.size() &&
			*((short*)(packet.data.data + 1)) >= 0 &&
			rooms[*((short*)(packet.data.data + 1))]->addClient(client))
		{
			client->setRoom(rooms[*((short*)(packet.data.data + 1))]);
			packet.data.data[0] = 2;
			network_udp->addSendPacketInList(packet);
			return;
		}
	}
	else if (packet.data.data[0] == 2)// new room
	{
	  std::cout << "new room" << std::endl;
		name = packet.data.data + ind;
		std::cout << name << std::endl;
		findNextString(packet.data.data, ind);
		pass = packet.data.data + ind;
		findNextString(packet.data.data, ind);
		user = packet.data.data + ind;
		client->setName(user);
		//std::cout << "pour l'instant la scene = " << scene << std::endl;
		rooms.push_back(new Room(name, pass, defaultScene, network_udp, &ressourceManager, &listScript));
		client->setRoom(rooms.back());
		rooms.back()->addClient(client);
		rooms.back()->startGame();
		*((short*)(packet.data.data + 1)) = rooms.size() - 1;
		network_udp->addSendPacketInList(packet);
		return;
	}
	else
	{
		packet.data.data[0] = 1;
		ind = 0;
		std::cout << "new client" << std::endl;
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
		  std::cout << "send room" << std::endl;
			(*it)->writeInfo(packet.data.data, ind);
			network_udp->addSendPacketInList(packet);
			ind += 1;
		}
	}
	packet.data.data[0] = -1;
	network_udp->addSendPacketInList(packet);
}

void	Application::handleGameCommand(Packet &packet, Client *client)
{
  //std::cout << "game cmd" << std::endl;
	client->getRoom()->sendEvent(packet.data.data[0], packet.data.data[1], client->getId());
}

void	Application::findNextString(char *str, size_t &ind)
{
	while (str[ind] != 0 && ind < 511)
		ind += 1;
	ind += 1;
}
bool Application::SetDefaultScene(std::string scenePath)
{
	if (scenePath.substr(scenePath.find(".")) == ".scene")
	{
		defaultScene = scenePath;
		return (true);
	}
	return false;
}

void Application::SetResolution(sf::Vector2i res)
{
	//resolution = res;
}

void Application::SetResolution(int x, int y)
{
	/*
	resolution.x = x;
	resolution.y = y;
	*/
	}

void Application::Launch()
{
	//_window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "SFML works!");
  //Game = new GameManager(&ressourceManager, defaultScene, listScript);
	/*_scene = new Scene(listScript);
	_scene->LoadScene(_defaultScene);
	GameLoop();*/
}
