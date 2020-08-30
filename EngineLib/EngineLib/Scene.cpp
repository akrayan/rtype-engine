#include "Engine.h"

Scene::Scene(GameManager * gm, SceneLoader *scl) : Game(gm), sceneloader(scl)
{
}

Scene::~Scene()
{
}

GameObject * Scene::FindByName(std::string name)
{
	auto it = objectlist.begin();
	while (it != objectlist.end())
	{
		if ((*it)->GetName() == name)
		{
			return ((*it));
		}
		it++;
	}
	return NULL;
}

std::list<GameObject*> Scene::FindsByTag(std::string tag)
{
	std::list<GameObject*> list;

	auto it = objectlist.begin();

	while (it != objectlist.end())
	{
		if ((*it)->GetTag() == tag)
		{
			list.push_back(*it);
		}
		it++;
	}
	return list;

}

void Scene::Instantiate(GameObject *go, bool start)
{
	objectlist.push_back(go);
	if (start) go->GetComponent<Script>()->Start();
}

GameObject *Scene::Instantiate(std::string str)
{
	GameObject *g = sceneloader->Instantiate(str);
	std::list<Script *> l = g->GetComponents<Script>();

	objectlist.push_back(g);
	auto it = l.begin();
	while (it != l.end())
	{
		(*it)->Start();
		it++;
	}
	return g;
}

void Scene::Destroy(GameObject * go)
{
	objectlist.remove(go);
}
