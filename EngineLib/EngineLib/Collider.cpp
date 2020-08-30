#include "Engine.h"

bool contain(std::list<std::string> l, std::string str)
{
	auto it = l.begin();

	while (it != l.end())
	{
		if (*it == str)
		{
			return true;
		}
		it++;
	}
	return false;
}

Collider::Collider()
{
}


Collider::~Collider()
{
}

Collision * Collider::DetectByPixel(SpriteRenderer *Sr1, SpriteRenderer *Sr2, BitArray *bitArray)
{
	Collision *col;
	sf::Sprite S1 = Sr1->_sprite;
	sf::Sprite S2 = Sr2->_sprite;

	sf::FloatRect Intersection;
	if (S1.getGlobalBounds().intersects(S2.getGlobalBounds(), Intersection)) {
		sf::IntRect O1SubRect = S1.getTextureRect();
		sf::IntRect O2SubRect = S2.getTextureRect();

		sf::Uint8* mask1 = bitArray->GetMask(S1.getTexture());
		sf::Uint8* mask2 = bitArray->GetMask(S2.getTexture());

		for (float i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
			for (float j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

				sf::Vector2f o1v = S1.getInverseTransform().transformPoint(i, j);
				sf::Vector2f o2v = S2.getInverseTransform().transformPoint(i, j);

				if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
					o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
					o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

					if (bitArray->GetPixel(mask1, S1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > 100 &&
						bitArray->GetPixel(mask2, S2.getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > 100)
					{
						col = new Collision();
						col->Ox = i;
						col->Oy = j;
						return col;
					}

				}
			}
		}
	}
	return (NULL);
}

Collision * Collider::DetectCollisionWith(Collider * other, BitArray *bitArray)
{
	Collision *col = NULL;
	SpriteRenderer *Sr1, *Sr2;
	bool test = false;

	auto it = ignoreCollisionWith.begin();
	while (it != ignoreCollisionWith.end())
	{

		if (*it == other->gameobject->GetTag())
		{
			test = true;
		}
		it++;
	}
	if (test)//contain(ignoreCollisionWith, other->gameobject->GetTag()))
		return col;

	Sr1 = gameobject->GetComponent<SpriteRenderer>();
	Sr2 = other->gameobject->GetComponent<SpriteRenderer>();

	if (Sr1 != NULL && Sr2 != NULL)
	{
		return DetectByPixel(Sr1, Sr2, bitArray);
	}
	return NULL;
}

bool Collider::IsInCollisionWith(Collider * c)
{
	auto it = InCollisionWith.begin();
	while (it != InCollisionWith.end())
	{
		if ((*it) == c)
			return (true);
		it++;
	}
	return false;
}

void Collider::AddTagIgnore(std::string tag)
{
	bool test = false;
	std::list<std::string>::iterator it = ignoreCollisionWith.begin();

	while (it != ignoreCollisionWith.end())
	{
		if (*it == tag)
		{
			test = true;
		}
		it++;
	}
	if (!test)//!contain(ignoreCollisionWith, tag))
	{
		ignoreCollisionWith.push_back(tag);
	}

}
