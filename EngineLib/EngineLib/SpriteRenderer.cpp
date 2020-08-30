#include "Engine.h"

SpriteRenderer::SpriteRenderer()
{
	//_texture = new sf::Texture();
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Display(/*sf::RenderWindow * win*/)
{
	
	_sprite.setPosition((gameobject->transform.GetPosition()));
	_sprite.setScale((gameobject->transform.GetScale()));
	_sprite.setRotation(gameobject->transform.GetRotation());
	_sprite.setTextureRect(rectTexture);
	//win->draw(_sprite);
	Game->GameRoom->sendAll("sprite;"
		+ textureName + ";"
		+ std::to_string(_sprite.getPosition().x) + ";" 
		+ std::to_string(_sprite.getPosition().y) + ";"
		+ std::to_string(_sprite.getRotation()) + ";"
		+ std::to_string(_sprite.getScale().x) + ";"
		+ std::to_string(_sprite.getScale().y) + ";"
		+ std::to_string(_sprite.getTextureRect().height) + ";"
		+ std::to_string(_sprite.getTextureRect().left) + ";"
		+ std::to_string(_sprite.getTextureRect().top) + ";"
		+ std::to_string(_sprite.getTextureRect().width) + ";"
	);

}

void SpriteRenderer::SetTexture(std::string path)
{
	textureName = path;
	_texture = Game->ressourceManager->GetTexture(path);
	if (_texture != NULL) _sprite.setTexture(*_texture);
	rectTexture = _sprite.getTextureRect();
	//_sprite.setOrigin(rectTexture.width / 2, rectTexture.height / 2);*/
}

void SpriteRenderer::SetTextureRepeatable(bool val)
{
	_texture->setRepeated(val);
}

void SpriteRenderer::SetDepth(float depth)
{
	_depth = depth;
}
/*
const sf::Sprite & SpriteRenderer::GetSprite()
{
	return _sprite;
}*/

float SpriteRenderer::GetDepth()
{
	return _depth;
}

bool CompareSpriteByDepth(SpriteRenderer * s1, SpriteRenderer * s2)
{
	return (s1->GetDepth() < s2->GetDepth());
}
