//#include "GameObject.h"
#include "Engine.h"

GameObject::GameObject(GameManager * gm, std::string name) : transform(gm, this), name(name)
{

}

GameObject::~GameObject()
{
}

std::string GameObject::GetName()
{
	return name;
}

std::string GameObject::GetTag()
{
	return tag;
}

void GameObject::SetTag(std::string tagg)
{
	tag = tagg;
}
/*
template <typename T> std::list<T *> GameObject::GetComponents() {
	std::list<T *> tmp;

	for (int i = 0; i < Components.size(); i++)
	{
		if (typeid(T).name() == Components[i]->_type || dynamic_cast<T *>(_components[i]) != NULL)
		{
			tmp.push_back(dynamic_cast<T *>(Components[i]));
		}
	}
	return (tmp);
}

template <typename T> T *GameObject::AddComponent() {
	T *tmp;

	tmp = new T();
	tmp->gameobject = this;
	tmp->SetType(typeid(T).name());
	Components.push_back(tmp);
	return (tmp);
}

template <typename T> T *GameObject::AddComponent(T *component) {

	component->gameobject = this;
	component->SetType(typeid(T).name());
	Components.push_back(component);
	return (component);
}

template <typename T> T *GameObject::GetComponent() {
	for (int i = 0; i < _components.size(); i++)
	{
		if (typeid(T).name() == _components[i]->_type || dynamic_cast<T *>(_components[i]) != NULL)
		{
			return (dynamic_cast<T *>(_components[i]));
		}
	}
	return (NULL);
}*/