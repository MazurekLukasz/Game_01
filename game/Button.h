#pragma once
#include <SFML/Graphics.hpp>
#include"Game.h"

class Button
{
public:
	Button(GameDataRef data, std::string name, sf::Vector2f position, ButtonTag tag);
	Button(GameDataRef data, std::string name, sf::Vector2f position, ButtonTag tag, std::string nam);
	~Button();
	sf::Sprite getSprite() { return Icon; }
	ButtonTag getTag() { return TAG; }
	sf::Vector2f getPosition() { return Icon.getPosition(); }
	std::string  getName() { return _Name; }

private:
	GameDataRef _data;
	sf::Sprite Icon;
	ButtonTag TAG;
	std::string _Name;
};

