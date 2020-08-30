#pragma once
#include "IComponent.h"
class TextRenderer :
	public IComponent
{
	/*sf::Font *_font;
	sf::Text text;
	*/
	std::string font;
	std::string text;
	int size;

	float _depth = 1;

public:
	TextRenderer();
	~TextRenderer();

	void Display(/*sf::RenderWindow *win*/);

	void SetString(std::string str);
	void SetFont(std::string path);
	void SetSize(int i);
	
};

bool CompareTextByDepth(TextRenderer *s1, TextRenderer *s2);