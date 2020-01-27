#include "Character.h"

Character::Character(GameDataRef data, sf::Vector2f spawnPos, sf::Vector2u imageCount, std::string texName):
	_data(data), anim(data, imageCount, texName)
{
	this->_fireTime = 0.5f;
	this->row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100, 100));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(spawnPos);
	body.setTexture(&_data->assets.GetTexture(texName));

	collider.setSize(sf::Vector2f(body.getSize().x - 30.0f, body.getSize().y - 40.0f));
	collider.setOrigin(collider.getSize() / 2.0f);
	collider.setPosition(body.getPosition());
}

void Character::AnimationController()
{
	if (anim.canChangeAnimation())
	{
		if (!canJump)
		{
			// In the air
			if (fire)
			{
				// i am in the air, and I will make a shot
				row = 3;
				start = 0;
				end = 2;
				anim.DisableAnimChange();
			}
			else
			{
				// I am just in the air
				row = 2;
				start = 0;
				end = 2;

			}
		}
		else
		{
			// on the ground
			if (fabs(velocity.x) < 0.010f && fire)
			{
				// shot in place
				row = 4;
				start = 0;
				end = 0;
				anim.DisableAnimChange();
			}
			else if (fabs(velocity.x) >= 0.010f  && fire)
			{
				// shot in move
				row = 5;
				end = 2;
				start = 0;
				anim.DisableAnimChange();
			}
			else if (fabs(velocity.x) >= 0.010f)
			{
				// movement
				row = 1;
				end = 2;
				start = 0;

			}
			else //if (fabs(velocity.x) < 0.01f)
			{
				// idle
				row = 0;
				end = 2;
				start = 0;

			}

		}
	}
	
}

void Character::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		// collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision on the right
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		// collision on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		// collision on the top
		velocity.y = 0.0f;
	}
}

bool Character::isDeath()
{

	if (HP <= 0.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Character::Flip()
{
	if (velocity.x > 0.0f)
		faceRight = true;
	else if (velocity.x < 0.0f)
		faceRight = false;
}

void Character::Draw()
{
	_data->window.draw(body);

	for (Projectile& project : _projectiles)
	{
		project.Draw();
	}
}

Character::~Character()
{
	std::cout << "you are already death" << std::endl;
}

