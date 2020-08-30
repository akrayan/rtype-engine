#include "Engine.h"

GameManager::GameManager(RessourceManager * rsc, Room *net, std::string defscene, std::map<std::string, Script*(*)()> *mapScript)
{

	ressourceManager = rsc;
	GameRoom = net;
	//srand(time(NULL));
	//	_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML works!");
	listScript = mapScript;
	_defaultScene = defscene;
	loader = new SceneLoader(this, *mapScript);
	Sound = new SoundManager(this);
	scene = loader->LoadScene(defscene);
	StartAll();

	//	GameLoop();
}

GameManager::~GameManager()
{
}

void GameManager::GameLoop()
{
  //sf::Event event;

  /*	while (_window->isOpen())
	{
		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window->close();
			if (event.type == sf::Event::KeyPressed)
				Input[0].addKeyPressed(event.key.code);
			if (event.type == sf::Event::KeyReleased)
				Input[0].addKeyReleased(event.key.code);
		}
  */
		if (_clock.getElapsedTime().asSeconds() > 1 / _fps)
		{
			DisplayAll();
			UpdateAll();
			//DetectCollision();
			_clock.restart();
			Input[0].clearAction();
			Input[1].clearAction();
			Input[2].clearAction();
			Input[3].clearAction();
		}
		//}
}

void GameManager::DisplayAll()
{
	std::list<SpriteRenderer *> drawList;
	std::list<TextRenderer *> drawList2;
	//_window->clear();
	GameRoom->sendAll("clear;");
	drawList = scene->GetComponentsInScene<SpriteRenderer>();
	drawList.sort(CompareSpriteByDepth);
	auto it = drawList.begin();
	while (it != drawList.end())
	{
	  (*it)->Display();
		it++;
	}
	drawList2 = scene->GetComponentsInScene<TextRenderer>();
	drawList2.sort(CompareTextByDepth);
	auto it2 = drawList2.begin();
	while (it2 != drawList2.end())
	{
	  (*it2)->Display();
		it2++;
	}
	//_window->display();
}

void GameManager::UpdateAll()
{
	std::list<Script *> scriptList;

	scriptList = scene->GetComponentsInScene<Script>();
	auto it = scriptList.begin();
	while (it != scriptList.end())
	{
		(*it)->Update();
		it++;
	}
}

void GameManager::CallConnect(int id)
{
	std::list<Script *> scriptList;

	scriptList = scene->GetComponentsInScene<Script>();
	auto it = scriptList.begin();
	while (it != scriptList.end())
	{
		(*it)->OnClientConnect(id);
		it++;
	}
}

void GameManager::StartAll()
{
	std::list<Script *> scriptList;

	scriptList = scene->GetComponentsInScene<Script>();
	auto it = scriptList.begin();
	while (it != scriptList.end())
	{
		(*it)->Start();
		it++;
	}
}

float GameManager::GetFPS()
{
	return _fps;
}

void GameManager::LoadScene(std::string path)
{
	scene = loader->LoadScene(path);
	StartAll();
}

void GameManager::AddClient(Client *c)
{
  tabcl.push_back(c);
  CallConnect(tabcl.size() - 1);
}

void GameManager::ReceivePacket(sf::Event::EventType type, sf::Keyboard::Key key, sockaddr_in id)
{
  int i;
  bool contain = false;

  for (i = 0; i < tabcl.size() && !contain; i++)
    contain = (tabcl[i]->isSame(id));
  i--;


  if (contain)
    {
      if (type == sf::Event::KeyPressed)
	Input[i].addKeyPressed(key);
      if (type == sf::Event::KeyReleased)
	Input[i].addKeyReleased(key);
    }
}
