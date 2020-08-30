#include "Engine.h"

TextRenderer::TextRenderer()
{
	/*_font = new sf::Font();
	text.setFillColor(sf::Color::White);
	*/
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::Display(/*sf::RenderWindow * win*/)
{
	/*text.setPosition(gameobject->transform.GetPosition());
	win->draw(text);*/
	Game->GameRoom->sendAll("text;"
		+ font + ";"
		+ text + ";"
		+ std::to_string(size) + ";"
		+ std::to_string(gameobject->transform.GetPositionX()) + ";"
		+ std::to_string(gameobject->transform.GetPositionY()) + ";"
		+ std::to_string(gameobject->transform.GetRotation()) + ";"
		+ std::to_string(gameobject->transform.GetScaleX()) + ";"
		+ std::to_string(gameobject->transform.GetScaleY()) + ";"
	);
}

void TextRenderer::SetString(std::string str)
{
	text = str;
}

void TextRenderer::SetFont(std::string path)
{
	/*_font->loadFromFile(path);
	text.setFont(*_font);*/
	font = path;
}

void TextRenderer::SetSize(int i)
{
	size = i;
	//text.setCharacterSize(i);
}

bool CompareTextByDepth(TextRenderer * s1, TextRenderer * s2)
{
	return false;
}
