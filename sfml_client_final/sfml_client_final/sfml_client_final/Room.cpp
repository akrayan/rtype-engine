
//
// Room.cpp for Room in /home/shiba/shiba/rendu/tek3/cpp/cpp_rtype/client
//
// Made by shiba
// Login   <zita.cheng@epitech.eu>
//
// Started on  Fri Jan 12 23:26:35 2018 shiba
// Last update Sun Jan 28 19:08:57 2018 shiba
//

#include "Room.hh"


Room::Room()
{
}

void		Room::buttonTexture(int x, int y, const std::string &name)
{
  if (this->texture["button"].loadFromFile("src/button.png"))
    {
      this->sprite[name].setTexture(this->texture["button"]);
      this->sprite[name].setScale(0.20, 0.16);
      this->sprite[name].setPosition(x, y);
    }
}

void		Room::setButton(int x, int y, const std::string &name)
{
  if (this->texture["but"].loadFromFile("src/but.png"))
    {
      this->sprite[name].setTexture(this->texture["but"]);
      this->sprite[name].setScale(0.5, 0.5);
      this->sprite[name].setPosition(x, y);
    }
}

void		Room::setTitle(int x, int y, const std::string &index,
			       const std::string &title, int s)
{
  this->text[index].setFont(this->font["button"]);
  this->text[index].setString(title);
  this->text[index].setCharacterSize(s);
  this->text[index].setPosition(x, y);
  this->text[index].setFillColor(sf::Color(213, 183, 64));
}

void		Room::setText(const std::string &name, int x, int y)
{
  this->text[name].setFont(this->font["input"]);
  this->text[name].setCharacterSize(20);
  this->text[name].setPosition(x, y);
  this->text[name].setFillColor(sf::Color::Black);
}

void		Room::setBar(const std::string &name, int x, int y)
{
  this->sprite[name].setTexture(this->texture["input"]);
  this->sprite[name].setScale(0.5, 1);
  this->sprite[name].setPosition(x, y);
}

void		Room::setBase()
{
  //Background
  if (this->texture["bk"].loadFromFile("src/fly.png"))
    {
      this->sprite["bk"].setTexture(this->texture["bk"]);
      this->sprite["bk"].setScale(this->width / this->sprite["bk"].getLocalBounds().width,
				  this->height / this->sprite["bk"].getLocalBounds().height);
    }

  //Buttons
  this->buttonTexture(430, 150, "button0");
  this->buttonTexture(430, 350, "button1");

  //Text
  this->font["button"].loadFromFile("src/two.ttf");
  this->setTitle(570, 235, "join", "Join Game", 45);
  this->setTitle(550, 435, "create", "Create Game", 45);
}

void		Room::initCreate()
{
  this->setButton(490, 450, "back");
  this->setButton(690, 450, "valid");
  this->setTitle(570, 490, "valid", "Back", 25);
  this->setTitle(770, 490, "back", "Valid", 25);

  this->font["input"].loadFromFile("src/Oswald.ttf");
  this->setText("name", 490, 235);
  this->setText("pass", 490, 335);
  this->setText("room", 490, 200);
  this->text["room"].setString("Name :");
  this->text["room"].setFillColor(sf::Color::White);
  this->setText("password", 490, 300);
  this->text["password"].setString("Password (Optional) :");
  this->text["password"].setFillColor(sf::Color::White);
  if (this->texture["input"].loadFromFile("src/bar.png"))
    {
      this->setBar("name", 470, 200);
      this->setBar("pass", 470, 300);
    }
  if (this->texture["square"].loadFromFile("src/square.png"))
    {
      this->sprite["square"].setTexture(this->texture["square"]);
      this->sprite["square"].setScale(1.15, 0.5);
      this->sprite["square"].setColor(sf::Color(255, 255, 255, 100));
      this->sprite["square"].setPosition(400, 180);
    }
}

void	        Room::joinText(const std::string &name, int x, int y,
			       const std::string &text)
{
  this->text[name].setFont(this->font["input"]);
  this->text[name].setCharacterSize(20);
  this->text[name].setPosition(x, y);
  this->text[name].setFillColor(sf::Color::White);
  this->text[name].setString(text);
}

void	        Room::emptyRect(const std::string &id, int x, int y)
{
  this->rect[id].setPosition(x, y);
  this->rect[id].setFillColor(sf::Color(35, 121, 178, 0));
  this->rect[id].setOutlineThickness(1);
  this->rect[id].setOutlineColor(sf::Color(255, 255, 255, 200));
}

