#include "PlayerController.h"
#include <iostream>


PlayerController::PlayerController(unsigned int PNr, bool keyboard, int padNr)
{
	this->playerNr = PNr;
	this->Keyboard = keyboard;
	this->joystickNr = padNr;
	

	if (Keyboard)
	{
		_buttons.Left = sf::Keyboard::Left;
		_buttons.Right = sf::Keyboard::Right;
		_buttons.Attack = sf::Keyboard::X;
		_buttons.Jump = sf::Keyboard::Z;
	}

}

PlayerController::PlayerController(unsigned int PNr, bool keyboard)
{
	this->playerNr = PNr;
	this->Keyboard = keyboard;

	if (Keyboard)
	{
		_buttons.Left = sf::Keyboard::Left;
		_buttons.Right = sf::Keyboard::Right;
		_buttons.Attack = sf::Keyboard::X;
		_buttons.Jump = sf::Keyboard::Z;
	}

}
PlayerController::~PlayerController() 
{
}