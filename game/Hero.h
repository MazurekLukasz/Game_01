#pragma once

#include "Character.h"

class Hero: public Character
{
public:
	Hero(GameDataRef data,int pNr, PlayerButtons butt ,bool keyboard,int joyStickNr, sf::Vector2f spawnPos, sf::Vector2u imageCount, std::string texName);
	~Hero();

	void Control();
	void Update(float dt) override;
	void Fire();
	void Jump();
	void InitHPBar();
	void Friction();
	void setPosition(sf::Vector2f);

private:
	PlayerButtons _buttons;
	bool Keyboard;
	int padNr;
	int playerNr;
};

