#include "Header.h"



SGround::SGround()
{
}


SGround::~SGround()
{
}

void SGround::Start()
{
	boundary = gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();
	gameobject->transform.SetPosition(gameobject->transform.GetPositionX(), gameobject->transform.GetPositionY() - boundary.height);
}

void SGround::Update()
{
	gameobject->transform.Translate(-1 * ScrollSpeed, 0);
	if (gameobject->transform.GetPositionX() + gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds().width < 0)
		Game->scene->Destroy(gameobject);
}

void SGround::OnCollisionEnter(Collision * col)
{
	//std::cout << "aiie  " << gameobject->GetName() << " with    " << col->other->GetName() << std::endl;

}
