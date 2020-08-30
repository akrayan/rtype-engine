#include "Engine.h"



SoundManager::SoundManager(GameManager *gm)
{
	Game = gm;

}


SoundManager::~SoundManager()
{
}

void SoundManager::play(std::string path, bool loop, float volume)
{
	std::string loopstr;

	if (loop)
		loopstr = "true";
	else
		loopstr = "false";
	Game->GameRoom->sendAll("sound;"
		+ path + ";"
		+ std::to_string(volume) + ";"
		+ loopstr + ";"
	);
}

void SoundManager::playForOne(int id, std::string path, bool loop, float volume)
{
	std::string loopstr;

	if (loop)
		loopstr = "true";
	else
		loopstr = "false";
	Game->GameRoom->sendToOne("sound;"
		+ path + ";"
		+ std::to_string(volume) + ";"
		+ loopstr + ";"
	, id);
}

