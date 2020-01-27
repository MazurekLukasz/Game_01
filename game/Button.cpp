#include "Button.h"



Button::Button(GameDataRef data, std::string name, sf::Vector2f position, ButtonTag tag):
	_data(data)
{
	Icon.setTexture(_data->assets.GetTexture(name));
	Icon.setPosition(position);
	TAG = tag;
}

Button::Button(GameDataRef data, std::string name, sf::Vector2f position, ButtonTag tag, std::string nam) :
	_data(data)
{
	Icon.setTexture(_data->assets.GetTexture(name));
	Icon.setPosition(position);
	TAG = tag;
	_Name = nam;
}

Button::~Button()
{
}
