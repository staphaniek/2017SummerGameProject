#pragma once
#include "cocos2d.h"

class Ring : public cocos2d::Sprite
{
private:
	bool _goalCheck;
public:
	int _score;
	char _melody[5];
	bool _state;
	bool _goal;
	
	cocos2d::Vec2 upSpeed;
	cocos2d::Vec2 downSpeed;

	Ring();
	~Ring();

	void setGoalCheck();
	void resetGoalCheck();
	bool getGoalCheck();

	void initSetting(float speed, const char* melody);

	void changeDir();
	void setVelocity();

	static Ring* spriteWithFile(const char* fileName, float speed, const char* melody);
};

