#include "MainMenuState.h"
#include "LevelState.h"
#include <sstream>
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data): _data(data)
{
	keys.Right = sf::Keyboard::Right;
	keys.Left = sf::Keyboard::Left;
	PlayerIterator = 0;
	ResetFreePlayersMap();

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Init()
{

	//font------------------------------------------
	_data->assets.LoadFont("Roundnib", ROUNDNIB_FONT_FILEPATH);
	_text.setString("PAD 0 IS CONNECTED !");
	_text.setFont(_data->assets.GetFont("Roundnib"));
	_text.setPosition(50, _data->SCREEN_HEIGHT - 80);

	//load textures ---------------------------------------------------------------------------------------
	_data->assets.LoadTexture("Main Menu BG", MAIN_MENU_BACKGROUND_FILEPATH);
	_data->assets.LoadTexture("Title", TITLE_IMG_FILEPATH);
	// Buttons
	_data->assets.LoadTexture("Return Button", RETURN_BUTTON_FILEPATH);
	_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
	_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);

	//Avatars
	_data->assets.LoadTexture("MM Avatar", MegaMan_AVATAR_FILEPATH);
	_data->assets.LoadTexture("FM Avatar", FireMan_AVATAR_FILEPATH);

	//background and title --------------------------------------------------------
	_background.setTexture(this->_data->assets.GetTexture("Main Menu BG"));
	_title.setTexture(this->_data->assets.GetTexture("Title"));

	_title.setPosition(_data->SCREEN_WIDTH / 2 - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);


	// Set pointer texture
	_data->assets.LoadTexture("Pointer", FIRE_BALL_FILEPATH);
	_data->assets.LoadTexture("Player 1 Pointer", PLAYER_1_POINTER_FILEPATH);
	_data->assets.LoadTexture("Player 2 Pointer", PLAYER_2_POINTER_FILEPATH);

	// menu state enum -------------------------------------------------------------------------------------
	CreateGeneralButtons();
	menuState = General;
	CreateStandardPointer();
	std::cout <<"debug" << std::endl;
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		for (const auto &Point : _Pointers)
		{
			Point.second->checkInputs(Buttons.size(), event);
			Point.second->setActualButton(*Buttons.at(Point.second->getIterator()));
			Point.second->UpdatePointerPos();
		}

		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
		else if(event.type == sf::Event::KeyPressed) 
		{
			if (menuState == General)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
			
					ButtonTag tag = Buttons.at(_Pointers["Pointer"]->getIterator())->getTag();

					if (tag == PLAY)
					{
						newMenuState = CharacterSelect;
					}
					else if (tag == EXIT)
					{
						_data->window.close();
					}
					else if (tag == RETURN)
					{
						newMenuState = General;
					}
				}
			}
			else if (menuState == CharacterSelect)
			{
				// ------------------------- KEYBOARD -------------------------------------------------------------
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (!KeyboardPlayer)
					{
						newMenuState = General;
					}
					else if (KeyboardPlayer)
					{
						if (KeyboardReady == true)
						{
							KeyboardReady = false;
						}
						else
						{
							KeyboardPlayer = false;
							KeyboardReady = false;
							freePlayers[KeyboardPlayerName] = true;

							_data->PlayersManager.deletePlayer(checkPlayerNr(KeyboardPlayerName));
							_Pointers.erase(KeyboardPlayerName);
							PlayerIterator--;
						}
					}
				}
				//-------------------------------------------------------------------------
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (KeyboardPlayer)
					{
						if (KeyboardReady == true)
						{
						}
						else 
						{
							_data->PlayersManager.getPlayers().at(KeyboardPlayerName)->setName(Buttons.at(_Pointers[KeyboardPlayerName]->getIterator())->getName());
							KeyboardReady = true;
						}
					}
					else if (!KeyboardPlayer)
					{
						if (isFreePlayer()) 
						{
							KeyboardPlayer = true;
							KeyboardPlayerName = returnFirstFreePlayer();
							freePlayers[KeyboardPlayerName] = false;

							_data->PlayersManager.createPlayer(checkPlayerNr(KeyboardPlayerName), 0, true);
							CreatePointer(KeyboardPlayerName, keys);
							PlayerIterator++;
							std::cout <<"hey" << std::endl;
						}
					}
				}
				
			}
		}//------------------------------ PAD 0 ----------------------------

		else if (event.type == sf::Event::JoystickButtonPressed)
		{
			if (menuState == CharacterSelect)
			{
				if (event.key.code == sf::Joystick::isButtonPressed(0, 1))
				{
					if (padPlayer1.exists)
					{
						if (padPlayer1.ready == true)
						{
						}
						else
						{
							_data->PlayersManager.getPlayers().at(padPlayer1.name)->setName(Buttons.at(_Pointers[padPlayer1.name]->getIterator())->getName());
							padPlayer1.ready = true;
						}
						
					}
					else if (!padPlayer1.exists)
					{
						if (isFreePlayer())
						{
							padPlayer1.exists = true;
							padPlayer1.name = returnFirstFreePlayer();
							freePlayers[padPlayer1.name] = false;

							_data->PlayersManager.createPlayer(checkPlayerNr(padPlayer1.name), 0, false);
							CreatePointer(padPlayer1.name,0);
							PlayerIterator++;
						}
					}
				}

				if (event.key.code == sf::Joystick::isButtonPressed(0, 0))
				{
					if (!padPlayer1.exists)
					{
						newMenuState = General;
					}
					else if(padPlayer1.exists)
					{
						if (padPlayer1.ready == true)
						{
							padPlayer1.ready = false;
						}
						else 
						{
							padPlayer1.exists = false;
							freePlayers[padPlayer1.name] = true;

							_data->PlayersManager.deletePlayer(checkPlayerNr(padPlayer1.name));
							_Pointers.erase(padPlayer1.name);
							PlayerIterator--;
						}
					}
				}
			}
		}
		
	}
}


