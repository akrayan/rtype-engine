#pragma once
class EventNetwork
{
	std::list<sf::Keyboard::Key>  action;
	std::list<sf::Keyboard::Key>  pressed;
	std::list<sf::Keyboard::Key>  released;

public:
	EventNetwork();
	~EventNetwork();

	bool GetButton(sf::Keyboard::Key key);
	bool IsPressed(sf::Keyboard::Key key);
	bool IsReleased(sf::Keyboard::Key key);

	void addKeyPressed(sf::Keyboard::Key key);
	void addKeyReleased(sf::Keyboard::Key key);

	void clearAction();

};
