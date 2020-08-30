#include "Engine.h"

EventNetwork::EventNetwork()
{
}


EventNetwork::~EventNetwork()
{
}

bool EventNetwork::GetButton(sf::Keyboard::Key key)
{
	auto it = action.begin();
	while (it != action.end())
	{
		if (key == *it)
			return true;
		it++;
	}
	return false;
}

bool EventNetwork::IsPressed(sf::Keyboard::Key key)
{
	auto it = pressed.begin();
	while (it != pressed.end())
	{
		if (key == *it)
			return true;
		it++;
	}
	return false;
}

bool EventNetwork::IsReleased(sf::Keyboard::Key key)
{
	auto it = released.begin();
	while (it != released.end())
	{
		if (key == *it)
			return true;
		it++;
	}
	return false;
}

void EventNetwork::addKeyPressed(sf::Keyboard::Key key)
{

	bool contain = false, contain2 = false;
	int i = -1;
	auto it = pressed.begin();
	while (it != pressed.end())
	{
		contain = (key == *it) || contain;
		it++;
	}
	it = action.begin();
	while (it != action.end())
	{
		contain2 = (key == *it) || contain2;
		it++;
	}
	/*
	while (++i < pressed.size())
		contain = (key == pressed[i]) || contain;
	i = -1;
	while (++i < action.size())
		contain2 = (key == action[i]) || contain2;
	*/if (!contain)
	{
		pressed.push_back(key);
	}
	if (!contain && !contain2)
		action.push_back(key);

}

void EventNetwork::addKeyReleased(sf::Keyboard::Key key)
{
	bool contain = false;
	int i = -1;

	auto it = pressed.begin();
	while (it != pressed.end())
	{
		if (*it == key)
			it = pressed.erase(it);
		else
			it++;
	}
	it = released.begin();
	while (it != released.end())
	{
		contain = (key == *it) || contain;
		it++;
	}/*
	i = -1;
	while (++i < released.size())
		contain = (key == released[i]) || contain;*/
	if (!contain)
		released.push_back(key);
}

void EventNetwork::clearAction()
{
	action.clear();
	released.clear();
}



