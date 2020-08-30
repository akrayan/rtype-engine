//#include "IComponent.h"
#include "Engine.h"



void IComponent::SetType(std::string str)
{
	type = str;
}

std::string IComponent::GetType()
{
	return type;
}

void IComponent::SetManager(GameManager * manager)
{
	Game = manager;
}
/*/
void IComponent::setParent(GameObject * parent)
{
	gameobject = parent;
}*/


IComponent::~IComponent()
{
}