void MainMenuState::Update(float dt)
{
	if (menuState == CharacterSelect)
	{
		if (checkReady())
		{
			_data->machine.AddState((StateRef)new LevelState(this->_data), true);
		}
	}

	if (newMenuState != menuState)
	{
		// erase buttons
		_data->PlayersManager.ResetPlayers();
		Buttons.clear();
		_Pointers.clear();
		ResetFreePlayersMap();
		ResetPlayersExists();

		// create buttons
		if (newMenuState == General)
		{
			CreateGeneralButtons();
			CreateStandardPointer();
		}
		else if (newMenuState == CharacterSelect)
		{
	
			CreateChSelectButtons();
			//_data->PlayersManager.createPlayer(0,_data->PlayersManager.pad[0]);
		}


		for (const auto &Point : _Pointers)
		{
			Point.second->resetIterator();
			Point.second->setActualButton(*Buttons.at(Point.second->getIterator()));
			Point.second->UpdatePointerPos();
		}
		menuState = newMenuState;
	}
	//-----------------------------------------------------------------
		if (_data->input.IsSpriteClicked(Buttons.at(0)->getSprite(), sf::Mouse::Left, _data->window))
		{
		}
	//-------------------------------------------------------------------------------
		_data->PlayersManager.checkPads();

}

void MainMenuState::Draw(float dt) // ---------------------------------------------------------------
{
	_data->window.clear();
	//_data->window.draw(_background);
	_data->window.draw(_title);

	// Draw buttons
	if (!Buttons.empty())
	{
		for (Button* button : Buttons)
		{
			_data->window.draw(button->getSprite());
		}
	}
	if (!_Pointers.empty())
	{
		for (const auto &Point : _Pointers)
		{
			_data->window.draw(Point.second->getSprite());
		}
	}

	if(sf::Joystick::isConnected(0))
	{
		_data->window.draw(_text);
	}

	_data->window.display();
}


// -----------------------create buttons ---------------------------------------------------

void MainMenuState::CreateGeneralButtons()
{
	Buttons.push_back(new Button(_data, "Play Button", sf::Vector2f((_data->SCREEN_WIDTH / 2) - 200.0f, _data->SCREEN_HEIGHT / 2), PLAY));
	Buttons.push_back(new Button(_data, "Exit Button", sf::Vector2f((_data->SCREEN_WIDTH / 2), _data->SCREEN_HEIGHT / 2), EXIT));
}