bool		Room::sendJoin(NetworkManager *client, Packet p,
			       const std::string &pseudo)
{
  int		size;

  std::memset(p.data.data, 0, sizeof(p.data.data));
  if (this->currentInt == JOIN)
    {
      if (*(this->rooms[this->line] + 3) == 4)
	{
	  this->finish = false;
	  return (false);
	}
      p.data.data[0] = 1;
      *((short*)(p.data.data + 1)) = *((short*)(this->rooms[this->line] + 1));
      std::memcpy(p.data.data + 3, this->password.c_str(), this->password.size());
      std::memcpy(p.data.data + 4 + this->password.size(),
		  pseudo.c_str(), pseudo.size());
    }
  else
    {
      p.data.data[0] = 2;
      std::memcpy(p.data.data + 1, this->name.c_str(), this->name.size());
      std::memcpy(p.data.data + 2 + this->name.size(),
		  this->password.c_str(), this->password.size());
      std::memcpy(p.data.data + 3 + this->name.size() + this->password.size(),
		  pseudo.c_str(), pseudo.size());
    }
  client->addSendPacketInList(p);
  size = client->getSizeReceiveList();
  while (size > 0)
    {
      p = client->getReceivePacket();
      if (p.data.data[0] == -1)
	this->finish = false;
      else
	this->finish = true;
      size -= 1;
    }
  return (this->finish);
}

void		Room::initJoin()
{
  this->rect["bk"].setSize(sf::Vector2f(1000, 550));
  this->rect["bk"].setPosition(180, 100);
  this->rect["bk"].setFillColor(sf::Color(35, 121, 178, 100));
  this->rect["bk"].setOutlineThickness(1);
  this->rect["bk"].setOutlineColor(sf::Color(255, 255, 255, 200));

  this->rect["rooms"].setSize(sf::Vector2f(560, 420));
  this->emptyRect("rooms", 210, 150);
  this->rect["players"].setSize(sf::Vector2f(340, 360));
  this->emptyRect("players", 790, 150);
  this->emptyRect("choose", 210, 160);
  this->rect["choose"].setSize(sf::Vector2f(540, 19));

  this->joinText("select", 210, 120, "All rooms :");
  this->joinText("showPlayer", 790, 120, "Players in this room :");

  this->joinText("P1", 800, 160, "");
  this->joinText("P0", 800, 190, "");
  this->joinText("P2", 800, 220, "");
  this->joinText("P3", 800, 250, "");

  this->setTitle(570, 690, "back1", "Back", 25);
  this->setTitle(770, 690, "join1", "Join", 25);
  this->setButton(690, 650, "back1");
  this->setButton(490, 650, "join1");

  if (this->texture["left"].loadFromFile("src/left.png"))
    {
      this->sprite["left"].setTexture(this->texture["left"]);
      this->sprite["left"].setScale(0.45, 0.4);
      this->sprite["left"].setPosition(870, 530);
    }

  if (this->texture["right"].loadFromFile("src/right.png"))
    {
      this->sprite["right"].setTexture(this->texture["right"]);
      this->sprite["right"].setScale(0.45, 0.4);
      this->sprite["right"].setPosition(970, 530);
    }
  this->sprite["pass_join"] = this->sprite["pass"];
  this->sprite["pass_join"].setPosition(480, 570);
  this->text["pass_join"] = this->text["showPlayer"];
  this->text["pass_join"].setString("Password :");
  this->text["pass_join"].setPosition(400, 605);
  this->setText("password_join", 500, 605);
}

void		Room::init(size_t w, size_t h)
{
  this->buttonId = 0;
  this->currentInt = MENU;
  this->index = 0;
  this->currentInput = NAME;
  this->finish = false;
  this->width = w;
  this->height = h;
  this->name.clear();
  this->password.clear();
  this->page = 0;
  this->max_p = 0;
  this->max_y = 0;
  this->line = 0;

  this->setBase();
  this->initCreate();
  this->initJoin();
}

Room::~Room()
{

}

void            Room::completeWord(char c)
{
  if (c == 8)
    {
      if (this->currentInput == NAME && this->name.length() > 0)
	this->name.erase(this->name.length() - 1);
      else if (this->password.length() > 0)
	this->password.erase(this->password.length() - 1);
    }
  else if (c != 8)
    {
      if (this->currentInput == NAME &&
	  this->name.length() <= 50)
	this->name += c;
      else if (this->password.length() <= 50)
	this->password += c;
      if (this->currentInt == JOIN)
	this->password += c;
    }
  this->text["name"].setString(this->name);
  this->text["pass"].setString(this->password);
  this->text["password_join"].setString(this->password);
}

