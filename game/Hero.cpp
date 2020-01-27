#include "Hero.h"

Hero::Hero(GameDataRef data, int pNr, PlayerButtons butt, bool keyboard, int joyStickNr, sf::Vector2f spawnPos, sf::Vector2u imageCount, std::string texName):
	Character(data,spawnPos,imageCount,texName)
{
	playerNr = pNr;
	_buttons = butt;
	Keyboard = keyboard;
	padNr = joyStickNr;

	InitHPBar();

}

Hero::~Hero()
{
	std::cout <<"Hero is Death"<< std::endl;
}

void Hero::Control() 
{
	//velocity.x *= 0.0001f;
	if (Keyboard)
	{
		if (sf::Keyboard::isKeyPressed(_buttons.Left))
			velocity.x -= speed;

		if (sf::Keyboard::isKeyPressed(_buttons.Right))
			velocity.x += speed;

		if (sf::Keyboard::isKeyPressed(_buttons.Attack) && !fire && canFire)
		{
			Fire();
		}

		if ((sf::Keyboard::isKeyPressed(_buttons.Jump)) && canJump)
		{
			Jump();
		}

	}
	else
	{
		// If keyboard false then Use Pad
		velocity.x += speed * (sf::Joystick::getAxisPosition(padNr, sf::Joystick::X) / 100);

		if (abs(sf::Joystick::getAxisPosition(padNr, sf::Joystick::X) / 100) <= 0.15)
		{
			velocity.x = 0;
		}

		if ((sf::Joystick::isButtonPressed(padNr, 2)) && !fire && canFire)
		{
			Fire();
		}

		if (sf::Joystick::isButtonPressed(padNr, 0) && canJump)
		{
			Jump();
		}
	}
}


void Hero::Update(float dt)
{
	Friction();
	//-----------------------------------------------------------------------------------------------------------
	hp_bar.setPosition(sf::Vector2f(_data->view.getCenter().x - (_data->SCREEN_WIDTH / 2) + +15.0f + ((playerNr - 1) * 150), _data->view.getCenter().y - (_data->SCREEN_HEIGHT / 2) + 15.0f));
	color.setPosition(hp_bar.getPosition());
	hp_Rect.width = hp_bar.getSize().x * (20.0f / HP);
	color.setTextureRect(hp_Rect);

	for (Projectile& project : _projectiles)
	{
		project.Update(dt);
	}
	//-----------------------------------------------------------------------------------------------------------------
	Control();
	AnimationController();
	Flip();

	velocity.y += 981.0f * dt;

	anim.Update(row, start, end, faceRight);
	body.setTextureRect(anim._uvRect);
	//body.setFillColor(sf::Color(180, 20, 180));
	collider.move(velocity * dt);
	body.setPosition(collider.getPosition());

	if (_clock.getElapsedTime().asSeconds() >= _fireTime)
	{
		canFire = true;

	}

	if (_clockProjectile.getElapsedTime().asSeconds() >= ProjectileLiveTime && !_projectiles.empty())
	{
		_projectiles.erase(_projectiles.begin());
		_clockProjectile.restart();
	}
	fire = false;

	if (velocity.y > 0)
	{
		canJump = false;
	}
}

void Hero::Fire()
{
	_clockProjectile.restart();
	_clock.restart();
	canFire = false;
	fire = true;
	_projectiles.push_back(Projectile(_data, 8.0f, collider.getPosition(), "Icicle", faceRight));
}

void Hero::Jump()
{
	canJump = false;
	velocity.y = -sqrtf(2.0f * 981.0f * jumpPower);
}

void Hero::Friction()
{
	velocity.x *= 0.0001f;
}

void Hero::InitHPBar()
{
	_data->assets.LoadTexture("Hp Bar", HP_BAR_FILEPATH);
	hp_bar.setTexture(&_data->assets.GetTexture("Hp Bar"));
	hp_bar.setSize(sf::Vector2f(143, 40));
	hp_bar.setPosition(sf::Vector2f(_data->view.getCenter().x - (_data->SCREEN_WIDTH / 2) + 15.0f + ((playerNr -1) * 150), _data->view.getCenter().y - (_data->SCREEN_HEIGHT / 2) + 15.0f));

	_data->assets.LoadTexture("Hp Bar2", HP_BAR2_FILEPATH);
	color.setTexture(&_data->assets.GetTexture("Hp Bar2"));
	color.setSize(hp_bar.getSize());
	color.setPosition(hp_bar.getPosition());

	hp_Rect.height = hp_bar.getSize().y;
}

void Hero::setPosition(sf::Vector2f point)
{
	collider.setPosition(point);
	body.setPosition(collider.getPosition());
}