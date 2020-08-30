//
// Animation.cpp for  in /home/belugum/rendu/cpp_rtype/client
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Wed Jan 17 17:44:52 2018 Maxime Beluguet
// Last update Sun Jan 28 20:15:57 2018 Maxime Beluguet
//

#include "Animation.hh"

Animation::Animation():texture(nullptr),sprite(nullptr),nb_x(-1),nb_y(-1)
{
  texture = new sf::Texture;
  sprite = new sf::Sprite;
}

void	Animation::load(std::string name, int nb_x, int nb_y, int x_pos, int y_pos)
{
  this->nb_x = nb_x;
  this->nb_y = nb_y;
  if (!texture->loadFromFile(name))
    {
      std::cerr << "Error ctor animation " << name << std::endl;
      nb_x = -1;
      nb_y = -1;
    }
  else
    {
      sprite->setTexture(*texture);
    }
  sprite->setPosition(x_pos, y_pos);
}

Animation::~Animation()
{
  delete texture;
  delete sprite;
}

sf::Sprite	const &Animation::getAnim(unsigned int nb)
{
  if (nb_x > 0 && nb_y > 0)
    {
      nb = nb % (nb_x * nb_y);
      std::cout << nb << std::endl;
      sprite->setTextureRect(sf::Rect<int>((int)((nb % nb_x) * texture->getSize().x / nb_x),
					   (int)((nb / nb_x) * texture->getSize().y / nb_y),
					   (int)(texture->getSize().x / nb_x),
					   (int)(texture->getSize().y / nb_y)));
    }
  return (*sprite);
}
