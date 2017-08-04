#pragma once
#include "cocos2d.h"

class Obstacle : public cocos2d::Sprite
{
public:
	int _type;
	enum state{IDLE,DEAD} _state;

	cocos2d::Sprite* _leftHand;
	cocos2d::Sprite* _rightHand;
	cocos2d::Sprite* _leftFoot;
	cocos2d::Sprite* _rightFoot;

	static Obstacle* spriteWithFile(int type);
	void addHandFoot();
	void attachHandFoot(int index, cocos2d::Point anchorPoint, cocos2d::Point initPos);
	void attachPhysicsBody(cocos2d::Ref* object);
	void attachPhysicsHandFoot(cocos2d::Ref* object);
	void setAnimation();
	void resetAnimation();

	Obstacle();
	Obstacle(int type);
	~Obstacle();
};