void MainMenuState::CreateChSelectButtons()
{
	Buttons.push_back(new Button(_data, "MM Avatar", sf::Vector2f(_data->SCREEN_WIDTH / 2 - 300, _data->SCREEN_HEIGHT / 2), AVATAR,"Mega Man"));
	Buttons.push_back(new Button(_data, "FM Avatar", sf::Vector2f(_data->SCREEN_WIDTH / 2 - 150, _data->SCREEN_HEIGHT / 2), AVATAR, "Fire Man"));
	//Buttons["AVATAR2"] = new Button(_data, "FM Avatar", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),AVATAR);
	//Buttons.push_back(new Button(_data, "Return Button", sf::Vector2f((_data->SCREEN_WIDTH / 2), _data->SCREEN_HEIGHT / 2), RETURN));
}

void MainMenuState::CreateStandardPointer()
{
	_Pointers["Pointer"] = (new Pointer(_data, "Pointer", keys));
	_Pointers["Pointer"]->setActualButton(*Buttons.at(_Pointers["Pointer"]->getIterator()));
	_Pointers["Pointer"]->UpdatePointerPos();
}

void MainMenuState::CreatePointer(std::string nam, PlayerButtons key)
{
	std::string name;
	if (nam == "Player 1")
	{
		name = "Player 1 Pointer";
		
	}
	else if (nam == "Player 2")
	{
		name = "Player 2 Pointer";
	}
	else if (nam == "Player 3")
	{
		name = "Player 1 Pointer";
	}
	else if (nam == "Player 4")
	{
		name = "Player 1 Pointer";
	}
	_Pointers[nam]=(new Pointer(_data, name, key));
	_Pointers[nam]->setActualButton(*Buttons.at(_Pointers[nam]->getIterator()));
	_Pointers[nam]->UpdatePointerPos();
}

void MainMenuState::CreatePointer(std::string nam, int PadNr)
{
	std::string name;
	if (nam == "Player 1")
	{
		name = "Player 1 Pointer";

	}
	else if (nam == "Player 2")
	{
		name = "Player 2 Pointer";
	}
	else if (nam == "Player 3")
	{
		name = "Player 1 Pointer";
	}
	else if (nam == "Player 4")
	{
		name = "Player 1 Pointer";
	}
	_Pointers[nam] = (new Pointer(_data, name, PadNr));
	_Pointers[nam]->setActualButton(*Buttons.at(_Pointers[nam]->getIterator()));
	_Pointers[nam]->UpdatePointerPos();
}


bool MainMenuState::isFreePlayer()
{
	for (const auto &P : freePlayers)
	{
		if (P.second == true)
		{
			return true;
		}
		 
	}
	return false;
}


std::string MainMenuState::returnFirstFreePlayer()
{
	for (const auto &P : freePlayers)
	{
		if (P.second == true)
		{
			return P.first;
		}
	}
	return "Player 1";
}



int MainMenuState::checkPlayerNr(std::string nam)
{
	if (nam == "Player 1")
	{
		return 1;
	}
	else if (nam == "Player 2")
	{
		return 2;
	}
	else if (nam == "Player 3")
	{
		return 3;
	}
	else if (nam == "Player 4")
	{
		return 4;
	}
	return 1;
}


void MainMenuState::ResetFreePlayersMap()
{
	freePlayers["Player 1"] = true;
	freePlayers["Player 2"] = true;
	freePlayers["Player 3"] = true;
	freePlayers["Player 4"] = true;
}

void MainMenuState::ResetPlayersExists() 
{
	padPlayer1.exists = false;
	KeyboardPlayer = false;
	PlayerIterator = 0;
}

bool MainMenuState::checkReady()
{
	if (PlayerIterator == 0)
	{
		return false;
	}
	int count = 0;

	if (KeyboardReady)
	{
		count++;
	}
	if (padPlayer1.ready)
	{
		count++;
	}
	if(count == PlayerIterator)
	{
		return true;
	}
	return false;
}