//
// Room.hpp for  in /home/belugum/rendu/cpp_rtype/server
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Fri Jan 19 18:16:30 2018 Maxime Beluguet
// Last update Mon Jan 29 13:42:03 2018 Maxime Beluguet
//

#ifndef ROOM_HPP_
# define ROOM_HPP_

#include <string>
#include <thread>
#include <vector>
#include <map>
#include <cstring>
#include "Client.hpp"
//#include "Engine.h"
//#include "../network/NetworkManager.hpp"

class Client;
class NetworkManager; //A enlever quand network OK
class RessourceManager;
class Script;
class GameManager;

class Room
{
  std::string	name;
  std::string	pass;
  bool		game_on;
  NetworkManager	*network;
  RessourceManager	*rsc;
  std::map<std::string, Script *(*)()> *listScript;

  GameManager	*game;
  std::vector<Client*>	clients;
  std::thread		*game_thread;
  Room();
public:
  Room(char*, char*, std::string const &, NetworkManager*, RessourceManager*, std::map<std::string, Script *(*)()> *);
  ~Room();
  bool	addClient(Client*);
  void	startGame();
  void	sendEvent(char, char, sockaddr_in const &);
  void	writeInfo(char*, char);
  void	sendAll(std::string);
  void	sendToOne(std::string, int id);
private:
  void	runRoom();
};

#endif
