#pragma once
class SLevel : public Script
{
	float BGMvol = 30;
	float timeBetweenWave = 4;
	sf::Clock Timer1;
	sf::Clock Timer2;

	bool firstCall = true;
	TextRenderer *ScoreText = NULL;
	GameObject *LastGround = NULL;

public:

	int Score = 0;
	SLevel();
	~SLevel();

	virtual void Start();
	virtual void Update();
	virtual void OnClientConnect(int id);
	void createMob();
};

