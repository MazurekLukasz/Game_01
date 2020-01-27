#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"


class Animation
{
public:
	Animation(GameDataRef data, sf::Vector2u imageCount, std::string texName);
	~Animation();

	void Update(int row, unsigned int start, unsigned int end, bool FaceRight);
	bool canChangeAnimation() { return canChange; }
	void DisableAnimChange() { canChange = false; }

public:
	sf::IntRect _uvRect;
private:
	GameDataRef _data;
	sf::Vector2u _imageCount;
	sf::Vector2u _currentImage;
	sf::Clock _clock;
	
	float _switchTime;
	bool canChange;
};

