//
// Client.hpp for  in /home/belugum/rendu/cpp_rtype/server
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Fri Jan 19 19:01:23 2018 Maxime Beluguet
// Last update Mon Jan 29 13:08:09 2018 Maxime Beluguet
//

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <Winsock2.h>
//#include <netinet/in.h>
#include "Room.hpp"

class Room;

class Client
{
  sockaddr_in	id;
  std::string	name;
  Room		*room;
  Client();
public:
  Client(sockaddr_in const &);
  ~Client();
  bool	isSame(sockaddr_in const &);
  void	setRoom(Room*);
  Room	*getRoom();
  void	setName(std::string const &);
  std::string const	&getName() const;
  sockaddr_in const	&getId() const;
};

#endif
