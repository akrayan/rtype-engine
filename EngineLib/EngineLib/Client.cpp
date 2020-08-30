//
// Client.cpp for  in /home/belugum/rendu/cpp_rtype/server
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Fri Jan 19 19:01:19 2018 Maxime Beluguet
// Last update Sun Jan 21 21:27:24 2018 Maxime Beluguet
//

#include "Client.hpp"

Client::Client(sockaddr_in const &sock_id):id(sock_id),room(nullptr)
{
}

Client::~Client()
{
}

bool	Client::isSame(sockaddr_in const &sock_id)
{
  return (sock_id.sin_port == id.sin_port &&
	  sock_id.sin_addr.s_addr == id.sin_addr.s_addr);
}

void	Client::setRoom(Room *room)
{
  this->room = room;
}

Room	*Client::getRoom()
{
  return (room);
}

void	Client::setName(std::string const &name)
{
  this->name = name;
}

sockaddr_in const	&Client::getId() const
{
  return (id);
}

std::string const	&Client::getName() const
{
  return (name);
}
