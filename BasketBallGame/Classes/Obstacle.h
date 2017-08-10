#pragma once
#include "cocos2d.h"

const float smallCWDegree = 25.0f;
const float largeCWDegree = 50.0f;
const float smallCCWDegree = -25.0f;
const float largeCCWDegree = -50.0f;
const float smallAminTime = 0.5f;
const float largeAnimTime = 1.0f;

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
	void attachPhysicsBody(int index);
	void attachPhysicsHandFoot(int index);

	void setAnimation(int index);
	void setCWAnimation(int index);
	void setCCWAnimation(int index);
	void resetAnimation();

	Obstacle();
	Obstacle(int type);
	~Obstacle();
};