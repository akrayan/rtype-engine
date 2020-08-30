//
// Interface.hh for inter in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
// 
// Made by shiba
// Login   <zita.cheng@epitech.eu>
// 
// Started on  Fri Jan 12 22:45:06 2018 shiba
// Last update Mon Jan 29 11:54:46 2018 shiba
//

#ifndef INTERFACE_HH
# define INTERFACE_HH

# include <iostream>
# include <SFML/Audio.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <ctime>
# include <cstdlib>
# include <chrono>
# include "Menu.hh"
# include "Room.hh"
# include "Game.hh"
# include "../network/NetworkManager.hpp"

enum	View
  {
    MENU,
    ROOM,
    GAME
  };

class			Interface
{
private:
  bool				        click;
  size_t				width;
  size_t				height;
  sf::RenderWindow			window;
  Menu					menu;
  Room					room;
  Game					game;
  bool					quit;
  View					view;
  sf::Music				music;
  sf::Event				ev;
  bool					evSuccess;
  std::map<std::string, sf::Sprite>	sprite;
  std::map<std::string, sf::Texture>	texture;
  sf::Clock				timer;
  sf::Vector2i                          mouse;
  sf::Vector2i                          win_pos;
  NetworkManager			*client;
  Packet				packet;
  
public:
  Interface();
  ~Interface();
  void			loop();
  void		        event();
  bool			connect();
  void			load();
  void			initLoad();
  void			callMenu();
  void			callRoom();
  void		        callGame();
};

# endif /* INTERFACE_HH */
