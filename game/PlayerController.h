#pragma once

#include<SFML/Graphics.hpp>
#include "definitions.h"


class PlayerController
{
public:
	PlayerController(unsigned int PNr, bool keyboard, int padNr);
	PlayerController(unsigned int PNr,bool keyboard);
	~PlayerController();

	PlayerButtons getButtons() { return _buttons; }
	bool isKeyboard() { return Keyboard; }
	void setName(std::string nam) { name = nam; }
	std::string getName() { return name; }
	int getPadNr() { return joystickNr; }
	void setReady() { Ready = true; }
	void setUnready() { Ready = false; }
	bool returnReady() { return Ready; }

private:
	PlayerButtons _buttons;
	bool Keyboard;
	std::string name;

	int playerNr;
	int joystickNr;
	bool Ready;
};

