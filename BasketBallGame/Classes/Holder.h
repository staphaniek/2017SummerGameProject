#pragma once
#include "cocos2d.h"

const cocos2d::Color3B rainbow[7] = { cocos2d::Color3B(255, 0 , 0), cocos2d::Color3B(255, 127, 0) , cocos2d::Color3B(255, 255, 0) , cocos2d::Color3B(0, 255, 0) , cocos2d::Color3B(0, 0, 255) , cocos2d::Color3B(75, 0, 130) , cocos2d::Color3B(148, 0, 211) };

class Holder : public cocos2d::Sprite
{
public:
	int _lifeBonus;
	int _ani;


	Holder();
	~Holder();
	Holder(int lifeBonus);
	
	static Holder* spriteWithFile(const char* fileName, int lifeBonus);
};

