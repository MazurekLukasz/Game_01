#include "SplashState.h"
#include "MainMenuState.h"
#include <sstream>
#include "definitions.h"
#include <iostream>

SplashState::SplashState(GameDataRef data): _data(data)
{
}

SplashState::~SplashState()
{
}

void SplashState::Init() 
{
	_data->assets.LoadTexture("SplashScreen",SPLASH_SCENE_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.GetTexture("SplashScreen"));
	_background.setOrigin(_background.getGlobalBounds().width/2, _background.getGlobalBounds().height/2);
	_background.setPosition(_data->SCREEN_WIDTH/2, _data->SCREEN_HEIGHT/2);
}

void SplashState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			_data->window.close();
	}
}

void SplashState::Update(float dt) 
{
	if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
}

void SplashState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.display();
}
