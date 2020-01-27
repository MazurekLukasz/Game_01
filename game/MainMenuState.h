#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "definitions.h"
#include "Button.h"
#include "Pointer.h"
#include<map>

struct PadPlayer
{
	bool exists;
	std::string name;
	bool ready;
};

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);
	~MainMenuState();

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void CreateGeneralButtons();
	void CreateChSelectButtons();
	void CreateStandardPointer();
	void CreatePointer(std::string player, PlayerButtons key);
	void CreatePointer(std::string player, int padNr);
	void ResetFreePlayersMap();
	void ResetPlayersExists();
	bool checkReady();

	bool isFreePlayer();
	std::string returnFirstFreePlayer();
	int checkPlayerNr(std::string);

private:
	GameDataRef _data;
	sf::Sprite _background;
	sf::Sprite _title;
	sf::Text _text;

	std::vector<Button*> Buttons;
	std::map<std::string,Pointer*> _Pointers;
	std::map<std::string,bool> freePlayers;

	MenuState menuState;
	MenuState newMenuState;
	PlayerButtons keys;
	int PlayerIterator;


	
	bool KeyboardPlayer;
	std::string KeyboardPlayerName;
	bool KeyboardReady;

	PadPlayer padPlayer1;
	
};

