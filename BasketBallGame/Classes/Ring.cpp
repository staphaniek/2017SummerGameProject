#include "Ring.h"
#define UP true
#define DOWN false

USING_NS_CC;

Ring::Ring()
{
}


Ring::~Ring()
{
}

void Ring::initSetting(float speed, const char* melody)
{
	_goal = false;
	_score = 0;
	_state = UP;
	_goalCheck = false;
	upSpeed = Vec2(0,speed);
	downSpeed = Vec2(0,-speed);
	strcpy(_melody, melody);
}

Ring* Ring::spriteWithFile(const char* fileName, float speed, const char* melody)
{
	Ring* sprite = new Ring();
	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->initSetting(speed, melody);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Ring::changeDir()
{
	_state = (!_state);
	setVelocity();
}

void Ring::setVelocity()
{
	if (_state == UP)
	{
		this->getPhysicsBody()->setVelocity(upSpeed);
	}
	else
	{
		this->getPhysicsBody()->setVelocity(downSpeed);
	}
}

void Ring::setGoalCheck()
{
	_goalCheck = true;
}

void Ring::resetGoalCheck()
{
	_goalCheck = false;
}

bool Ring::getGoalCheck()
{
	return _goalCheck;
}