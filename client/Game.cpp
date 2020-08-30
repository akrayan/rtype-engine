#include "Game.hh"

Game::Game()
{
}


Game::~Game()
{
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
  if (this->texture["ennemy"].loadFromFile("src/game/speedship.png"))
    sprite["ennemy"].setTexture(texture["ennemy"]);
}

void	Game::init_texture_shoot()
{
  if (this->texture["player_shoot"].loadFromFile("src/game/tir.png"))
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

void	Game::draw(sf::RenderWindow &window, std::string name, int y, int x,
		   int rotation)
{
  sprite[name].setPosition(x, y);
  sprite[name].setRotation(rotation);
  window.draw(sprite[name]);
}

std::string Game::getEvent(const sf::Event &e)
{
  /*  switch (e.KeyPressed)
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
      }*/
  (void)e;
  return std::string("NONE");
}
