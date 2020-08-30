#include "Engine.h"


SceneLoader::SceneLoader(GameManager * gm, std::map<std::string, Script*(*)()> mapScript) : Game(gm), listScript(mapScript)
{

	pOnParse["TransformObject"] = &ParseTransform;
	pOnParse["SpriteRenderer"] = &ParseSpriteRenderer;
	pOnParse["TextRenderer"] = &ParseTextRenderer;
	pOnParse["Collider"] = &ParseCollider;
}

SceneLoader::~SceneLoader()
{
}

Scene * SceneLoader::LoadScene(std::string path)
{
	scene = new Scene(Game, this);
	std::ifstream f(path, std::ios::in);
	std::string s;

	while (std::getline(f, s, '\n'))
	{
		std::cout << s << std::endl;
		checkLine(s);

	}
	return scene;
}

GameObject * SceneLoader::Instantiate(std::string path)
{
	GameObject *go;
	std::ifstream f(path, std::ios::in);
	std::string s;

	go = new GameObject(Game, path.substr(0, path.find('.')));
	//std::cout << path << "\n" << go->GetName() << std::endl;
	while (std::getline(f, s, '\n'))
	{
		//std::cout << s << std::endl;
		std::stringstream stream(s);
		checkCompoOrChild(go, stream);
	}
	return go;
}


void SceneLoader::checkLine(std::string line)
{
	std::string s, s1;
	std::stringstream stream(line);
	GameObject *g;
	int i = 0;

	std::getline(stream, s, '>');
	if (s.find(':') != std::string::npos)
	{
		std::stringstream stream(s);
		std::getline(stream, s, ':');
		std::getline(stream, s1, ':');

		if (s == "GameObject")
		{
			g = new GameObject(Game, s1);
			scene->Instantiate(g);
			//g->SetInput(Input);
			//_objectList.push_back(g);
		}
		else
			std::cout << "ERROR not GameObject " + s + "\n";
		return;
	}
	/*while (i < scene.objectList.size() && _objectList[i]->GetName() != s)
		i++;*/
	g = scene->FindByName(s);
	if (g != NULL)
		checkCompoOrChild(g, stream);
	else
		std::cout << "ERROR unknow gameobject \n\n";
}

void SceneLoader::checkCompoOrChild(GameObject *parent, std::stringstream &stream)
{
	std::string compo, str;
	std::getline(stream, compo, '>');
	std::stringstream stream2(compo);

	std::getline(stream2, str, '=');
	if (str == "Tag")
	{
		std::getline(stream2, str, '=');
		parent->SetTag(str);
	}
	else if (listScript.find(compo) != listScript.end())
		parent->AddComponent<Script>(listScript[compo](), Game);
	else
		ParseComponent(compo, parent, stream);

	/*auto iter = pOnParse.find(compo);
	if (iter != pOnParse.end())
	{
	(*iter->second)(parent, stream);
	}
	else
	{
	std::cout << "ERROR unknow component " + compo + "\n\n";
	}*/

}

int SceneLoader::ParseComponent(std::string Compo, GameObject *g, std::stringstream &stream)
{

	auto i = pOnParse.find(Compo);
	if (i == pOnParse.end())
		return (-1);
	return ((*i->second)(Game, g, stream));
}

int SceneLoader::ParseTransform(GameManager *Game, GameObject *g, std::stringstream &stream)
{
	std::string s2, s3, s4;

	std::getline(stream, s2, '>');
	if (s2 == "position")
	{
		std::getline(stream, s3, '=');
		std::getline(stream, s4, '=');
		if (s3 == "x")
		{
			g->transform.SetPosition(std::stof(s4), g->transform.GetPositionY());
		}
		else if (s3 == "y")
		{
			g->transform.SetPosition(g->transform.GetPositionX(), std::stof(s4));
		}
		else
		{
			std::cout << "ERROR they must have a setter for position\n\n";

		}
	}
	else if (s2 == "scale")
	{
		std::getline(stream, s3, '=');
		std::getline(stream, s4, '=');
		if (s3 == "x")
		{
			g->transform.SetScale(std::stof(s4), g->transform.GetScaleY());
		}
		else if (s3 == "y")
		{
			g->transform.SetScale(g->transform.GetScaleX(), std::stof(s4));
		}
		else
		{
			std::cout << "ERROR they must have a setter for Scale\n\n";

		}
	}
	else
	{
		std::stringstream stream2(s2);
		std::getline(stream2, s3, '=');
		std::getline(stream2, s4, '=');
		if (s3 == "rotation")
		{
			g->transform.SetRotation(std::stof(s4));
		}
		else
		{
			std::cout << "ERROR unknow member of transform\n\n";
			return (-1);

		}
	}
	return (0);
}

