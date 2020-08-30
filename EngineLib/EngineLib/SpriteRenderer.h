#pragma once
//#include "Engine.h"

class SpriteRenderer :
	public IComponent
{
	sf::Texture *_texture = NULL;
	std::string textureName;
	float _depth = 0;

public:
	SpriteRenderer();
	~SpriteRenderer();

	void Display(/*sf::RenderWindow *win*/);

	void SetTexture(std::string path);
	void SetTextureRepeatable(bool val);
	void SetDepth(float depth);

	//const sf::Sprite & GetSprite();

	float GetDepth();

	sf::Sprite _sprite;
	sf::IntRect rectTexture;
};

bool CompareSpriteByDepth(SpriteRenderer *s1, SpriteRenderer *s2);

