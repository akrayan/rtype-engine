#include "Engine.h"



RessourceManager::RessourceManager()
{
}


RessourceManager::~RessourceManager()
{
}

sf::Texture * RessourceManager::GetTexture(std::string path)
{
	sf::Texture *tex;

	//std::cout << "yooooo !" << std::endl;
	if (textures.find(path) == textures.end())
	{
		tex = new sf::Texture();
		tex->loadFromFile(path);
		textures[path] = tex;
		return tex;
	}
	return textures[path];
}
