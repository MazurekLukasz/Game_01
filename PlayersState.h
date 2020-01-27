#pragma once
#include"PlayerController.h"

class PlayersState
{
public:
	PlayersState();
	~PlayersState();
	PlayerController* getPlayerController(unsigned int nr) { return Players.at(nr); }

private:
	std::vector<PlayerController*> Players;

	bool pad0, pad1, pad2, pad3;
	bool Player1, Player2, Player3, Player4;
};

