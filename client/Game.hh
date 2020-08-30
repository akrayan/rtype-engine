#pragma once

#ifndef __GAME__HH__
# define __GAME__HH__

#include "Menu.hh"

class Game
{
public:
  Game();
  ~Game();
  void		init(size_t width, size_t height);
  void		init_texture_players();
  void		init_texture_ennemies();
  void		init_texture_shoot();
  void		draw(sf::RenderWindow &window, std::string name, int y, int x,
						int rotation);
  std::string	getEvent(const sf::Event &e);
  
private:
  std::map<std::string, sf::Texture>	texture;
  std::map<std::string, sf::Sprite>	sprite;
  size_t			        width;
  size_t				height;
  bool					finish;
  std::map<std::string, sf::Text>	text;
  sf::Font				font;

};

#endif // !__GAME__HH__
