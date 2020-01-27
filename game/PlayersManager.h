#pragma once
#include"PlayerController.h"


class PlayersManager
{
public:
	PlayersManager();
	~PlayersManager();

	void checkPads();
	void ShowPadState();
	void InitPadText();

	std::map<std::string, PlayerController*> getPlayers() { return Players; }
	void createPlayer(int playerNR, int padNr, bool keyboard);
	void deletePlayer(int playerNR);
	void ResetPlayers();
	
	bool pad[4];
private:
	std::map<std::string,PlayerController*> Players;
	//sf::Text padConnectedText;
};