void		Room::menuEvent(const sf::Event &e)
{
  std::string	str;

  if (this->currentInt == MENU &&
      (e.key.code == sf::Keyboard::Up ||
       e.key.code == sf::Keyboard::Down))
    {
      str = "button" + std::to_string(this->buttonId);
      this->sprite[str].setColor(sf::Color::White);
      this->buttonId = (this->buttonId + 1) % 2;
      str = "button" + std::to_string(this->buttonId);
      this->sprite[str].setColor(sf::Color(255, 20, 20));
    }
  if (e.key.code == sf::Keyboard::Return && this->currentInt == MENU)
    this->currentInt = this->buttonId == 0 ? JOIN : CREATE;
}

void		Room::calculLine(sf::Vector2i mouse)
{
  int		px;
  int		l;

  l = -1;
  px = 162;
  while (px <= mouse.y)
    {
      px += 22;
      ++l;
    }
  this->line = l;
}

void	        Room::mouseEvent(const sf::Event &e, sf::RenderWindow &win)
{
  sf::Vector2i	mouse;
  sf::Vector2i	win_pos;

  if (e.type == sf::Event::MouseButtonPressed &&
      e.mouseButton.button == sf::Mouse::Left)
    {
      mouse = sf::Mouse::getPosition();
      win_pos = win.getPosition();
      mouse.x -= win_pos.x;
      mouse.y -= win_pos.y;
      if (currentInt == CREATE && mouse.x >= 520 && mouse.y >= 480 &&
	  mouse.x <= 680 && mouse.y <= 540)
	{
	  this->password.clear();
	  this->currentInt = MENU;
	}
      else if (currentInt == CREATE && mouse.x >= 720 && mouse.y >= 480 &&
	       mouse.x <= 880 && mouse.y <= 540 && this->name.length() > 0)
	this->finish = true;
      else if (currentInt == JOIN && mouse.x >= 510 && mouse.y >= 685 &&
	       mouse.x <= 680 && mouse.y <= 735)
	{
	  this->password.clear();
	  this->currentInt = MENU;
	}
      else if (currentInt == JOIN && mouse.x >= 720 && mouse.y >= 685 &&
	       mouse.x <= 880 && mouse.y <= 735 && this->rooms.size() > 0)
	this->finish = true;
      else if (currentInt == MENU && mouse.x >= 470 && mouse.y >= 200 &&
	  mouse.x <= 910 && mouse.y <= 310)
	this->currentInt = JOIN;
      else if (currentInt == MENU && mouse.x >= 470 && mouse.y >= 400 &&
	  mouse.x <= 910 && mouse.y <= 510)
	this->currentInt = CREATE;
      else if (currentInt == JOIN && mouse.x >= 970 && mouse.y >= 530 &&
	       mouse.x <= 1020 && mouse.y <= 580 &&
	       this->page < this->max_p)
	this->page += 1;
      else  if (currentInt == JOIN && mouse.x >= 870 && mouse.y >= 530 &&
		mouse.x <= 920 && mouse.y <= 580 && this->page > 0)
	this->page -= 1;
      else  if (currentInt == JOIN && mouse.x >= 220 && mouse.y >= 160 &&
		mouse.x <= 740 && mouse.y <= this->max_y)
	this->calculLine(mouse);
    }
}

void		Room::event(const sf::Event &e, sf::RenderWindow &win)
{
  std::string	name;

  name = "button" + std::to_string(this->buttonId);
  if (e.type == sf::Event::KeyPressed)
    {
      this->menuEvent(e);
      if (this->currentInt == CREATE &&
	  e.key.code == sf::Keyboard::Tab)
	{
	  if (this->currentInput == NAME)
	    this->currentInput = PASS;
	  else
	    this->currentInput = NAME;
	}
    }
  if (e.type == sf::Event::TextEntered &&
      ((e.text.unicode < 128 &&
	e.text.unicode >= 32) || e.text.unicode == 8))
    this->completeWord(static_cast<int>(e.text.unicode));
  this->mouseEvent(e, win);
  if (e.key.code == sf::Keyboard::Return &&
      ((this->currentInt == CREATE && this->name.length() > 0) ||
       (this->currentInt == JOIN && this->rooms.size() > 0)))
    this->finish = true;
}

void		Room::drawMenu(sf::RenderWindow &win)
{
  win.draw(this->sprite["button0"]);
  win.draw(this->sprite["button1"]);
  win.draw(this->text["join"]);
  win.draw(this->text["create"]);
}

