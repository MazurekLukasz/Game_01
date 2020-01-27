#include "Projectile.h"



Projectile::Projectile(GameDataRef data, float radius, sf::Vector2f StartPos, std::string name, bool faceRight):
	_data(data)
{
	_faceRight = faceRight;
	body.setSize(sf::Vector2f(radius*2*2,radius*2*2));
	float delay = 50.0f;

	if(faceRight)
	{
		body.setPosition(StartPos.x+ delay, StartPos.y);
	}
	else
	{
		body.setPosition(StartPos.x - delay , StartPos.y);
	}
	
	
	body.setOrigin(radius,radius);
	body.setTexture(&_data->assets.GetTexture(name));
}

void Projectile::Update(float dt)
{
	if (_faceRight)
	{
		body.move(_speed *dt, 0);
	}
	else
	{
		body.move(- _speed *dt, 0);
	}

}

Projectile::~Projectile()
{
}

void Projectile::Draw()
{
	_data->window.draw(body);
}