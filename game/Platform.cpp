#include "Platform.h"



Platform::Platform(GameDataRef data, sf::Vector2f size, sf::Vector2f position, std::string name):
	_data(data)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(&_data->assets.GetTexture(name));
	body.setPosition(position);
}

void Platform::Draw()
{
	_data->window.draw(body);
}

Platform::~Platform()
{
}
