#pragma once
#include<SFML/Graphics.hpp>
#include "Button.h"

class Pointer
{
public:
	Pointer(GameDataRef data, std::string name, PlayerButtons PlBut);
	Pointer(GameDataRef data, std::string name, int PadNr);
	~Pointer();


	void Update();
	void setActualButton(Button &but);
	void UpdatePointerPos();

	void checkInputs(int size, sf::Event eve);
	void resetIterator() { buttIterator = 0; }
	int getIterator() { return buttIterator; }
	sf::Sprite getSprite() { return Icon; }

private:
	GameDataRef _data;
	Button* actualButton;
	sf::Sprite Icon;
	int buttIterator;
	PlayerButtons _buttons;
	std::string _Name;
	bool pad;
	int PadNR;
	sf::Clock clock;
};

