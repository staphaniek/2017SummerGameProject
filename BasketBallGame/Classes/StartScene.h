#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(StartScene);
	virtual bool init();
	cocos2d::MenuItemImage* button[3];

	int _select;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	void onClickStart(Ref *object);
	void onClickExit(Ref *object);
	void onClickRanking(Ref *object);
};

#endif // __START_SCENE_H__
