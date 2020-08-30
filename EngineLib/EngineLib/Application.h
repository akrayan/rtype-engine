#pragma once

template<typename T> Script * createInstance() { return new T; }

class NetworkManager;

class Application
{
	//std::string		scene;
	bool			game_on;
	NetworkManager	*network_udp;
	std::vector<Client*>	clients;
	std::vector<Room*>	rooms;

	RessourceManager ressourceManager;
	GameManager *Game;
	std::map<std::string, Script *(*)()> listScript;
	std::string defaultScene;

public:
	Application();
	~Application();

	void initServer();
	void runApp();

	template<typename T> void AddAScript(std::string scriptName)
	{
		listScript[scriptName] = &createInstance<T>;
	}

	bool SetDefaultScene(std::string scenePath);
	void SetResolution(sf::Vector2i res);
	void SetResolution(int x, int y);

	void Launch();

	Client	*getClient(Packet const &);
	void		handleRoomCommand(Packet &, Client *);
	void		handleGameCommand(Packet &, Client *);
	void		findNextString(char *, size_t &);
};
