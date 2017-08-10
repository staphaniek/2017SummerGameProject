#pragma once
#include "cocos2d.h"

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

