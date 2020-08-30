#include "Header.h"



SPlayer::SPlayer()
{
}


SPlayer::~SPlayer()
{
}

void SPlayer::Start()
{
	boundary.left = 0;
	boundary.top = 75;
	boundary.height = 720 - 75;
	boundary.width = 1024;

	//playerboundary = gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();
	SpriteBar = Game->scene->FindByName("WeaponBar" + std::to_string(idClient + 1))->GetComponent<SpriteRenderer>();
   	if (SpriteBar != NULL) widthBar = SpriteBar->rectTexture.width;
	else std::cout << "booooooooooooooouh" << std::endl;
	//std::cout << dynamic_cast<int>(Sr->rectTexture.width) << std::endl;
}

void SPlayer::Update()
{
	float Speed = 5;
	sf::Vector2f v = { 0, 0 };

	playerboundary = gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();

	if (Game->Input[idClient].IsPressed(sf::Keyboard::Right) && playerboundary.left + playerboundary.width < boundary.width)
		v.x += 1;
	if (Game->Input[idClient].IsPressed(sf::Keyboard::Left) && playerboundary.left > boundary.left)
		v.x -= 1;
	if (Game->Input[idClient].IsPressed(sf::Keyboard::Up) && playerboundary.top > boundary.top)
		v.y -= 1;
	if (Game->Input[idClient].IsPressed(sf::Keyboard::Down) && playerboundary.top + playerboundary.height < boundary.height)
		v.y += 1;

	//std::cout << gameobject->transform.GetPositionX() << "  " << gameobject->transform.GetPositionY() << std::endl;
	gameobject->transform.Translate(v * Speed);

	/*if (cl.getElapsedTime().asSeconds() > DelayShoot && Game->Input[idClient].GetButton(sf::Keyboard::Space))
	{
		std::cout << "piou piou" << std::endl;
		Game->Sound.play("Ressources/weapon_player.wav", false, 50);
		CreateBullet();
	}*/
	if ((firstTime || cl.getElapsedTime().asSeconds() > DelayShoot) && Game->Input[idClient].IsPressed(sf::Keyboard::Space) && progresShoot < 100)
	{
		//std::cout << "pressed" << std::endl;
		progresShoot += 1 / ((Game->GetFPS() * ChargeTime) / 100);
	}
	if ((firstTime || cl.getElapsedTime().asSeconds() > DelayShoot) && Game->Input[idClient].IsReleased(sf::Keyboard::Space))
	{
		//std::cout << "released" << std::endl;
		firstTime = false;
		cl.restart();
		Game->Sound->play("Ressources/weapon_player.wav", false, 50);
		CreateBullet((progresShoot / 25));
		progresShoot = 0;
	}

	
	if (SpriteBar != NULL)
	{
		SpriteBar->rectTexture.width = (progresShoot / 100) * widthBar;
		//std::cout << (progresShoot / 100) << std::endl;
	}
}

void SPlayer::OnCollisionEnter(Collision * col)
{
	if (col->other->GetTag() != "player")
		Game->scene->Destroy(gameobject);
	//std::cout << "aiie  " << gameobject->GetName() << " with    " << col->other->GetName() << std::endl;
}

void SPlayer::CreateBullet(int type)
{
	GameObject *go = Game->scene->Instantiate("Prefab/Bullet1.prefab");
	sf::FloatRect PlayerRect = gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();
	SBullet *b = go->GetComponent<SBullet>();
	
	b->damage = type + 1;
	go->transform.SetScale(go->transform.GetScale() * (float)(type + 1));
	sf::FloatRect Srect = go->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();

	go->transform.SetPosition(gameobject->transform.GetPositionX() + PlayerRect.width + 3,
		PlayerRect.top + (PlayerRect.height / 2) - (Srect.height / 2));
}
