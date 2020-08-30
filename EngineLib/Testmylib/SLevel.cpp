#include "Header.h"


SLevel::SLevel()
{
}


SLevel::~SLevel()
{
}

void SLevel::Start()
{
	
	ScoreText = Game->scene->FindByName("Score")->GetComponent<TextRenderer>();

	LastGround = Game->scene->Instantiate("Prefab/Ground1.prefab");
}

void SLevel::Update()
{
	std::string score;
	int i = 0;

	if ((Timer1.getElapsedTime().asSeconds() > timeBetweenWave) || firstCall)
	{

		if ((Timer2.getElapsedTime().asSeconds() > 0.3) || firstCall)
		firstCall = false;
		createMob();
		Timer1.restart();
	}
	score = "Score : ";
	score += std::to_string(Score);
	if (ScoreText != NULL)
		ScoreText->SetString(score);
	else
		std::cout << "pas trouvé frer" << std::endl;
	if (LastGround != NULL && LastGround->transform.GetPositionX() < 1023 - LastGround->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds().width)
	{
		LastGround = Game->scene->Instantiate("Prefab/Ground1.prefab");
	}
}

void SLevel::OnClientConnect(int id)
{
	GameObject *player = Game->scene->Instantiate("Prefab/Player" + std::to_string(id + 1) + ".prefab");

	player->GetComponent<SPlayer>()->idClient = id;
	Game->Sound->playForOne(id, "Ressources/BGM.ogg", true, 20);

}

void SLevel::createMob()
{
	//GameObject *Mob = Game->scene->Instantiate("Prefab/Mob.prefab");
	GameObject *Mob = new GameObject(Game, "Mob");
	SpriteRenderer *Sr = Mob->AddComponent<SpriteRenderer>(Game);
	//sf::FloatRect PlayerRect = gameobject->GetComponent<SpriteRenderer>()->_sprite.getGlobalBounds();
	
	Mob->SetTag("Mob");
	Sr->SetTexture("Ressources/ufo.png");
	//Mob->transform.SetScale(0.3, );
	Mob->transform.SetPosition(1024, (rand() % 400 - 75) + 100);
	Mob->AddComponent<SMob>(Game);
	Mob->AddComponent<Collider>(Game);

	Game->scene->Instantiate(Mob, true);
	
}