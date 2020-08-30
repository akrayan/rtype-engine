#pragma once
//#include "Engine.h"

class GameObject;
class GameManager;
class Collider;
struct Collision;

class TransformObject
{
	sf::Vector2f position{ 0, 0 };
	sf::Vector2f scale = { 1, 1};
	float rotation = 0;
	GameObject * gameobject;
	GameManager * gamemanager;
	bool one = true;

	Collision * Collide(Collider * C, std::list<Collider*> list, Collision * col);

public:
	//TransformObject() {};
	TransformObject(GameManager * gmref , GameObject * goref);
	~TransformObject();
	
	void SetPosition(sf::Vector2f pos);
	void SetPosition(float x, float y);
	void SetScale(sf::Vector2f pos);
	void SetScale(float x, float y);
	void SetRotation(float angle);
	
	float GetRotation();
	sf::Vector2f GetPosition();
	float GetPositionX();
	float GetPositionY();
	sf::Vector2f GetScale();
	float GetScaleX();
	float GetScaleY();

	void Rotate(float angle);
	void Translate(float x, float y);
	void Translate(sf::Vector2f pos);
};

sf::Vector2f VectorNormalize(sf::Vector2f v, int *iteration);