void		Room::listRoom(sf::RenderWindow &win)
{
  size_t	i;
  int		y;
  int	        cpt;
  char		nb;
  int		p;
  std::string	player;

  i = 0;
  y = 0;
  for (auto it = this->rooms.begin(); it != this->rooms.end(); ++it)
    {
      this->text["P0"].setString("");
      this->text["P1"].setString("");
      this->text["P2"].setString("");
      this->text["P3"].setString("");
      if (i == this->line)
	{
	  this->rect["choose"].setPosition(220, 162 + y);
	  nb = (*it)[3];
	  p = -2;
	  cpt = 3;
	  while (++p < nb)
	    {
	      player.clear();
	      while ((*it)[++cpt])
		player += (*it)[cpt];
	      if ( p >= 0)
		{
		  this->text["P" + std::to_string(p)].setString(player);
		  win.draw(this->text["P" + std::to_string(p)]);
		}
	    }
	}
      this->joinText(std::to_string(*((short*)((*it) + 1))), 220, 160 + y,
		     (*it) + 4);
      y += 22;
      win.draw(this->text[std::to_string(*((short*)((*it) + 1)))]);
      i += 1;
    }
  this->max_y = 160 + y;
  if (this->rooms.size() > 0)
    win.draw(this->rect["choose"]);
}

void		Room::drawJoin(sf::RenderWindow &win)
{
  win.draw(this->rect["bk"]);
  win.draw(this->sprite["back1"]);
  win.draw(this->sprite["join1"]);
  win.draw(this->text["back1"]);
  win.draw(this->text["join1"]);
  win.draw(this->rect["rooms"]);
  win.draw(this->rect["players"]);
  win.draw(this->text["select"]);
  win.draw(this->text["showPlayer"]);
  win.draw(this->sprite["left"]);
  win.draw(this->sprite["right"]);
  this->listRoom(win);
  win.draw(this->text["pass_join"]);
  win.draw(this->sprite["pass_join"]);
  win.draw(this->text["password_join"]);
}

void		Room::drawCreate(sf::RenderWindow &win)
{
  win.draw(this->sprite["square"]);
  win.draw(this->text["room"]);
  win.draw(this->text["password"]);
  win.draw(this->sprite["name"]);
  win.draw(this->sprite["pass"]);
  win.draw(this->text["name"]);
  win.draw(this->text["pass"]);
  win.draw(this->sprite["back"]);
  win.draw(this->sprite["valid"]);
  win.draw(this->text["back"]);
  win.draw(this->text["valid"]);
}

void		Room::draw(sf::RenderWindow &win)
{
  win.draw(this->sprite["bk"]);
  switch (this->currentInt)
    {
    case MENU:
      this->drawMenu(win);
      break;
    case CREATE:
      this->drawCreate(win);
      break;
    case JOIN:
      this->drawJoin(win);
      break;
    }
}

std::string	Room::getName() const
{
  return (this->name);
}

std::string	Room::getPassword() const
{
  return (this->password);
}

bool		Room::onClick(sf::RenderWindow &win)
{
  sf::Vector2i	mouse;
  sf::Vector2i	win_pos;

  mouse = sf::Mouse::getPosition();
  win_pos = win.getPosition();
  mouse.x -= win_pos.x;
  mouse.y -= win_pos.y;
  if (currentInt == CREATE && mouse.x >= 520 && mouse.y >= 480 &&
      mouse.x <= 680 && mouse.y <= 540)
    return (true);
  if (currentInt == CREATE && mouse.x >= 720 && mouse.y >= 480 &&
      mouse.x <= 880 && mouse.y <= 540)
    return (true);
  if (currentInt == JOIN && mouse.x >= 510 && mouse.y >= 685 &&
      mouse.x <= 680 && mouse.y <= 735)
    return (true);
  if (currentInt == JOIN && mouse.x >= 720 && mouse.y >= 685 &&
      mouse.x <= 880 && mouse.y <= 735)
    return (true);
  if (currentInt == JOIN && mouse.x >= 970 && mouse.y >= 530 &&
      mouse.x <= 1020 && mouse.y <= 580)
    return (true);
  if (currentInt == JOIN && mouse.x >= 870 && mouse.y >= 530 &&
      mouse.x <= 920 && mouse.y <= 580)
    return (true);
  else  if (currentInt == JOIN && mouse.x >= 220 && mouse.y >= 160 &&
	    mouse.x <= 740 && mouse.y <= this->max_y)
    return (true);
  if (currentInt == MENU && mouse.x >= 470 && mouse.y >= 200 &&
      mouse.x <= 910 && mouse.y <= 310)
    {
      this->sprite["button1"].setColor(sf::Color::White);
      this->sprite["button0"].setColor(sf::Color(255, 20, 20));
      return (true);
    }
  if (currentInt == MENU && mouse.x >= 470 && mouse.y >= 400 &&
      mouse.x <= 910 && mouse.y <= 510)
    {
      this->sprite["button0"].setColor(sf::Color::White);
      this->sprite["button1"].setColor(sf::Color(255, 20, 20));
      return (true);
    }
  return (false);
}

bool		Room::isFinish() const
{
  return (this->finish);
}

void		Room::setRoom(char *room)
{
  this->rooms.push_back(room);
}
