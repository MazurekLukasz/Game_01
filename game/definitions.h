#pragma once
#include<SFML/Graphics.hpp>




#define SPLASH_STATE_SHOW_TIME 3.0
#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/images/splash.jpg"

#define ROUNDNIB_FONT_FILEPATH "Resources/fonts/ROUNDNIB.ttf"

#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/images/splash.jpg"
#define TITLE_IMG_FILEPATH "Resources/images/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/images/play_button.png"
#define EXIT_BUTTON_FILEPATH "Resources/images/exit_button.png"
#define RETURN_BUTTON_FILEPATH "Resources/images/return_button.png"


// Pointers
#define PLAYER_1_POINTER_FILEPATH "Resources/images/Player1Pointer.tga"
#define PLAYER_2_POINTER_FILEPATH "Resources/images/Player2Pointer.tga"

// ---------------------------
#define LEVEL_BACKGROUND_FILEPATH "Resources/images/bg_level.jpg"
#define LAND_01_FILEPATH "Resources/images/land_01.png"

// -------------------------stone ------------------------------------------------------------------
#define GR_STONE_M_01 "Resources/images/ground/stone/mid_01.png"
#define GR_STONE_LEFT_FILEPATH "Resources/images/ground/stone/left.png"
#define GR_STONE_RIGHT_FILEPATH "Resources/images/ground/stone/right.png"
#define GR_STONE_MT_01 "Resources/images/ground/stone/mid_top_01.png"
#define GR_STONE_MT_02 "Resources/images/ground/stone/mid_top_02.png"
// -------------------------------------------------------------------------------------------------
#define RESS "Resources/images/ground/elements/ress_01.png"





#define MegaMan_FILEPATH "Resources/images/spritesheetmegaman1.png"
#define ICICLE_FILEPATH "Resources/images/icicle.png"
//#define MegaMan_AVATAR_FILEPATH "Resources/images/Megaman_avatar.jpg"
#define MegaMan_AVATAR_FILEPATH "Resources/images/Armature.png"
#define FireMan_FILEPATH "Resources/images/fireman.png"
#define FireMan_AVATAR_FILEPATH "Resources/images/Fireman_avatar.jpg"

#define RED_MegaMan_FILEPATH "Resources/images/red_megaman.png"
#define HP_BAR_FILEPATH "Resources/images/hp_bar_1.png"
#define HP_BAR2_FILEPATH "Resources/images/hp_bar_2.png"
#define FIRE_BALL_FILEPATH "Resources/images/fire_ball.png"

enum MenuState
{
	General,
	CharacterSelect
};

enum ButtonTag
{
	PLAY,
	EXIT,
	RETURN,
	AVATAR
};

struct PlayerButtons {
	sf::Keyboard::Key Left;
	sf::Keyboard::Key Right;
	sf::Keyboard::Key Attack;
	sf::Keyboard::Key Jump;
};

