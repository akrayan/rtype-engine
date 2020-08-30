//
// Room.cpp for  in /home/belugum/rendu/cpp_rtype/server
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Fri Jan 19 18:16:28 2018 Maxime Beluguet
// Last update Mon Jan 29 14:36:53 2018 Maxime Beluguet
//

#include <Winsock2.h>

#include <iostream>
#include "Room.hpp"
#include "Engine.h"

Room::Room(char *name, char *pass,
	   std::string const &scene,
	   NetworkManager *network,
	   RessourceManager* rsc,
	   std::map<std::string, Script *(*)()> *ls) : name(name),
						       pass(pass ? pass : ""),
						       game_on(true),
						       network(network),
						       rsc(rsc),
						       listScript(ls)
				    //,game(network, scene)
{
	std::cout << "on creer une room et une game avec " << scene << std::endl;
	game = new GameManager(rsc, this, scene, listScript);

}

Room::~Room()
{
}

bool	Room::addClient(Client* client)
{
  if (clients.size() >= 4)
    return (false);
  clients.push_back(client);
  game->AddClient(client);
  return (true);
}

void	Room::runRoom() //Appels au game (?) peut-etre à enlever
{
  while (game_on)
    {
      game->GameLoop();
    }
}

void	Room::startGame()
{
  game_thread = new std::thread(&Room::runRoom, this);
  /*  while (game_on)
    {
      game->GameLoop();
      }*/
}

void	Room::sendEvent(char type, char key, sockaddr_in const &id)
{
  //  std::cout << "key = "<< (int)key << std::endl;
  game->ReceivePacket(static_cast<sf::Event::EventType>(type), static_cast<sf::Keyboard::Key>(key), id);
  //game.event(event, id);
}

void	Room::writeInfo(char* packet, char id)
{
  size_t	ind = 4;

  *((short*)(packet + 1)) = id;
  packet[3] = (char)clients.size();
  std::cout << clients.size() << std::endl;
  std::memcpy(packet + ind, name.c_str(), name.length() > 32 ? 32 : name.length());
  ind += (name.length() > 32 ? 32 : name.length()) + 1;
  packet[ind - 1] = 0;
  for (auto it = clients.begin(); it != clients.end(); it++)
    {
      std::memcpy(packet + ind, (*it)->getName().c_str(),
		  (*it)->getName().length() > 32 ? 32 : (*it)->getName().length());
      ind += ((*it)->getName().length() > 32 ? 32 : (*it)->getName().length()) + 1;
      packet[ind - 1] = 0;
    }
}

void	Room::sendAll(std::string str)
{
  Packet	tmp;

  //std::cout << "i send  =   " << str << std::endl;
  std::memcpy(tmp.data.data, str.c_str(), str.size());
  //tmp.data = ...
  for (auto it = clients.begin(); it != clients.end(); it++)
    {
      tmp.dest = (*it)->getId();
      network->addSendPacketInList(tmp);
    }
}

void Room::sendToOne(std::string str, int id)
{
	Packet	tmp;

	//std::cout << "i send  =   " << str << std::endl;
	std::memcpy(tmp.data.data, str.c_str(), str.size());
	//tmp.data = ...
		tmp.dest = clients[id]->getId();
		network->addSendPacketInList(tmp);
}
