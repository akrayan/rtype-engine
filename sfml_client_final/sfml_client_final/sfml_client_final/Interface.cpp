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
  this->width = 1024;
  this->height = 720;
  this->window.create(sf::VideoMode(this->width, this->height), "RType");
  this->window.setMouseCursorVisible(false);
  this->texture["cursor"].loadFromFile("src/cursor1.png");
  this->sprite["cursor"].setTexture(this->texture["cursor"]);
  this->sprite["cursor"].setScale(1, 1);
  this->texture["click"].loadFromFile("src/cursor2.png");
  this->sprite["click"].setTexture(this->texture["click"]);
  this->sprite["click"].setScale(1, 1);
  if (this->music.openFromFile("src/intro.ogg"))
    {
	  this->music.setVolume(15);
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
	 if (this->view == GAME && (this->ev.type == sf::Event::KeyPressed || this->ev.type == sf::Event::KeyReleased))
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
  {
	  this->music.stop();
	  this->view = GAME;
  }
}

void		Interface::callGame()
{
  std::string	eventType = "";
  gameStruct	stGame;

  //this->game.draw(this->window, "background", 0, 0, 0, 1, 1);
  while (client->getSizeReceiveList() > 0) {
	  packet = client->getReceivePacket();
	  
	  stGame = this->fillGameStruct(packet);
	  this->game.draw(this->window, stGame);
	  //std::cout << client->getSizeReceiveList() << std::endl;
	  //this->game.draw(this->window, "player_shoot", 300, 100, 0);
  }
  //std::cout << "\n\nyoupi je sors\n\n" << std::endl;
 /* eventType = this->game.getEvent(this->ev);
  std::strcpy(packet.data.data, eventType.c_str());
  client->addSendPacketInList(packet);
  */
 }

gameStruct	Interface::fillGameStruct(Packet packet)
{
	gameStruct	stGame;
	std::string	str(packet.data.data);
	int			last;
	int			first = 0;
	
	//std::cout << str << std::endl;
	if ((last = str.find(';', 0)) != std::string::npos)
	{
		stGame.action = (str.substr(first, last - first));
		if (stGame.action == "clear")
			return stGame;
		if (stGame.action == "sprite")
		{
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.name = str.substr(first, last - first);
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.x = std::stof(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.y = std::stof(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rotation = std::stof(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.scaleX = std::stof(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.scaleY = std::stof(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rect.height = std::stoi(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rect.left = std::stoi(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rect.top = std::stoi(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rect.width = std::stoi(str.substr(first, last - first));
		}
		else if (stGame.action == "sound")
		{
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.name = str.substr(first, last - first);
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.volume = std::stoi(str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.loop = str.substr(first, last - first) == "true";
		}
		else if (stGame.action == "text")
		{
			
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.name = str.substr(first, last - first);
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.text = (str.substr(first, last - first));
			first = last + 1;
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.size = std::stoi(str.substr(first, last - first));
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.x = std::stof(str.substr(first, last - first));
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.y = std::stof(str.substr(first, last - first));
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.rotation = std::stof(str.substr(first, last - first));
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.scaleX = std::stof(str.substr(first, last - first));
			if ((last = str.find(';', first)) != std::string::npos)
				stGame.scaleY = std::stof(str.substr(first, last - first));
		}
	}

	//std::cout << "end serialization" << std::endl;
	return (stGame);
}

void		Interface::loop()
{
  while (!this->quit)
    {
      this->click = false;
      this->event();
      if (view != GAME) this->window.clear(sf::Color::Black);
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
      if (view != GAME) this->window.display();
    }
}
