#include "Obstacle.h"
#include "MyBodyParser.h"
#include "DevConf.h"


USING_NS_CC;

Obstacle::Obstacle()
{
	_type = 1;
	_state = true;
	upSpeed = Vec2(0, 35 + 5 * _level);
	downSpeed = Vec2(0, -(35 + 5 * _level));
}

Obstacle::Obstacle(int type)
{
	_type = type;
	_state = true;
	upSpeed = Vec2(0, 35 + 5 * _level);
	downSpeed = Vec2(0, -(35 + 5 * _level));
}

Obstacle::~Obstacle()
{
}

void Obstacle::addHandFoot()
{
	Point subPos[4];
	Point subAnchor[4];

	// left hand
	subPos[0] = Point(this->getBoundingBox().size.width / 16, this->getBoundingBox().size.height / 2);
	subAnchor[0] = Point(0.9, 0.5);

	// right hand
	subPos[1] = Point(this->getBoundingBox().size.width * 15 / 16, this->getBoundingBox().size.height / 2);
	subAnchor[1] = Point(0.1, 0.5);

	// left foot
	subPos[2] = Point(this->getBoundingBox().size.width / 6, this->getBoundingBox().size.height / 8);
	subAnchor[2] = Point(0.75, 0.75);
	
	// right foot
	subPos[3] = Point(this->getBoundingBox().size.width * 5 / 6, this->getBoundingBox().size.height / 8);
	subAnchor[3] = Point(0.25, 0.75);
	
	for (int i = 0; i < 4; ++i)
	{
		attachHandFoot(i,subAnchor[i], subPos[i]);
		setAnimation(i);
	}
	
}

Obstacle* Obstacle::spriteWithFile(int type)
{
	Obstacle* sprite = new Obstacle(type);
	char fileName[30];
	sprintf(fileName, "obstacle%dbody.png", type);
	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Obstacle::attachHandFoot(int index,Point anchorPoint, Point initPos)
{
	char fileName[30];
	sprintf(fileName, "obstacle%dsub.png", _type);
	auto sprite = Sprite::create(fileName);
	sprite->setAnchorPoint(anchorPoint);
	sprite->setPosition(initPos);
	sprite->setTag(index);
	this->addChild(sprite);
}

void Obstacle::attachPhysicsBody(int index)
{
	MyBodyParser::getInstance()->parseJsonFile("obstacle.json");

	auto body = MyBodyParser::getInstance()->bodyFormJson(this, "body", PhysicsMaterial(1.0, 0.5, 0.1));
	body->setDynamic(false);
	body->setCollisionBitmask(index);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);
}

void Obstacle::attachPhysicsHandFoot(int index)
{
	for (int i = 0; i < 4; ++i)
	{
		auto body = PhysicsBody::createCircle(this->getChildByTag(0)->getBoundingBox().size.width / 2, PhysicsMaterial(0, 0.5, 0.1));

		body->setDynamic(false);
		body->setGravityEnable(false);
		body->setCollisionBitmask(index);
		body->setContactTestBitmask(true);
		this->getChildByTag(i)->setPhysicsBody(body);
	}
}

void Obstacle::setAnimation(int index)
{
	if (index == 0 || index == 3)
	{
		setCWAnimation(index);
	}
	else
	{
		setCCWAnimation(index);
	}
}

void Obstacle::setCWAnimation(int index)
{
	auto anim1 = RotateBy::create(smallAminTime, smallCWDegree);
	auto anim2 = RotateBy::create(largeAnimTime, largeCCWDegree);
	auto anim3 = RotateBy::create(smallAminTime, smallCWDegree);
	auto seq = Sequence::create(anim1, anim2, anim3, NULL);
	auto act = RepeatForever::create(seq);
	this->getChildByTag(index)->runAction(act);
}

void Obstacle::setCCWAnimation(int index)
{
	auto anim1 = RotateBy::create(smallAminTime, smallCCWDegree);
	auto anim2 = RotateBy::create(largeAnimTime, largeCWDegree);
	auto anim3 = RotateBy::create(smallAminTime, smallCCWDegree);
	auto seq = Sequence::create(anim1, anim2, anim3, NULL);
	auto act = RepeatForever::create(seq);
	this->getChildByTag(index)->runAction(act);
}

void Obstacle::resetAnimation()
{
	for (int i = 0; i < 4; ++i)
	{
		this->getChildByTag(i)->stopAllActions();
	}
}

void Obstacle::changeDir()
{
	_state = (!_state);
	setVelocity();
}

void Obstacle::setVelocity()
{
	if (_state)
	{
		this->getPhysicsBody()->setVelocity(upSpeed);
	}
	else
	{
		this->getPhysicsBody()->setVelocity(downSpeed);
	}
}