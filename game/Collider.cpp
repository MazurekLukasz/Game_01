#include "Collider.h"



Collider::Collider(sf::RectangleShape& body): body(body)
{
}

void Collider::Move(float dx, float dy)
{
	body.move(dx,dy);
}


bool Collider::CheckCollision(Collider&  other, sf::Vector2f& direction, float push)
{
	float deltaX = other.getPosition().x - getPosition().x;
	float deltaY = other.getPosition().y - getPosition().y;

	float intersectX = abs(deltaX) - (other.getHalfSize().x + getHalfSize().x);
	float intersectY = abs(deltaY) - (other.getHalfSize().y + getHalfSize().y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f),1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else 
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f,intersectY * (1.0f - push));
				other.Move(0.0f ,-intersectY * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				Move(0.0f ,-intersectY * (1.0f - push));
				other.Move(0.0f , intersectY * push);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}

		return true;
	}
	return false;
}


sf::Vector2f Collider::getPosition()
{
	return body.getPosition();
}

sf::Vector2f Collider::getHalfSize()
{
	return body.getSize() / 2.0f;
}

Collider::~Collider()
{
}
