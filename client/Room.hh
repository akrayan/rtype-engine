//
// Room.hh for Room in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
// 
// Made by shiba
// Login   <zita.cheng@epitech.eu>
// 
// Started on  Fri Jan 12 23:24:35 2018 shiba
// Last update Sun Jan 28 19:05:32 2018 shiba
//

#ifndef ROOM_HH
# define ROOM_HH

# include <iostream>
# include <map>
# include <SFML/Audio.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <list>
# include <cstdint>
# include <cstring>
# include "../network/NetworkManager.hpp"

class					Room
{
  enum	Choice
  {
    CREATE,
    JOIN,
    MENU
  };

  enum	Input
  {
    NAME,
    PASS
  };

private:
  std::map<std::string, sf::Texture>    texture;
  std::map<std::string, sf::Sprite>     sprite;
  std::map<std::string, sf::Text>	text;
  std::map<std::string, sf::Font>	font;
  std::map<std::string, sf::RectangleShape>	rect;
  std::vector<char *>			rooms;
  std::string				name;
  std::string				password;
  size_t				width;
  size_t				height;
  int					buttonId;
  Choice				currentInt;
  size_t				index;
  size_t				max;
  Input					currentInput;
  bool					finish;
  size_t				page;
  size_t				max_p;
  int					max_y;
  size_t				line;
  
public:
  Room();
  ~Room();
  std::string				getName() const;
  void					event(const sf::Event &, sf::RenderWindow &);
  void					draw(sf::RenderWindow &);
  void					init(size_t, size_t);
  void					buttonTexture(int, int, const std::string &);
  void					setButton(int, int, const std::string &);
  void					setTitle(int, int, const std::string &,
						 const std::string &, int);
  void					drawMenu(sf::RenderWindow &);
  void					drawJoin(sf::RenderWindow &);
  void					drawCreate(sf::RenderWindow &);
  void					completeWord(char);
  std::string				getPassword() const;
  void					setBar(const std::string &, int, int);
  void					setText(const std::string &, int, int);
  void					menuEvent(const sf::Event &);
  bool					onClick(sf::RenderWindow &);
  bool				        isFinish() const;
  void					mouseEvent(const sf::Event &, sf::RenderWindow &);
  void					setBase();
  void					initCreate();
  void					initJoin();
  void					joinText(const std::string &, int,
						 int, const std::string &);
  void					emptyRect(const std::string &, int, int);
  void					listRoom(sf::RenderWindow &);
  void					calculLine(sf::Vector2i);
  void					setRoom(char *);
  bool					sendJoin(NetworkManager *, Packet,
						 const std::string &);
};

# endif /* ROOM_HH */
