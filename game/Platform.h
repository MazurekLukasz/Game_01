#pragma once

#include<SFML/Graphics.hpp>
#include "Game.h"
#include "Collider.h"

class Platform
{
public:
	Platform(GameDataRef data, sf::Vector2f size, sf::Vector2f position, std::string name);
	~Platform();

	void Draw();
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	GameDataRef _data;
};

