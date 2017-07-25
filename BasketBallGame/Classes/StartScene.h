#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"

const int BGTAG = 100;

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	Ball* _ball;
	void initBall();
	Ball* createBall(cocos2d::Vec2 &pos);
	void attachBallbody(Ball* ball);

	cocos2d::Vec2 ring1UpSpeed = cocos2d::Vec2(0,25);
	cocos2d::Vec2 ring1DownSpeed = cocos2d::Vec2(0, -25);
	cocos2d::Vec2 ring2UpSpeed = cocos2d::Vec2(0, 30);
	cocos2d::Vec2 ring2DownSpeed = cocos2d::Vec2(0, -30);
	cocos2d::Vec2 ring3UpSpeed = cocos2d::Vec2(0, 35);
	cocos2d::Vec2 ring3DownSpeed = cocos2d::Vec2(0, -35);
	cocos2d::Vec2 ring4UpSpeed = cocos2d::Vec2(0, 40);
	cocos2d::Vec2 ring4DownSpeed = cocos2d::Vec2(0, -40);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

	cocos2d::LabelTTF *_labelScore;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	void onClickThrow(Ref* object);

	void createBG();
	void createScore();

	void update(float fDelta);

	bool keyCheck[128];
	int _score;
	int _life;

	void initSetting();

	bool isLeft;
	bool isRight;
	bool isDown;
	bool isUp;
	bool isJump;
	bool isThrow;

private:
	cocos2d::PhysicsWorld *sceneWorld;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	bool onContactBegin(cocos2d::PhysicsContact &contact);

};

#endif // __START_SCENE_H__
