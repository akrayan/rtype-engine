//
// Menu.hh for interface in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
// 
// Made by shiba
// Login   <zita.cheng@epitech.eu>
// 
// Started on  Tue Jan  9 20:19:55 2018 shiba
// Last update Sun Jan 28 15:51:28 2018 shiba
//

#ifndef MENU_HH
# define MENU_HH

# include <iostream>
# include <map>
# include <SFML/Audio.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

enum		Input
  {
    NAME = 0,
    IP = 1,
    PORT = 2
  };

class					Menu
{
private:
  std::map<std::string, sf::Texture>	texture;
  std::map<std::string, sf::Sprite>	sprite;
  size_t				width;
  size_t				height;
  bool					finish;
  std::map<std::string, sf::Text>	text;
  sf::Font				font;
  Input					currentInput;
  std::string				name;
  std::string				ip;
  std::string			        port;
  sf::Vector2i				mouse;
  
  void					setBackground();
  void					checkMouse();
  void				        setInput(int, int, std::string);
  void				        setTitle(std::string, std::string, int, int);
  void				        setBar(std::string, int, int);
  void					setBarColor();
  void					completeWord(char);

public:
  Menu();
  ~Menu();
  void					init(size_t, size_t);
  bool					isFinish() const;
  void					event(const sf::Event &);
  void					draw(sf::RenderWindow &);
  std::string				getName() const;
  std::string				getIp() const;
  std::string				getPort() const;
  void					setFinish(bool v);
};

# endif /* MENU_HH_ */
