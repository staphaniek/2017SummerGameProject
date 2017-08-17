#pragma once
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	GameOverScene();
	~GameOverScene();

	int _select;
	cocos2d::MenuItemImage* button1;
	cocos2d::MenuItemImage* button2;

	static cocos2d::Scene* createScene(int score);

	CREATE_FUNC(GameOverScene);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	virtual bool init();

	void onClickRestart(Ref *object);
	void onClickHome(Ref *object);
};

