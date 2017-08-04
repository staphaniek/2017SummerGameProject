#include "cocos2d.h"

class Ball : public cocos2d::Sprite
{
public:
	bool _removed;
	int _score;
	float _speed;
	float _maxSpeed;
	float _angle;
	bool _actionComplete;
	bool _throwState;

	cocos2d::Sprite* _gaugeBar;
	cocos2d::Sprite* _gaugeOutline;
	bool _gaugeState; // true : up, false : down
	void updateGauge();
	void addGauge();
	void removeGauge();
	void initGauge();

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