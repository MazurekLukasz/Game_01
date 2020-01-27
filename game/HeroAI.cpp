#include "HeroAI.h"


HeroAI::HeroAI(GameDataRef data, sf::Vector2f spawnPos, sf::Vector2u imageCount, std::string texName):
	Character(data, spawnPos,imageCount, texName)
{
	points[0] = GetPosition().x + 100.0f;
	points[1] = GetPosition().x - 100.0f;
	deltaSpeed = speed;

}


HeroAI::~HeroAI()
{
}

void HeroAI::Update(float dt)
{
	for (Projectile& project : _projectiles)
	{
		project.Update(dt);
	}

	velocity.x *= 0.0001f;
	velocity.y += 981.0f * dt;
	//velocity.x += 40.0f;


	//watchTarget();

	if (haveTarget())
	{
		followTarget();
		Shoot();
	}
	else
	{

		std::cout << "target";
		Patrol();
	}
	


	AnimationController();
	Flip();

	anim.Update(row, start, end, faceRight);
	body.setTextureRect(anim._uvRect);

	collider.move(velocity * dt);
	body.setPosition(collider.getPosition());

	hp_Rect.width = hp_bar.getSize().x * (20.0f/HP);
	color.setTextureRect(hp_Rect);


	if (_clock.getElapsedTime().asSeconds() >= _fireTime)
	{
		canFire = true;
		_clock.restart();
	}


	if (_clockProjectile.getElapsedTime().asSeconds() >= ProjectileLiveTime && !_projectiles.empty())
	{
		_projectiles.erase(_projectiles.begin());
		_clockProjectile.restart();
	}
	fire = false;
}



void HeroAI::Patrol()
{	
	if (GetPosition().x >= points[0])
	{
		deltaSpeed = -speed;
	}

	if(GetPosition().x <= points[1])
	{
		deltaSpeed = speed;
	}
	velocity.x += deltaSpeed;
}
void HeroAI::Wait()
{
	velocity.x = 0;
}

//void HeroAI::setTarget(Character &targ)
//{
	//*target = targ;
//}

void HeroAI::followTarget()
{
	if (canJump && target->GetPosition().y < collider.getPosition().y && target->canHeroJump() )
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpPower);
	}

	if ((target->GetPosition().x - 200.0f) >= collider.getPosition().x)
	{
		velocity.x = speed;
	}
	else if ((target->GetPosition().x + 200.0f) <= collider.getPosition().x)
	{
		velocity.x = -speed;
	}
}

void HeroAI::watchTarget()
{
	if (target->GetPosition().x  >= collider.getPosition().x)
	{
		faceRight = true;
		
	}
	else if (target->GetPosition().x < collider.getPosition().x)
	{
		faceRight = false;
	}
}

bool HeroAI::haveTarget() 
{

	if(target != NULL)
		return true;
	else
		return false;
}

void HeroAI::Shoot() 
{
	if ((abs(target->GetPosition().y - GetPosition().y) <= (collider.getSize().y /2.0f)) && !fire && canFire)
	{
		_clockProjectile.restart();
		fire = true;
		canFire = false;
		_projectiles.push_back(Projectile(_data, 8.0f, collider.getPosition(), "Fire Ball", faceRight));
	}
}