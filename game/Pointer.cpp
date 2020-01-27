#include "Pointer.h"



Pointer::Pointer(GameDataRef data,std::string name, PlayerButtons PlBut): _data(data)
{
	_Name = name;
	Icon.setTexture(_data->assets.GetTexture(name));
	Icon.setOrigin(Icon.getGlobalBounds().width / 2, Icon.getGlobalBounds().height / 2);

	buttIterator = 0;
	_buttons = PlBut;
	pad = false;
}

Pointer::Pointer(GameDataRef data, std::string name, int padNr) : _data(data)
{
	_Name = name;
	Icon.setTexture(_data->assets.GetTexture(name));
	Icon.setOrigin(Icon.getGlobalBounds().width / 2, Icon.getGlobalBounds().height / 2);

	buttIterator = 0;
	pad = true;
	PadNR = padNr;
}
Pointer::~Pointer()
{
}
void Pointer::Update()
{
}

void Pointer::setActualButton(Button &but)
{
	actualButton = &but;
}

void Pointer::UpdatePointerPos()
{
	Icon.setPosition(actualButton->getPosition());
	if (_Name == "Player 2 Pointer")
	{
		Icon.setPosition(Icon.getPosition().x, Icon.getPosition().y-15);
	}
}

void Pointer::checkInputs(int size, sf::Event eve)
{
	if (!pad)
	{
		if (eve.type == sf::Event::KeyPressed)
		{

			if (eve.key.code == _buttons.Right)
			{
				buttIterator++;
				if (buttIterator >= size)
				{
					//buttIterator = 0;
					resetIterator();
				}
			}
			else if (eve.key.code == _buttons.Left)
			{
				buttIterator--;

				if (buttIterator < 0)
				{
					buttIterator = size - 1;
				}
			}
		}
	}
	else if (pad)
	{
		if (eve.type == sf::Event::JoystickMoved)
		{
			float axis = sf::Joystick::getAxisPosition(PadNR, sf::Joystick::X);
			if (clock.getElapsedTime().asSeconds() >= 0.1f) 
			{
				if (axis >= 80)
				{
					buttIterator++;
					if (buttIterator == size)
					{
						//buttIterator = 0;
						resetIterator();
					}
				}
				else if (axis <= -80)
				{
					buttIterator--;

					if (buttIterator < 0)
					{
						buttIterator = size - 1;
					}
				}
				clock.restart();
			}
		}
	}
}



