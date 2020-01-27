#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Collider.h"


class Projectile
{
public:
	Projectile(GameDataRef data, float radius, sf::Vector2f StartPos, std::string name, bool faceRight);
	~Projectile();

	void Draw();
	void Update(float dt);
	Collider GetCollider() { return Collider(body); }

private:
	GameDataRef _data;
	sf::RectangleShape body;

	bool _faceRight;
	float _speed = 350.0f;
};

