//
// Animation.hh for  in /home/belugum/rendu/cpp_rtype/client
//
// Made by Maxime Beluguet
// Login   <belugum@epitech.net>
//
// Started on  Wed Jan 17 15:08:25 2018 Maxime Beluguet
// Last update Wed Jan 17 21:26:54 2018 Maxime Beluguet
//

#ifndef ANIMATION_HH_
# define ANIMATION_HH_

# include <iostream>
# include <SFML/Audio.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>


class	Animation
{
  sf::Texture			*texture;
  sf::Sprite			*sprite;
  int				nb_x;
  int				nb_y;

public:
  Animation();
  ~Animation();
  void	load(std::string, int, int, int, int);
  sf::Sprite	const &getAnim(unsigned int nb);
};

#endif
