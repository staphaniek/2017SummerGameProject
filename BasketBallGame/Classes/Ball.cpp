#include "Ball.h"

USING_NS_CC;

Ball::Ball()
{
	_speed = 0;
	_maxSpeed = 1000;
	_gaugeState = true;
	_throwState = false;
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
		sprite->initArrow();
		sprite->initGauge();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Ball::updateGauge()
{
	if (_gaugeState)
	{
		_speed = _speed + 10;
		if (_speed >= _maxSpeed)
		{
			_gaugeState = false;
		}
		else
		{
			float scale = _speed / _maxSpeed;
			_gaugeBar->setScaleX(scale);
		}
	}
	else
	{
		_speed = _speed - 10;
		if (_speed <= 0)
		{
			float scale = _speed / _maxSpeed;
			_gaugeBar->setScaleX(scale);
			_gaugeState = true;
		}
		else
		{
			float scale = _speed / _maxSpeed;
			_gaugeBar->setScaleX(scale);
		}
	}
}

void Ball::initSetting()
{
	_removed = false;
	_score = 0;
	_angle = 0;
	_arrow = NULL;
	_actionComplete = false;
}

void Ball::incAngle(float dt)
{
	if (_angle >= 90) return;
	_angle += dt;
	if(_arrow!=NULL)_arrow->setRotation(-_angle);
}

void Ball::decAngle(float dt)
{
	if (_angle <= 0) return;
	_angle -= dt;
	if (_arrow != NULL)_arrow->setRotation(-_angle);
}

void Ball::initArrow()
{
	_arrow = Sprite::create("arrow.png");
	_arrow->setAnchorPoint(Point(0, 0.5f));

	_arrow->setScaleX(0.3);
	_arrow->setScaleY(0.15);

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

void Ball::initGauge()
{
	_gaugeOutline = Sprite::create("gaugeoutline.png");
	_gaugeOutline->setAnchorPoint(Point(0.5, 1));
	_gaugeOutline->setPosition(this->getContentSize().width / 2, -10);
	this->addChild(_gaugeOutline,1);
	_gaugeBar = Sprite::create("gaugebar.png");
	_gaugeBar->setAnchorPoint(Point(0, 0));
	_gaugeBar->setPosition(2, 2);
	_gaugeOutline->addChild(_gaugeBar,-1);
	removeGauge();
}

void Ball::addGauge()
{
	_gaugeBar->setVisible(true);
	_gaugeOutline->setVisible(true);
}

void Ball::removeGauge()
{
	_gaugeBar->setVisible(false);
	_gaugeOutline->setVisible(false);
}