int SceneLoader::ParseSpriteRenderer(GameManager *Game, GameObject *g, std::stringstream &stream)
{
	SpriteRenderer *sr;
	std::string s2, s3, s4;

	if ((sr = g->GetComponent<SpriteRenderer>()) == NULL)
		sr = g->AddComponent<SpriteRenderer>(Game);
	if (!std::getline(stream, s2, '>'))
		return (0);
	std::stringstream stream2(s2);
	std::getline(stream2, s3, '=');
	std::getline(stream2, s4, '=');

	if (s3 == "texture")
	{
		sr->SetTexture(s4);
	}
	else if (s3 == "depth")
	{
		sr->SetDepth(std::stof(s4));
	}
	else if (s3 == "rectTextureTop")
	{
		sr->rectTexture.top = std::stof(s4);
		sr->_sprite.setTextureRect(sr->rectTexture);
	}
	else if (s3 == "rectTextureLeft")
	{
		sr->rectTexture.left = std::stof(s4);
		sr->_sprite.setTextureRect(sr->rectTexture);
	}
	else if (s3 == "rectTextureHeight")
	{
		sr->rectTexture.height = std::stof(s4);
		sr->_sprite.setTextureRect(sr->rectTexture);
	}
	else if (s3 == "rectTextureWidth")
	{
		sr->rectTexture.width = std::stof(s4);
		sr->_sprite.setTextureRect(sr->rectTexture);
	}
	else if (s3 == "repeatTexture")
	{
		sr->SetTextureRepeatable(s4 == "true");
	}
	else
	{
		std::cout << "ERROR unknow member of SpriteRenderer\n\n";
		return (-1);
	}
	return (0);
}

int SceneLoader::ParseTextRenderer(GameManager *Game, GameObject *g, std::stringstream &stream)
{
	TextRenderer *tr;
	std::string s2, s3, s4;

	if ((tr = g->GetComponent<TextRenderer>()) == NULL)
		tr = g->AddComponent<TextRenderer>(Game);
	if (!std::getline(stream, s2, '>'))
		return (0);
	std::stringstream stream2(s2);
	std::getline(stream2, s3, '=');
	std::getline(stream2, s4, '=');

	if (s3 == "font")
	{
		tr->SetFont(s4);
	}
	else if (s3 == "text")
	{
		tr->SetString(s4);
	}
	else if (s3 == "size")
	{
		tr->SetSize(std::stof(s4));
	}
	else
	{
		std::cout << "ERROR unknow member of SpriteRenderer\n\n";
		return (-1);
	}
	return (0);
}

int SceneLoader::ParseCollider(GameManager *Game, GameObject * g, std::stringstream & stream)
{
	Collider *c;
	std::string s2, s3, s4;

	if ((c = g->GetComponent<Collider>()) == NULL)
		c = g->AddComponent<Collider>(Game);
	if (!std::getline(stream, s2, '>'))
		return (0);
	std::stringstream stream2(s2);
	std::getline(stream2, s3, '=');
	std::getline(stream2, s4, '=');

	if (s3 == "ignore")
	{
		c->AddTagIgnore(s4);
	}
	else if (s3 == "IsTrigger")
	{
		if (s4 == "true")
			c->IsTrigger = true;
		else if (s4 == "false")
			c->IsTrigger = false;
	}
	else
	{
		std::cout << "ERROR unknow member of Collider\n\n";
		return (-1);
	}
	return 0;
}
