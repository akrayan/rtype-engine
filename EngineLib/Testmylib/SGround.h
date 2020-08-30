#pragma once
class SGround : public Script
{
	sf::FloatRect boundary;
public:
	float ScrollSpeed = 0.5;

	SGround();
	~SGround();

	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(Collision *col);
};

