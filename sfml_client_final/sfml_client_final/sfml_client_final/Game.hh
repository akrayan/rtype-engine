#pragma once

#ifndef __GAME__HH__
# define __GAME__HH__

#include "Menu.hh"
#include "GameStruct.h"
#include "network\INetwork.hpp"

typedef struct GameObject {
	sf::Texture text;
	sf::Sprite sprite;
	int id;
} GameObject;

class Game
{
public:
  Game();
  ~Game();
  void init_texture(std::string path);
  void init_sound(std::string path);
  void init_font(std::string path);

  void		init(size_t width, size_t height);
  void		init_texture_players();
  void		init_texture_ennemies();
  void		init_texture_shoot();
  void		draw(sf::RenderWindow &window, gameStruct stGame);
  //void		draw(sf::RenderWindow &window, gameData servInfo);
  std::string	getEvent(const sf::Event &e);
  
private:
	std::initializer_list<GameObject *> objectlist;
	std::map<std::string, sf::Music>	sound;
	std::map<std::string, sf::Font>	fonts;
  std::map<std::string, sf::Texture>	texture;
  std::map<std::string, sf::Sprite>	sprite;
  size_t			        width;
  size_t				height;
  bool					finish;
  std::map<std::string, sf::Text>	text;
  sf::Font				font;

};

#endif // !__GAME__HH__
