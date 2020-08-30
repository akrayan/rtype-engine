#pragma once
//#include "Engine.h"
class Scene;

class GameManager
{
	
	std::vector<Client *> tabcl;
	std::string _defaultScene;
	SceneLoader *loader;
	float _fps = 60;
	sf::Vector2i resolution;
	sf::Clock _clock;
	//sf::RenderWindow *_window;
	std::map<std::string, Script *(*)()> *listScript;



	void DisplayAll();

	void UpdateAll();

	void CallConnect(int id);

	void StartAll();


public:
	BitArray bitArray;
	EventNetwork Input[4];
	Scene *scene;
	SoundManager *Sound;
	RessourceManager *ressourceManager;
	Room *GameRoom;
	//NetworkManager	*networkManager;


	GameManager(RessourceManager *rsc, Room *net, std::string defscene, std::map<std::string, Script *(*)()> *mapScript);
	~GameManager();

	float GetFPS();
	void LoadScene(std::string path);
	void AddClient(Client *);
	void ReceivePacket(sf::Event::EventType, sf::Keyboard::Key, sockaddr_in id);

	void GameLoop();
};
