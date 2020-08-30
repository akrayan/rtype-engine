#pragma once
class SPlayer : public Script
{
	int Hp = 10;
	float Speed = 5;
	float DelayShoot = 0.3f;
	float ChargeTime = 1;
	float timer = 0;
	sf::Clock cl;
	sf::Clock cl2;
	float progresShoot = 0;
	SpriteRenderer *SpriteBar = NULL;
	int widthBar;
	bool firstTime = true;
	sf::IntRect boundary;
	sf::FloatRect playerboundary;

public:
	int idClient = 0;

	SPlayer();
	~SPlayer();

	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(Collision *col);
	void CreateBullet(int type);
};

