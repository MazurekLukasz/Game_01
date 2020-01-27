#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Hero.h"
#include "HeroAI.h"
#include "Platform.h"



class LevelState : public State
{
public:
	LevelState(GameDataRef data);
	~LevelState();

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	void spawnPlayers( sf::Vector2f spawnPos);
	void checkCollision(Hero &hero, float dt);

private:
	sf::Vector2f startPoint;
	GameDataRef _data;
	sf::RectangleShape _background;
	
	std::vector<Character*> characters;
	std::vector<Hero*> _heroes;
	std::vector<Platform> _platforms;
	};


