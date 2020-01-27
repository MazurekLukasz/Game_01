#pragma once
#include "Character.h"

class HeroAI: public Character
{
public:
	HeroAI(GameDataRef data, sf::Vector2f spawnPos,sf::Vector2u imageCount, std::string texName);
	~HeroAI();

	void Update(float dt) override;
	void Patrol();
	void Wait();
	void followTarget();
	bool haveTarget();
	void watchTarget();
	void Shoot();
	//void setTarget(Character &targ);

private:
	//Character* target;
	float points[2];
	float deltaSpeed;
	float width;


};

