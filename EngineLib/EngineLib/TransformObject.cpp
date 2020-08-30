//#include "TransformObject.h"
#include "Engine.h"
#define NBCHECKCOLLIDE 1

TransformObject::TransformObject(GameManager * gmref, GameObject * goref) : gamemanager(gmref), gameobject(goref)
{
}

TransformObject::~TransformObject()
{
}

void TransformObject::SetPosition(sf::Vector2f v)
{
	SpriteRenderer *s = gameobject->GetComponent<SpriteRenderer>();

	position = v;
	if (s != NULL)
		s->_sprite.setPosition((position));
}


void TransformObject::SetScale(sf::Vector2f v)
{
	SpriteRenderer *s = gameobject->GetComponent<SpriteRenderer>();

	scale = v;
	if (s != NULL)
		s->_sprite.setScale((scale));
}

void TransformObject::SetPosition(float x, float y)
{
	SpriteRenderer *s = gameobject->GetComponent<SpriteRenderer>();

	position = { x, y };
	if (s != NULL)
		s->_sprite.setPosition((position));

}

void TransformObject::SetScale(float x, float y)
{
	SpriteRenderer *s = gameobject->GetComponent<SpriteRenderer>();

	scale = { x, y };
	if (s != NULL)
		s->_sprite.setScale((scale));

}

void TransformObject::SetRotation(float angle)
{
	rotation = angle;
}

float TransformObject::GetRotation()
{
	return rotation;
}

sf::Vector2f TransformObject::GetPosition()
{
	return position;
}

float TransformObject::GetPositionX()
{
	return position.x;
}

float TransformObject::GetPositionY()
{
	return position.y;
}

sf::Vector2f TransformObject::GetScale()
{
	return scale;
}

float TransformObject::GetScaleX()
{
	return scale.x;
}

float TransformObject::GetScaleY()
{
	return scale.y;
}

void TransformObject::Rotate(float angle)
{

}

void TransformObject::Translate(float x, float y)
{
	Translate({x, y});
}

Collision *TransformObject::Collide(Collider *C, std::list<Collider *> list, Collision *col)
{

	std::list<Script *> Slist;

	if (C != NULL)
	{
		auto ite = list.begin();
		while (ite != list.end())
		{
			if ((*ite) != C && ((col = C->DetectCollisionWith(*ite, &gamemanager->bitArray)) != NULL))
			{
				col->other = (*ite)->gameobject;
				Slist = C->gameobject->GetComponents<Script>();
				auto it2 = Slist.begin();
				while (it2 != Slist.end())
				{
					(*it2)->OnCollisionEnter(col);
					it2++;
				}
				col->other = C->gameobject;
				Slist.clear();
				Slist = (*ite)->gameobject->GetComponents<Script>();
				it2 = Slist.begin();
				while (it2 != Slist.end())
				{
					(*it2)->OnCollisionEnter(col);
					it2++;
				}
				col->other = (*ite)->gameobject;
				return col;
			}
			ite++;
		}
	}
	return col;
}

void TransformObject::Translate(sf::Vector2f v)
{

	if (v.x == 0 && v.y == 0)
		return;
	int i = 0, it = 1;
	sf::Vector2f vn = VectorNormalize(v, &it);

	Collider *C = gameobject->GetComponent<Collider>();
	SpriteRenderer *Sr = gameobject->GetComponent<SpriteRenderer>();

	std::list<Collider *> list;
	auto ite = list.begin();
	Collision *col = NULL;

	if (C != NULL)
		list = gamemanager->scene->GetComponentsInScene<Collider>();
	while (i * NBCHECKCOLLIDE < it && col == NULL)//((old + v) != position)
	{
		position += vn * (float)NBCHECKCOLLIDE;
		if (Sr != NULL) Sr->_sprite.setPosition(position);
		col = Collide(C, list, col);
		if (col != NULL && !C->IsTrigger && !(col->other->GetComponent<Collider>()->IsTrigger))
		{
			//std::cout << gameobject->GetName() << C->IsTrigger << col->other->GetName() << (col->other->GetComponent<Collider>()->IsTrigger) << std::endl;
			position -= vn * (float)(NBCHECKCOLLIDE + 1);
			if (Sr != NULL) Sr->_sprite.setPosition(position);		}
		i++;
	}
}

sf::Vector2f VectorNormalize(sf::Vector2f v, int *iteration)
{
	sf::Vector2i sign;

	sign.x = (v.x >= 0) ? 1 : -1;
	sign.y = (v.y >= 0) ? 1 : -1;
	v.x = v.x * sign.x;
	v.y = v.y * sign.y;

	if (v.x == v.y && v.x != 0)
	{
		*iteration = static_cast<int>(v.x);
		v.x /= v.x;
		v.y /= v.y;
	}
	else if (v.x > v.y)
	{
		*iteration += static_cast<int>(v.x);
		v.x /= v.x;
		v.y /= v.x;
	}
	else
	{
		*iteration += static_cast<int>(v.y);
		v.x /= v.y;
		v.y /= v.y;
	}
	v.x *= sign.x;
	v.y *= sign.y;
	return v;
}
