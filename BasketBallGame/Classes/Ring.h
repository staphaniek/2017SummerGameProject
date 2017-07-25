#pragma once
#include "cocos2d.h"

const int RING1TAG = 11;
const int RING2TAG = 12;
const int RING3TAG = 13;
const int RING4TAG = 14;
const int RING1UPTAG = 15;
const int RING2UPTAG = 17;
const int RING3UPTAG = 19;
const int RING4UPTAG = 21;
const int RING1DOWNTAG = 16;
const int RING2DOWNTAG = 18;
const int RING3DOWNTAG = 20;
const int RING4DOWNTAG = 22;
const int RING1SIZE = 200;
const int RING2SIZE = 160;
const int RING3SIZE = 120;
const int RING4SIZE = 100;

class Ring : public cocos2d::Sprite
{
public:
	int _score;

	Ring();
	~Ring();

	static Ring* spriteWithFile(const char* fileName);
};

