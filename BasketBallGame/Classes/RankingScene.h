#pragma once
#include "cocos2d.h"
#include <string>
using namespace std;

USING_NS_CC;

class RankingScene : public Layer
{
public:

	static Scene* createScene(bool mode);

	virtual bool init();

	CREATE_FUNC(RankingScene);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	void onClickOK(Ref * object);

	RankingScene();
	~RankingScene();
};

