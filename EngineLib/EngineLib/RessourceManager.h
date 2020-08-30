#pragma once
class RessourceManager
{
	std::map<std::string, sf::Texture *> textures;
public:
	RessourceManager();
	~RessourceManager();

	sf::Texture *GetTexture(std::string path);
};

