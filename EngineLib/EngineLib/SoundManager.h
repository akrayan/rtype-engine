#pragma once
class SoundManager
{
	GameManager *Game;
	std::map<sf::String, sf::Music *> Sounds;
public:
	SoundManager(GameManager *gm);
	~SoundManager();
	
	void play(std::string path, bool loop = false, float volume = 100);
	void playForOne(int id, std::string path, bool loop = false, float volume = 100);

};

