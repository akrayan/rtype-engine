#include "Game.hh"

Game::Game()
{
}


Game::~Game()
{
}

void	Game::init_texture(std::string path)
{
	std::cout << "jinvoque " << path << std::endl;
	if (this->texture[path].loadFromFile(path))
	{
		texture[path].setRepeated(true);
		sprite[path].setTexture(texture[path]);
	}
}

void Game::init_sound(std::string path)
{
	if (sound.find(path) == sound.end())
		this->sound[path].openFromFile(path);
}

void Game::init_font(std::string path)
{
	if (fonts.find(path) == fonts.end())
		this->fonts[path].loadFromFile(path);
}

void	Game::init_texture_players()
{
  if (this->texture["player1"].loadFromFile("src/game/playerOne.png"))
    sprite["player1"].setTexture(texture["player1"]);
  if (this->texture["player2"].loadFromFile("src/game/playerTwo.png"))
    sprite["player2"].setTexture(texture["player2"]);
  if (this->texture["player3"].loadFromFile("src/game/playerThree.png"))
    sprite["player3"].setTexture(texture["player3"]);
  if (this->texture["player4"].loadFromFile("src/game/playerFour.png"))
    sprite["player4"].setTexture(texture["player4"]);
}

void	Game::init_texture_ennemies()
{
  if (this->texture["ennemy"].loadFromFile("src/game/ennemy.png"))
    sprite["ennemy"].setTexture(texture["ennemy"]);
}

void	Game::init_texture_shoot()
{
  if (this->texture["player_shoot"].loadFromFile("src/game/bullet.png"))
    sprite["player_shoot"].setTexture(texture["player_shoot"]);
}

void	Game::init(size_t width, size_t height)
{
  //taille de la fenetr
  this->width = width;
  this->height = height;

  //load la font (police)
  this->font.loadFromFile("src/Oswald.ttf");
  
  //iniatilation de toutes les textures et du sprite background
  if (this->texture["background"].loadFromFile("src/game/background.png")) {
    this->sprite["background"].setTexture(this->texture["background"]);
    this->sprite["background"].setScale(width / sprite["background"].getLocalBounds().width ,
					height / sprite["background"].getLocalBounds().height);
  }
  init_texture_players();
  init_texture_ennemies();
  init_texture_shoot();
  
  //Boolean pour savoir si le client quitte ou est déco du jeu.
  this->finish = false;
}

void	Game::draw(sf::RenderWindow &window, gameStruct stGame)
{
	sf::Text t;
	//std::cout << "le nom = " << stGame.name << std::endl;
	if (stGame.action == "clear")
	{
		window.display();
		window.clear();
		return ;
	}
	/*std::cout << "je draw = " << stGame.name << std::endl;
	std::cout << "a la position = " << stGame.x << "  " << stGame.y << std::endl;
	std::cout << "avec une taille de = " << stGame.scaleX << "  " << stGame.scaleY << std::endl;
	std::cout << "un rect de = " << stGame.rect.height << "  " << stGame.rect.left << "  " << stGame.rect.top << "  " << stGame.rect.width << "\n\n" << std::endl;
	*/
	/*if (sprite.find(stGame.name) != sprite.end())
	{
		std::cout << "je draw = " << stGame.name << std::endl;
		std::cout << "a la position = " << stGame.x << "  " << stGame.y << std::endl;
		std::cout << "avec une taille de = " << stGame.scaleX << "  " << stGame.scaleY <<std::endl;
		std::cout << "un rect de = " << stGame.rect.height << "  " << stGame.rect.left << "  " << stGame.rect.top << "  " << stGame.rect.width << "\n\n" << std::endl;
		*/
	if (stGame.action == "sprite")
	{
		if (sprite.find(stGame.name) == sprite.end())
			init_texture(stGame.name);
		sprite[stGame.name].setPosition(stGame.x, stGame.y);
		sprite[stGame.name].setRotation(stGame.rotation);
		sprite[stGame.name].setScale(stGame.scaleX, stGame.scaleY);
		sprite[stGame.name].setTextureRect(stGame.rect);
		window.draw(sprite[stGame.name]);
	}
	else if (stGame.action == "sound")
	{
		std::cout << "je dois jouer " << stGame.name << std::endl;
		init_sound(stGame.name);
		sound[stGame.name].setLoop(stGame.loop);
		sound[stGame.name].setVolume(stGame.volume);
		sound[stGame.name].play();

	}
	else if (stGame.action == "text")
	{
		//std::cout << "je dois ecrire " << stGame.text << " de taille "<< stGame.scaleX << stGame.scaleY << std::endl;
		t.setFillColor(sf::Color::White);
		init_font(stGame.name);
		t.setFont(fonts[stGame.name]);
		t.setPosition(stGame.x, stGame.y);
		t.setRotation(stGame.rotation);
		t.setScale(stGame.scaleX, stGame.scaleY);
		t.setCharacterSize(stGame.size);
		t.setString(stGame.text);
		window.draw(t);

	}
		//}
	/*std::cout << stGame.x << " " << stGame.y << " " << stGame.rotation << " " <<
		stGame.scaleX << " " << stGame.scaleY << std::endl;
	std::cout << "fin du draw" << std::endl;
	*/
}

/*
void Game::draw(sf::RenderWindow & window, gameData servInfo)
{
	sf::Sprite	sprite;

	if (servInfo.TextorTexture == true)
	{
		sprite.setTextureRect(servInfo.texture);
		sprite.setPosition(servInfo.pos.x, servInfo.pos.y);
		sprite.setScale(servInfo.scale.x, servInfo.scale.y);
		sprite.setRotation(servInfo.rot);
		window.draw(sprite);
	}
}
*/

std::string Game::getEvent(const sf::Event &e)
{
  switch (e.KeyPressed)
    {
    case sf::Keyboard::Left:
      return ("LEFT");
      break;
    case sf::Keyboard::Right:
      return ("RIGHT");
      break;
    case sf::Keyboard::Up:
      return ("UP");
      break;
    case sf::Keyboard::Down:
      return ("DOWN");
      break;
    case sf::Keyboard::Return:
      return ("ESCAPE");
      break;
    default:
      break;
    }
  return std::string("NONE");
}
