#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Game.h"
#include "Collider.h"
#include "Projectile.h"
#include "definitions.h"

class Character
{
public:
	Character(GameDataRef data, sf::Vector2f spawnPos, sf::Vector2u imageCount, std::string texName);
	~Character();

	virtual void Update(float dt) {}

	void Draw();
	void Flip();
	void getDamage(float damage) { this->HP -= damage; }
	bool isDeath();

	void OnCollision(sf::Vector2f direction);
	void AnimationController();
	void DrawHPBar() { _data->window.draw(hp_bar); _data->window.draw(color); }


	sf::Vector2f GetPosition() { return collider.getPosition(); }
	Collider GetCollider() { return Collider(collider); }
	bool canHeroJump() { return canJump; }

	void setTarget(Character* targ) {
		target = targ;
	}
	Character* getTarget() { return target; }

public:
	std::vector<Projectile> _projectiles;
	sf::Vector2f direction;
protected:
	sf::Vector2f velocity;
	GameDataRef _data;
	sf::RectangleShape body;
	sf::RectangleShape collider;

	sf::RectangleShape hp_bar;
	sf::RectangleShape color;
	sf::IntRect hp_Rect;
	
	Animation anim;
	sf::Clock _clock;
	sf::Clock _clockProjectile;


	Character* target;

	float _fireTime;

	unsigned int row, start, end;
	float speed = 200.0f;

	bool canJump;
	bool fire;
	bool canFire;
	bool faceRight;
	float jumpPower = 100.0f;
	float ProjectileLiveTime = 1.2f;
	float HP = 20.0f;



};

