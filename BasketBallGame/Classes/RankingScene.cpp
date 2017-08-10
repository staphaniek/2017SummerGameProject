#include "RankingScene.h"

// 0 : startScene에서 넘어온 경우, 1 : Game이 끝났을 때 불러진 경우
int _mode;

Scene* RankingScene::createScene(int mode)
{
	// scene : autorelease object
	auto scene = Scene::create();

	// layer : autorelease object
	auto layer = RankingScene::create();

	_mode = mode;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

RankingScene::RankingScene()
{
}


RankingScene::~RankingScene()
{
}

bool RankingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto back = Sprite::create("rankingscenebg.png");
	float scale = winSize.height / back->getContentSize().height;
	back->setScale(scale);
	back->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(back);
	auto backSize = winSize;// back->getBoundingBox().size;

	Point rankingpos[10] = {
		Point(backSize.width * 1 / 10, backSize.height),
		Point(backSize.width * 1 / 10, backSize.height * 7 / 8),
		Point(backSize.width * 1 / 10, backSize.height * 6 / 8),
		Point(backSize.width * 1 / 10, backSize.height * 5 / 8),
		Point(backSize.width * 1 / 10, backSize.height * 4 / 8),
		Point(backSize.width * 9 / 10, backSize.height),
		Point(backSize.width * 9 / 10, backSize.height * 7 / 8),
		Point(backSize.width * 9 / 10, backSize.height * 6 / 8),
		Point(backSize.width * 9 / 10, backSize.height * 5 / 8),
		Point(backSize.width * 9 / 10, backSize.height * 4 / 8),
	};

	for (int i = 0; i < 10; i++)
	{
		auto unit = Sprite::create("rankingunit.png");
		unit->setAnchorPoint(Point(0, 0));
//		unit->setScale(scale);
		unit->setPosition(rankingpos[i]);
		back->addChild(unit);
	}

	auto rankingnumber = Sprite::create("rankingnumber.png");
	rankingnumber->setPosition(Point(winSize.width / 2, winSize.height / 2));
	back->addChild(rankingnumber);



	return true;
}