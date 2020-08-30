#pragma once
//#include "Engine.h"

class TransformObject;

class GameObject
{
	std::list<IComponent *> Components;
	std::string tag;
	std::string name;

public:
	TransformObject transform;

	GameObject(GameManager * gm, std::string name);
	~GameObject();
	
	std::string GetName();
	std::string GetTag();
	void SetTag(std::string tagg);

	/*
	template <typename T> T *AddComponent();
	template <typename T> T *AddComponent(T *component);
	template <typename T> T *GetComponent();
	template <typename T> std::list<T *> GetComponents();
	*/
	template <typename T> std::list<T *> GetComponents() {
		std::list<T *> tmp;
		auto it = Components.begin();

		while(it != Components.end())//for (int i = 0; i < Components.size(); i++)
		{
			if (typeid(T).name() == /*Components[i]*/(*it)->GetType() || dynamic_cast<T *>(/*Components[i]*/(*it)) != NULL)
			{
				tmp.push_back(dynamic_cast<T *>(/*Components[i]*/(*it)));
			}
			it++;
		}
		return (tmp);
	}

	template <typename T> T *AddComponent(GameManager *Game) {
		T *tmp;

		tmp = new T();
		tmp->gameobject = this;
		tmp->SetManager(Game);
		tmp->SetType(typeid(T).name());
		Components.push_back(tmp);
		return (tmp);
	}

	template <typename T> T *AddComponent(T *component, GameManager *Game) {

		component->gameobject = this;
		component->SetManager(Game);
		component->SetType(typeid(T).name());
		Components.push_back(component);
		return (component);
	}

	template <typename T> T *AddComponent(T *component) {

		component->gameobject = this;
		component->SetType(typeid(T).name());
		Components.push_back(component);
		return (component);
	}
	
	template <typename T> T *GetComponent() {
		auto it = Components.begin();

		while (it != Components.end())//for (int i = 0; i < Components.size(); i++)
		{
			if (typeid(T).name() == /*Components[i]*/(*it)->GetType() || dynamic_cast<T *>(/*Components[i]*/(*it)) != NULL)
			{
				return (dynamic_cast<T *>(/*Components[i]*/(*it)));
			}
			it++;
		}
		return (NULL);
	}
};
