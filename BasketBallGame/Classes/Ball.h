#include "cocos2d.h"

const int BALLTAG = 1;
const int BALLSIZE = 30;

class Ball : public cocos2d::Sprite
{
public:
	int _score;
	float _speed;
	float _angle;
	bool _actionComplete;
	cocos2d::Sprite* _arrow;
	Ball();
	~Ball();

	static Ball* spriteWithFile(const char* fileName);

	void initSetting();

	void incAngle(float dt);
	void decAngle(float dt);

	void initArrow();
	void addArrow();
	void removeArrow();
};