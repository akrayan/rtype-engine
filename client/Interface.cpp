//
// Interface.cpp for inter in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
//
// Made by shiba
// Login   <zita.cheng@epitech.eu>
//
// Started on  Fri Jan 12 22:49:46 2018 shiba
// Last update Mon Jan 29 11:56:30 2018 shiba
// Last update Sun Jan 28 20:14:01 2018 Maxime Beluguet
//

#include "Interface.hh"

void		Interface::initLoad()
{
  int		x;
  int	        y;
  int		i;

  y = 1;
  i = 1;
  if (this->texture["load"].loadFromFile("src/loading.png"))
    while (y < 724)
      {
	x = 1;
	while (x < 905)
	  {
	    this->sprite["load" + i].setTexture(this->texture["load"]);
	    this->sprite["load" + i].setTextureRect(sf::IntRect(x, y, 177, 177));
	    this->sprite["load" + i].setPosition(550, 600);
	    x += 181;
	    i += 1;
	  }
	y += 181;
      }
}

Interface::Interface()
{
  std::srand(std::time(nullptr));
  this->width = 1400;
  this->height = 800;
  this->window.create(sf::VideoMode(this->width, this->height), "RType");
  this->window.setMouseCursorVisible(false);
  this->texture["cursor"].loadFromFile("src/cursor1.png");
  this->sprite["cursor"].setTexture(this->texture["cursor"]);
  this->sprite["cursor"].setScale(0.3, 0.3);
  this->texture["click"].loadFromFile("src/cursor2.png");
  this->sprite["click"].setTexture(this->texture["click"]);
  this->sprite["click"].setScale(0.3, 0.3);
  if (this->music.openFromFile("src/intro.ogg"))
    {
      this->music.setLoop(true);
      this->music.play();
    }
  this->menu.init(this->width, this->height);
  this->room.init(this->width, this->height);
  this->game.init(this->width, this->height);
  this->initLoad();
  this->quit = false;
  this->click = false;
  this->view = MENU;
}

Interface::~Interface()
{
  this->window.close();
  this->music.stop();
  this->view = MENU;
}

void		Interface::event()
{
  Packet	tmp;

  this->evSuccess = false;
  if ((this->evSuccess = this->window.pollEvent(this->ev)))
    {
      if ((this->ev.type == sf::Event::KeyPressed &&
	   this->ev.key.code == sf::Keyboard::Escape) ||
	  this->ev.type == sf::Event::Closed)
	this->quit = true;
      if (this->view == GAME)
	{
	  inet_pton(AF_INET, this->menu.getIp().c_str(), &tmp.dest.sin_addr);
	  tmp.dest.sin_family = AF_INET;
	  tmp.dest.sin_port = htons(std::stoi(this->menu.getPort()));
	  tmp.data.data[0] = this->ev.type;
	  tmp.data.data[1] = this->ev.key.code;
	  this->client->addSendPacketInList(tmp);
	}
    }
}

void		Interface::load()
{
  static int	i = 0;

  if (this->timer.getElapsedTime().asSeconds() >= 0.2)
    {
      this->window.draw(this->sprite["load" + i]);
      i = (i + 1) % 20;
      this->timer.restart();
    }
  this->window.display();
}

bool				Interface::connect()
{
  Packet		        tmp;
  int				size;
  int				port;
  std::chrono::duration<double>	elapsed;
  char				*new_room;

  auto start = std::chrono::high_resolution_clock::now();
  port = std::rand() % 65000 + 4000;
  this->client = new NetworkManager();
  if (this->client->init(CLIENT, this->menu.getIp(), port) != 0)
    return (false);
  inet_pton(AF_INET, this->menu.getIp().c_str(), &tmp.dest.sin_addr);
  tmp.dest.sin_family = AF_INET;
  try
    {
      tmp.dest.sin_port = htons(std::stoi(this->menu.getPort()));
    }
  catch (std::invalid_argument& e)
    {
      return (false);
    }
  this->client->addSendPacketInList(tmp);
  size = 0;
  while (size != -1)
    {
      this->load();
      size = this->client->getSizeReceiveList();
      if ((size = this->client->getSizeReceiveList()) > 0)
	{
	  this->packet = this->client->getReceivePacket();
	  if (this->packet.data.data[0] != -1)
	    {
	      new_room = new char[512];
	      std::memcpy(new_room, this->packet.data.data, 512);
	      this->room.setRoom(new_room);
	    }
	  else
	    size = -1;
	}
      auto finish = std::chrono::high_resolution_clock::now();
      elapsed = finish - start;
      if (elapsed.count() >= 1)
	return (false);
    }
  return (true);
}

void		Interface::callMenu()
{
  if (evSuccess)
    this->menu.event(this->ev);
  this->menu.draw(this->window);
  if (this->menu.isFinish())
    {
      if (this->connect())
	this->view = ROOM;
      else
	this->menu.setFinish(false);
    }
}

void		Interface::callRoom()
{
  if (evSuccess)
    this->room.event(this->ev, this->window);
  this->click = this->room.onClick(this->window);
  this->room.draw(this->window);
  if (this->room.isFinish() &&
      this->room.sendJoin(this->client, this->packet, this->menu.getName()))
    this->view = GAME;
}

void		Interface::callGame()
{
  std::string	eventType = "";

  /*
    recevoir les infos du serv;
    les stocker;*/

  this->game.draw(this->window, "background", 0, 0, 0);
  //les envoyer 1 par 1 a la fonction draw du Game;
  this->game.draw(this->window, "player1", 600, 100, 0);
  this->game.draw(this->window, "player_shoot", 300, 100, 0);
  eventType = this->game.getEvent(this->ev);
  //Si eventType == ESCAPE, menu option pour quitter
  //ou retourner a la selection;
  //Communiquer au serv l'event si eventType != "NONE";
}

void		Interface::loop()
{
  while (!this->quit)
    {
      this->click = false;
      this->event();
      this->window.clear(sf::Color::Black);
      switch (this->view)
	{
	case MENU:
	  this->callMenu();
	  break;
	case ROOM:
	  this->callRoom();
	  break;
	case GAME:
	  this->callGame();
	  break;
	}
      this->mouse = sf::Mouse::getPosition();
      this->win_pos = this->window.getPosition();
      this->sprite["cursor"].setPosition(this->mouse.x - this->win_pos.x,
					 this->mouse.y - this->win_pos.y);
      this->sprite["click"].setPosition(this->mouse.x - this->win_pos.x,
					this->mouse.y - this->win_pos.y);
      if (this->click)
	this->window.draw(this->sprite["click"]);
      else
	this->window.draw(this->sprite["cursor"]);
      this->window.display();
    }
}
