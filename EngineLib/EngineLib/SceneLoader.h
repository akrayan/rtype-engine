#pragma once
class GameObject;
class GameManager;
class Scene;
class Script;


typedef int(*pointerOnParse)(GameManager *, GameObject *, std::stringstream &);

class SceneLoader
{
	GameManager *Game;
	Scene *scene;
	std::map<std::string, pointerOnParse> pOnParse;
	std::map<std::string, Script *(*)()> listScript;

	static int ParseTransform(GameManager *Game, GameObject * g, std::stringstream & stream);
	static int ParseSpriteRenderer(GameManager *Game, GameObject * g, std::stringstream & stream);
	static int ParseTextRenderer(GameManager *Game, GameObject * g, std::stringstream & stream);
	static int ParseCollider(GameManager *Game, GameObject * g, std::stringstream & stream);
	int ParseComponent(std::string Compo, GameObject * g, std::stringstream & stream);
	void checkLine(std::string line);

	void checkCompoOrChild(GameObject * parent, std::stringstream & stream);

public:
	SceneLoader(GameManager *gm, std::map<std::string, Script *(*)()> mapScript);
	~SceneLoader();


	Scene *LoadScene(std::string path);
	GameObject *Instantiate(std::string path);

};

