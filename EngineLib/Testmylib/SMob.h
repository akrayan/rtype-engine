#pragma once
class SMob : public Script
{
	//sf::Clock cl;
	float Xspeed = 2;
	float Yspeed = 0.5;
	float Ymax = 40;
	float Yorigin;
	float Yvector = 1;
	float LifeTime = 10;

	sf::Clock cl;

	SLevel *Level;

public:

    int HP = 3;

	SMob();
	~SMob();

	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(Collision *col);
};

