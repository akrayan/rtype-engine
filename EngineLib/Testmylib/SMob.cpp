#include "Header.h"

SMob::SMob()
{
}

SMob::~SMob()
{
}

void SMob::Start()
{
	Level = (Game->scene->FindByName("Level")->GetComponent<SLevel>());
	Yorigin = gameobject->transform.GetPositionY();
	//std::cout << "im alive !   " << Yorigin << std::endl;

}

void SMob::Update()
{
	if (cl.getElapsedTime().asSeconds() > LifeTime)
	{
		Game->scene->Destroy(gameobject);
	}
	if (HP <= 0)
	{
		Level->Score += 10;
		Game->scene->Destroy(gameobject);
	}
	if (gameobject->transform.GetPositionY() > Yorigin + Ymax)
		Yvector = -1;
	if (gameobject->transform.GetPositionY() < Yorigin - Ymax)
		Yvector = 1;
	gameobject->transform.Translate(Xspeed * -1, Yspeed * Yvector);

}

void SMob::OnCollisionEnter(Collision * col)
{
	//std::cout << "aiie  " << gameobject->GetName() << " with    " << col->other->GetName() << std::endl;

	Yvector = Yvector == 1 ? -1 : 1;
}