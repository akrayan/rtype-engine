#pragma once
//#include "Engine.h"

class IComponent
{
	

	std::string type;
protected:
	GameManager * Game;

public:
	GameObject * gameobject;

	void SetManager(GameManager *manager);
	//void SetParent(GameObject * parent);
	void SetType(std::string str);
	std::string GetType();


	virtual ~IComponent();

};

