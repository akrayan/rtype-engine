#pragma once

class Scene
{
	std::list<GameObject *> objectlist;
	GameManager *Game;
	SceneLoader *sceneloader;

public:
	Scene(GameManager *gm, SceneLoader *scl);
	~Scene();

	GameObject *FindByName(std::string name);
	std::list<GameObject *> FindsByTag(std::string tag);

	//template<typename T> std::list<T *> GetComponentsInScene();
	template<typename T> std::list<T *> GetComponentsInScene()
	{
		std::list<T *> list;
		auto it = objectlist.begin();

		while (it != objectlist.end())
		{
			list.splice(list.end(), (*it)->GetComponents<T>());
			it++;
		}
		return list;
	}
	void Instantiate(GameObject *go, bool start = false);
	GameObject *Instantiate(std::string str);
	void Destroy(GameObject *go);
};


