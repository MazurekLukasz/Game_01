#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "definitions.h"
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "PlayersManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	sf::View view;
	AssetManager assets;
	InputManager input;
	PlayersManager PlayersManager;
	float SCREEN_WIDTH = 1024;
	float SCREEN_HEIGHT = 512;
};
typedef std::shared_ptr<GameData> GameDataRef;


class Game
{
public:
	Game(std::string title);
	~Game();

private:
	void Run();

	const float dt = 1.0f/60.0f;
	sf::Clock _clock;
	GameDataRef _data = std::make_shared<GameData>();
};

