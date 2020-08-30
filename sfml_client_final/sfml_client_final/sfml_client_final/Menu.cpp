//
// Menu.cpp for interface cpp in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
// 
// Made by shiba
// Login   <zita.cheng@epitech.eu>
// 
// Started on  Tue Jan  9 20:22:30 2018 shiba
// Last update Sun Jan 28 16:36:02 2018 shiba
//

#include "Menu.hh"

//TODO enlever le son on entend pas

void		Menu::setBackground()
{
  if (this->texture["space"].loadFromFile("src/spaceship.jpg"))
    {
      this->sprite["space"].setTexture(this->texture["space"]);
      this->sprite["space"].setScale(
				     this->width / this->sprite["space"].getLocalBounds().width,
				     this->height / this->sprite["space"].getLocalBounds().height);
    }
  if (this->texture["title"].loadFromFile("src/title.png"))
    {
      this->sprite["title"].setTexture(this->texture["title"]);
      this->sprite["title"].setScale(1.4, 1.4);
      this->sprite["title"].setPosition(50, 80);
    }
  //Le background du menu
  this->texture["square"].loadFromFile("src/square.png");
  this->sprite["square"].setTexture(this->texture["square"]);
  this->sprite["square"].setScale(1.4, 0.7);
  this->sprite["square"].setPosition(270, 200);
  this->sprite["square"].setColor(sf::Color(255, 255, 255, 200));
}

void		Menu::setInput(int x, int y, std::string index)
{
  this->text[index].setFont(this->font);
  this->text[index].setCharacterSize(18);
  this->text[index].setPosition(x, y);
  this->text[index].setFillColor(sf::Color::Black);
}

void		Menu::setTitle(std::string index, std::string title, int x, int y)
{
  this->text[index].setFont(this->font);
  this->text[index].setString(title);
  this->text[index].setCharacterSize(20);
  this->text[index].setPosition(x, y);
}

void		Menu::setBar(std::string index, int x, int y)
{
  this->sprite[index].setTexture(this->texture["bar"]);
  this->sprite[index].setScale(0.5, 1);
  this->sprite[index].setPosition(x, y);
  this->sprite[index].setTexture(this->texture["bar"]);
}

void		Menu::init(size_t width, size_t height)
{
  this->width = width;
  this->height = height;   
  this->currentInput = NAME;
  this->setBackground();
  
  //Les bar
  this->texture["bar"].loadFromFile("src/bar.png");
  this->setBar("bar_name", 420, 240);
  this->setBar("bar_ip", 420, 340);
  this->setBar("bar_port", 420, 440);
  this->sprite["bar_name"].setColor(sf::Color(0, 255, 255));

  //Titles
  this->font.loadFromFile("src/Oswald.ttf");
  this->setTitle("name", "Name :", 400, 240);
  this->setTitle("ip", "IP Address:", 400, 340);
  this->setTitle("port", "Port :", 400, 440);

  //Input
  this->setInput(440, 280, "in_name");
  this->setInput(440, 380, "in_ip");
  this->setInput(440, 480, "in_port");

  this->finish = false;
}

Menu::Menu()
{
}

Menu::~Menu()
{
}

void		Menu::completeWord(char c)
{
  if (c == 8)
    {
      if (this->currentInput == NAME && this->name.length() > 0)
	this->name.erase(this->name.length() - 1);
      if (this->currentInput == IP && this->ip.length() > 0)
	this->ip.erase(this->ip.length() - 1);
      if (this->currentInput == PORT && this->port.length() > 0)
	this->port.erase(this->port.length() - 1);
    }
  else if (c != 8)
    {
      switch (this->currentInput)
	{
	case NAME:
	  if (this->name.length() <= 50)
	    this->name += c;
	  break;
	case IP:
	  if (this->ip.size() <= 50)
	    this->ip += c;
	  break;
	case PORT:
	  if (this->port.length() <= 50)
	    this->port += c;
	  break;
	}
    }
}

void		Menu::setBarColor()
{
  this->sprite["bar_name"].setColor(sf::Color(255, 255, 255));
  this->sprite["bar_ip"].setColor(sf::Color(255, 255, 255));
  this->sprite["bar_port"].setColor(sf::Color(255, 255, 255));
  switch (this->currentInput)
    {
    case NAME:
      this->currentInput = IP;
      this->sprite["bar_ip"].setColor(sf::Color(0, 255, 255));
      break;
    case IP:
      this->currentInput = PORT;
      this->sprite["bar_port"].setColor(sf::Color(0, 255, 255));
      break;
    case PORT:
      this->currentInput = NAME;
      this->sprite["bar_name"].setColor(sf::Color(0, 255, 255));
      break;
    }
}

void		Menu::event(const sf::Event &e)
{
  if (e.type == sf::Event::TextEntered && e.text.unicode == 9)
    this->setBarColor();
  if (e.type == sf::Event::TextEntered && e.text.unicode == 13 &&
      this->name.length() > 0 && this->port.length() > 0 &&
      this->ip.length() > 0)
    this->finish = true;
  if (e.type == sf::Event::TextEntered &&
      ((e.text.unicode < 128 &&
	e.text.unicode >= 32) || e.text.unicode == 8))
    this->completeWord(static_cast<int>(e.text.unicode));
}

void		Menu::draw(sf::RenderWindow &win)
{
  win.draw(this->sprite["space"]);
  win.draw(this->sprite["title"]);
  win.draw(this->sprite["square"]);
  win.draw(this->sprite["bar_name"]);
  win.draw(this->sprite["bar_ip"]);
  win.draw(this->sprite["bar_port"]);
  win.draw(this->text["name"]);
  win.draw(this->text["ip"]);
  win.draw(this->text["port"]);
  this->text["in_name"].setString(this->name);
  win.draw(this->text["in_name"]);
  this->text["in_ip"].setString(this->ip);
  win.draw(this->text["in_ip"]);
  this->text["in_port"].setString(this->port);
  win.draw(this->text["in_port"]);
}

bool		Menu::isFinish() const
{
  return (this->finish);
}

std::string	Menu::getName() const
{
  return (this->name);
}

std::string	Menu::getIp() const
{
  return (this->ip);
}

std::string	Menu::getPort() const
{
  return (this->port);
}

void		Menu::setFinish(bool v)
{
  this->finish = v;
}
