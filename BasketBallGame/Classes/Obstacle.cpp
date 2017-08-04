#include "Obstacle.h"

USING_NS_CC;

Obstacle::Obstacle()
{
	_type = 1;
	_state = IDLE;
}

Obstacle::Obstacle(int type)
{
	_type = type;
	_state = IDLE;
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
	subPos[3] = Point(this->getBoundingBox().size.width / 6, this->getBoundingBox().size.height / 8);
	subAnchor[3] = Point(0.75, 0.75);
	
	// right foot
	subPos[2] = Point(this->getBoundingBox().size.width * 5 / 6, this->getBoundingBox().size.height / 8);
	subAnchor[2] = Point(0.25, 0.75);
	
	for (int i = 0; i < 4; ++i)
	{
		this->attachHandFoot(i,subAnchor[i], subPos[i]);
	}
	setAnimation();
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

void Obstacle::attachPhysicsBody(cocos2d::Ref* object)
{
}

void Obstacle::attachPhysicsHandFoot(cocos2d::Ref* object)
{
}

void Obstacle::setAnimation()
{
	auto up1 = RotateBy::create(1, -25);
	auto up2 = RotateBy::create(2, -50);
	auto down2 = RotateBy::create(2, 50);
	auto down1 = RotateBy::create(1, 25);
	auto handSeq = Sequence::create(up1, down2, up1,NULL);
	auto footSeq = Sequence::create(down1, up2, down1,NULL);
	RepeatForever* action[4];
	action[0] = RepeatForever::create(footSeq);
	action[1] = RepeatForever::create(handSeq);
	action[2] = RepeatForever::create(footSeq);
	action[3] = RepeatForever::create(handSeq);

	this->getChildByTag(0)->runAction(action[0]);
	this->getChildByTag(1)->runAction(action[1]);
	this->getChildByTag(3)->runAction(action[3]);
	this->getChildByTag(2)->runAction(action[2]);
	/*
	for (int i = 0; i < 4; ++i)
	{
		if (i % 2 == 0)
		{
			// hand animation
			this->getChildByTag(i)->runAction(cwRepeat);
		}
		else
		{
			// foot animation
			this->getChildByTag(i)->runAction(ccwRepeat);
		}
	}
	*/
}

void Obstacle::resetAnimation()
{

}