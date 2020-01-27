#include "Game.h"
#include "SplashState.h"

Game::Game(std::string title)
{
	sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
	_data->window.create(/*sf::VideoMode(width,height)*/DesktopMode ,title, sf::Style::Close | sf::Style::Titlebar /*| sf::Style::Fullscreen */);
	_data->SCREEN_WIDTH = DesktopMode.width;
	_data->SCREEN_HEIGHT = DesktopMode.height;
	_data->machine.AddState((StateRef)new SplashState(this->_data));

	this->Run();
}

Game::~Game()
{
}

void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen()) 
	{
		this->_data->machine.ProcessStateChanges();

		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
}