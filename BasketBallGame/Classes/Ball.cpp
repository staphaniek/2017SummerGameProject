#include "Ball.h"

USING_NS_CC;

Ball::Ball()
{
}


Ball::~Ball()
{
}

Ball* Ball::spriteWithFile(const char* fileName)
{
	Ball* sprite = new Ball();
	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->initSetting();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Ball::initSetting()
{
	_removed = false;
	_score = 0;
	_speed = 600;
	_angle = 0;
	_arrow = NULL;
	_actionComplete = false;
}

void Ball::incAngle(float dt)
{
	if (_angle > 90) return;
	_angle += dt;
	if(_arrow!=NULL)_arrow->setRotation(-_angle);
}

void Ball::decAngle(float dt)
{
	if (_angle < 0) return;
	_angle -= dt;
	if (_arrow != NULL)_arrow->setRotation(-_angle);
}

void Ball::initArrow()
{
	_arrow = Sprite::create("arrow.png");
	_arrow->setAnchorPoint(Point(0, 0.5f));

	_arrow->setScaleX(3);
//	_arrow->setScaleY(1);

	this->addChild(_arrow);

	_arrow->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
}

void Ball::addArrow()
{
	_arrow->setVisible(true);
}

void Ball::removeArrow()
{
	_arrow->setVisible(false);
}