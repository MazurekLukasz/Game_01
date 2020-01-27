#include "PlayersManager.h"
#include <iostream>
PlayersManager::PlayersManager()
{
	checkPads();
	//Players.push_back(new PlayerController(0, pad[0]));
	//std::cout << "Player size:"<< playerCount<< std::endl;
	//std::cout << "Hava a pad ?:" << pad[0] << std::endl;
}

PlayersManager::~PlayersManager()
{
}

void PlayersManager::checkPads()
{
	for (unsigned int i = 0; i <= 3 ;i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			pad[i] = true;
		}
		else
		{
			pad[i] = false;
		}
	}
}


void PlayersManager::ShowPadState()
{
	//if (sf::Joystick::isConnected(0))
	//{
	//	window->draw(padConnectedText);
	//}
}

void PlayersManager::InitPadText()
{
	//font
	//_assets->LoadFont("Roundnib", ROUNDNIB_FONT_FILEPATH);
	//padConnectedText.setString("PAD 1 IS CONNECTED !");
	//padConnectedText.setFont(_assets->GetFont("Roundnib"));
	//padConnectedText.setPosition(30, SCREEN_HEIGHT - 30);
}

void PlayersManager::createPlayer(int playerNR,int padNr,bool keyboard)
{
	switch (playerNR)
	{
	case 1:
		Players["Player 1"] = new PlayerController(1,keyboard, padNr);
		break;
	case 2:
		Players["Player 2"] = new PlayerController(2,keyboard, padNr);
		break;
	case 3:
		Players["Player 3"] = new PlayerController(3, keyboard, padNr);
		break;
	case 4:
		Players["Player 4"] = new PlayerController(4, keyboard, padNr);
		break;
	}
}

void PlayersManager::deletePlayer(int playerNR)
{
	switch (playerNR)
	{
	case 1:
		Players.erase("Player 1");
		break;
	case 2:
		Players.erase("Player 2");
		break;
	case 3:
		Players.erase("Player 3");
		break;
	case 4:
		Players.erase("Player 4");
		break;
	}
}


void PlayersManager::ResetPlayers()
{
	Players.clear();
}
