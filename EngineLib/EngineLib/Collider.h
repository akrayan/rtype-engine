#pragma once
//#include "IComponent.h"

typedef struct Collision {
	float Ox;
	float Oy;
	GameObject *other;
} Collision;

class Collider :
	public IComponent
{
	std::list<std::string> ignoreCollisionWith;

	Collision * DetectByPixel(SpriteRenderer * Sr1, SpriteRenderer * Sr2, BitArray * bitArray);
public:
	bool IsTrigger = false;
	std::list<Collider *> InCollisionWith;

	Collider();
	~Collider();

	Collision *DetectCollisionWith(Collider *other, BitArray *bitArray);
	bool IsInCollisionWith(Collider *c);

	void AddTagIgnore(std::string tag);
};

