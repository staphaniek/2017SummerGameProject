#pragma once
#include "cocos2d.h"
#include <string>
using namespace std;

USING_NS_CC;

class RankingScene : public Layer
{
public:

	static Scene* createScene(int mode);

	virtual bool init();

	CREATE_FUNC(RankingScene);

	RankingScene();
	~RankingScene();
};

