#pragma once
class SBullet : public Script
{
	float LifeTime = 2;
	sf::Clock cl;

public:
	int damage = 1;
	float BulletSpeed = 40;


	SBullet();
	~SBullet();


	virtual void Update();
	virtual void OnCollisionEnter(Collision * col);
};

