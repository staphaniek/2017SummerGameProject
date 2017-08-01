#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Ring.h"

const int BGTAG = 100;

class StartScene : public cocos2d::Layer
{
private:
	int _life;
public:
    static cocos2d::Scene* createScene();

	Ball* _ball;
	Ball* initBall(cocos2d::Vec2 &pos);
	void createBall();

	Ring* ring[4];
	Ring* createRing(int score, int index, cocos2d::Color3B color, const char* melody);

	float ringSpeed[4] = { 25,30,35,40 };

	int _score;

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

	cocos2d::LabelTTF *_labelScore;
	cocos2d::LabelTTF *_labelLife;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	void onClickThrow(Ref* object);

	void attachGoal(Ring* ring,int index, const char* mode);

	void createBG();
	void createLife();
	bool updateLife(int amount);

	void createBasket();

	void createScore();
	void updateScore();
	bool isScoreChanged;

	void update(float fDelta);

	bool keyCheck[128];

	void initSetting();
	void gameOver(int score);

	bool isLeft;
	bool isRight;
	bool isDown;
	bool isUp;
	bool isThrow;
	bool isBall;

private:
	cocos2d::PhysicsWorld *sceneWorld;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	bool onContactBegin(cocos2d::PhysicsContact &contact);

};

#endif // __START_SCENE_H__
