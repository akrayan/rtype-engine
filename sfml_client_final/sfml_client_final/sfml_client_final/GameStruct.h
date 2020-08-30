#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct gameStruct
{
	std::string action;
	std::string	name;
	std::string	text;
	int volume;
	bool loop;
	int size;
	float		y;
	float		x;
	float		rotation;
	float		scaleX;
	float		scaleY;
	sf::IntRect rect;
};