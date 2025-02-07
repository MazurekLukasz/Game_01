#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy);

	bool CheckCollision(Collider& other, sf::Vector2f& direction, float push);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();

private:
	sf::RectangleShape& body;
};

