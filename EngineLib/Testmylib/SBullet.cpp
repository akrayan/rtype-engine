#include "Header.h"



SBullet::SBullet()
{
}


SBullet::~SBullet()
{
}

void SBullet::Update()
{
	if (cl.getElapsedTime().asSeconds() > LifeTime)
	{
		Game->scene->Destroy(gameobject);
	}
	if (damage <= 0)
		Game->scene->Destroy(gameobject);
	gameobject->transform.Translate(BulletSpeed, 0);
}

void SBullet::OnCollisionEnter(Collision * col)
{
	SMob * mob;

	if (col->other->GetTag() == "Mob")
	{
		mob = (col->other->GetComponent<SMob>());
		while (mob->HP > 0 && damage > 0)
		{
			mob->HP--;
			damage--;
		}
	}/*
	else if (col->other->GetTag() == "PlayerBullet")
		Game->scene->Destroy(gameobject);
		*/
}
