#include "LevelState.h"
#include "MainMenuState.h"
#include <sstream>
#include <iostream>
#include "definitions.h"
#include <SFML/Graphics.hpp>
#include "Collider.h"


LevelState::LevelState(GameDataRef data):
	_data(data)
{
	
}

LevelState::~LevelState()
{
}

void LevelState::Init()
{







	_data->assets.LoadTexture("Game background", LEVEL_BACKGROUND_FILEPATH);
	_background.setTexture(&_data->assets.GetTexture("Game background"));
	_background.setSize(sf::Vector2f((float)_data->SCREEN_WIDTH, (float)_data->SCREEN_HEIGHT));
	_background.setOrigin(_data->SCREEN_WIDTH /2, _data->SCREEN_HEIGHT/2);

	_data->assets.LoadTexture("Mega Man", MegaMan_FILEPATH);
	_data->assets.LoadTexture("Fire Man", FireMan_FILEPATH);
	_data->assets.LoadTexture("Red Man", RED_MegaMan_FILEPATH);


	_data->assets.LoadTexture("Fire Ball", FIRE_BALL_FILEPATH);
	_data->assets.LoadTexture("Icicle", ICICLE_FILEPATH);

	//new Hero(_data, sf::Vector2f(300, 200), sf::Vector2u(3.0f, 6.0f), 0.15f, 0.35f, name1);
	//characters.push_back();
	//	Enemy
	//characters.push_back(new HeroAI(_data, sf::Vector2f(800, 200), sf::Vector2u(3.0f, 6.0f), 0.15f, 0.5f, "Fire Man"));
	//characters.at(1)->setTarget(characters.at(0));
	_data->assets.LoadTexture("Stone mid 1", GR_STONE_M_01);
	_data->assets.LoadTexture("Stone mid top 1", GR_STONE_MT_01);
	_data->assets.LoadTexture("Stone mid top 2", GR_STONE_MT_02);
	
	_data->assets.LoadTexture("Stone left", GR_STONE_LEFT_FILEPATH);
	_data->assets.LoadTexture("Stone right", GR_STONE_RIGHT_FILEPATH);

//--------------------INIT---------------------------------------------------
	_data->assets.LoadTexture("ress", RESS);
	startPoint = sf::Vector2f(250, 200);
	
	
	
	int len = 200;
	for (int i = 0; i <= 4;i++) 
	{
		_platforms.push_back(Platform(_data, sf::Vector2f(len, len), sf::Vector2f(i* len, 600), "Stone mid top 1"));
	}
	for (int i = 0; i <= 4; i++)
	{
		_platforms.push_back(Platform(_data, sf::Vector2f(len, len), sf::Vector2f(i* len, 800), "Stone mid 1"));
	}
	//_platforms.push_back(Platform(_data, sf::Vector2f(400, 400), sf::Vector2f(_data->SCREEN_WIDTH - 150, _data->SCREEN_HEIGHT-130), "Land 1"));
	//_platforms.push_back(Platform(_data, sf::Vector2f(1024, 50), sf::Vector2f(SCREEN_WIDTH / 2, 25), "Land 1"));
	//_platforms.push_back(Platform(_data, sf::Vector2f(50,1024), sf::Vector2f(25,350), "Land 1"));
	//_platforms.push_back(Platform(_data, sf::Vector2f(50, 1024), sf::Vector2f(999, 350), "Land 1"));
	_data->view.setSize(sf::Vector2f(_data->SCREEN_WIDTH,_data->SCREEN_HEIGHT));

	// Spawn Players
	std::cout << "Player will be spawned" << std::endl;
	spawnPlayers(startPoint);
	std::cout << "Player created" << std::endl;
}


void LevelState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			_data->window.close();
		if(event.type == sf::Event::KeyPressed)
		{ }
	}
}


void LevelState::Update(float dt)
{
	//------------------------------------------------------------------
	if (!characters.empty())
	{

		for (unsigned int i = 0; i < characters.size() ; i++)
		{
			characters.at(i)->Update(dt);
			if (!characters.at(i)->_projectiles.empty())
			{
				for (unsigned int j = 0; j < characters.at(i)->_projectiles.size(); j++)
				{
					Projectile proj = characters.at(i)->_projectiles.at(j);
					for (unsigned int k = 0; k < characters.size(); k++)
					{
						Collider col = characters.at(k)->GetCollider();
						if (proj.GetCollider().CheckCollision(col, characters.at(k)->direction, 1.0f))
						{
							characters.at(k)->OnCollision(characters.at(k)->direction);
							characters.at(i)->_projectiles.erase(characters.at(i)->_projectiles.begin() + j);
							characters.at(k)->getDamage(5.0f);

						}
					}
				}
			}
		}
	}

	if (!characters.empty())
	{
		for (unsigned int i = 0; i < characters.size(); i++)
		{
			if (characters.at(i)->getTarget()->isDeath())
			{
				//Character* a = NULL;
				//characters.at(i)->setTarget(NULL);
			}

			if (characters.at(i)->isDeath())
			{
				characters.erase(characters.begin() + i);
			}


		}
	}
	//------------------------------------------------------------------------------------
	// Heroes vector
	if (!_heroes.empty())
	{// Set View as a hero 0 center 
		_data->view.setCenter(_heroes.at(0)->GetPosition().x,(_data->SCREEN_HEIGHT/2));
		_background.setPosition(_data->view.getCenter());

		for (Hero *hero : _heroes)
		{
			hero->Update(dt);
			checkCollision(*hero,dt);
		}
	}
}

void LevelState::Draw(float dt)
{
	//clear display
	_data->window.clear();

	// draw elements on scene
	_data->window.setView(_data->view);
	_data->window.draw(_background);

	for (Platform& platform : _platforms)
	{
		platform.Draw();
	}
	//------------------------------------
	sf::RectangleShape tex;
	tex.setTexture(&_data->assets.GetTexture("ress"));              //------------------ test kamienia 
	tex.setPosition(sf::Vector2f(200, 240));
	tex.setSize(sf::Vector2f(200,300));
	_data->window.draw(tex);
	//----------------------------------------------------


	if (!characters.empty())
	{
		for (Character *character : characters)
		{
			character->Draw();
			character->DrawHPBar();
		}
	}

	if (!_heroes.empty())
	{
		for (Hero *hero : _heroes)
		{
			hero->Draw();
			hero->DrawHPBar();
		}
	}
	//Set new display
	_data->window.display();
}///////////////////////////////////////////////////

void LevelState::checkCollision(Hero &hero, float dt)
{
	if (hero.GetPosition().y > _data->SCREEN_HEIGHT) 
	{
		hero.setPosition(startPoint);
	}

	Collider col = hero.GetCollider();

	for (Platform& platform : _platforms)
	{
		if (platform.GetCollider().CheckCollision(col, hero.direction, 1.0f))
		{
			hero.OnCollision(hero.direction);
	
		}
	}
}

void LevelState::spawnPlayers( sf::Vector2f spawnPos)
{
	if (!_data->PlayersManager.getPlayers().empty())
	{
		int k = 1;
		for (const auto &p : _data->PlayersManager.getPlayers())
		{
			_heroes.push_back(new Hero(_data,k, p.second->getButtons(),
				p.second->isKeyboard(), 0, spawnPos, sf::Vector2u(3, 6),
				p.second->getName()));
			k++;
		}
	}

}