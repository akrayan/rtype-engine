#include "Header.h"



SScroll::SScroll()
{
	
}


SScroll::~SScroll()
{
}

void SScroll::Update()
{
	float speed = 3;
	S = gameobject->GetComponent<SpriteRenderer>();
	sf::IntRect rect = S->_sprite.getTextureRect();
	
	S->rectTexture.left = rect.left = rect.left >= rect.width ? 0 : rect.left + 3;
	/*rect.left = rect.left >= rect.width ? 0 : rect.left + 3;
	S->_sprite.setTextureRect(rect);
	*/
}
