#include "RankingScene.h"
#include "DatabaseManager.h"
#include "StartScene.h"
#include "GameOverScene.h"

// 0 : startScene에서 넘어온 경우, 1 : Game이 끝났을 때 불러진 경우
bool _mode = false;
Score now;

Scene* RankingScene::createScene(bool mode, string name, int score)
{
	// scene : autorelease object
	auto scene = Scene::create();

	// layer : autorelease object
	auto layer = RankingScene::create();

	_mode = mode;
	
	now = Score();
	now._name = strdup(name.c_str());
	now.score = score;

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
	float scale = winSize.width / back->getContentSize().width;
	back->setScale(scale);
	back->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(back);
	auto backSize = winSize;// back->getBoundingBox().size;

	Point rankingpos[10] = {
		Point(backSize.width * 1 / 11, backSize.height * 15 / 16),
		Point(backSize.width * 1 / 11, backSize.height * 12 / 16),
		Point(backSize.width * 1 / 11, backSize.height * 9 / 16),
		Point(backSize.width * 1 / 11, backSize.height * 6 / 16),
		Point(backSize.width * 1 / 11, backSize.height * 3 / 16),
		Point(backSize.width * 9 / 10, backSize.height * 15 / 16),
		Point(backSize.width * 9 / 10, backSize.height * 12 / 16),
		Point(backSize.width * 9 / 10, backSize.height * 9 / 16),
		Point(backSize.width * 9 / 10, backSize.height * 6 / 16),
		Point(backSize.width * 9 / 10, backSize.height * 3 / 16),
	};

	for (int i = 0; i < 10; i++)
	{
		// ranking unit 배경
		auto unit = Sprite::create("rankingunit.png");
		unit->setAnchorPoint(Point(0, 0));
		unit->setPosition(rankingpos[i]);
		unit->setTag(i);
		back->addChild(unit);

		// ranking position 배경
		auto rankingNumberbg = Sprite::create("rankingnumber.png");
		if (i == 0)
		{
			// 금왕관
			rankingNumberbg->setColor(Color3B(255, 215, 0)); // gold
			auto crown = Sprite::create("goldmedal.png");
			crown->setAnchorPoint(Point(0, 0));
			crown->setPosition(Point(-12, rankingNumberbg->getContentSize().height - 15));
			rankingNumberbg->addChild(crown);
		}
		else if (i == 1)
		{
			// 은왕관
			rankingNumberbg->setColor(Color3B(192, 192, 192));
			auto crown = Sprite::create("silvermedal.png");
			crown->setAnchorPoint(Point(0, 0));
			crown->setPosition(Point(-30, rankingNumberbg->getContentSize().height - 40));
			rankingNumberbg->addChild(crown);
		}
		else if (i == 2)
		{
			// 동왕관
			rankingNumberbg->setColor(Color3B(215, 127, 50));
			auto crown= Sprite::create("bronzemedal.png");
			crown->setAnchorPoint(Point(0,0));
			crown->setPosition(Point(-8, rankingNumberbg->getContentSize().height));
			rankingNumberbg->addChild(crown);
		}
		else
		{
			// 나머지 배경들
			rankingNumberbg->setColor(Color3B(255, 156, 63));
		}
		rankingNumberbg->setPosition(Point(unit->getContentSize().width / 7.0, unit->getContentSize().height / 2.0));
		unit->addChild(rankingNumberbg);

		// 랭킹 숫자
		char tmp[3];
		sprintf(tmp, "%d", i + 1);
		auto rankingNumber = LabelTTF::create(tmp, "Arial", 40);
		rankingNumber->setPosition(Point(rankingNumberbg->getContentSize().width / 2, rankingNumberbg->getContentSize().height / 2));
		rankingNumberbg->addChild(rankingNumber);
	}

/*	DatabaseManager::getInstance()->createDB();
	DatabaseManager::getInstance()->insertDB("rnjswlsh", 230);
	DatabaseManager::getInstance()->insertDB("rnjswlsh1", 240);
	DatabaseManager::getInstance()->insertDB("rnjswlsh2", 250);
	DatabaseManager::getInstance()->insertDB("rnjswlsh3", 260);
*/
	// rankList 가져오기
	list<Score*> rankList = DatabaseManager::getInstance()->selectDB();
	int size = rankList.size();

	for (int i = 0; i < size; i++)
	{
		auto unit = back->getChildByTag(i);
		char tmp[50];
		sprintf(tmp, "%s", rankList.front()->_name);
		auto nameLabel = LabelTTF::create(tmp, "Arial", 40);
		nameLabel->setAnchorPoint(Point(0, 0.5));
		nameLabel->setHorizontalAlignment(TextHAlignment::LEFT);
		sprintf(tmp, "%d", rankList.front()->score);
		auto scoreLabel = LabelTTF::create(tmp, "Arial", 40);
		if (strcmp(now._name, rankList.front()->_name) == 0 && now.score == rankList.front()->score)
		{
			auto action1 = FadeIn::create(0.5);
			auto action2 = FadeOut::create(0.5);
			nameLabel->setFontFillColor(Color3B(255, 0, 0), true);
			auto seq = Sequence::create(action1, action2, NULL);
			auto repeat = RepeatForever::create(seq);
			nameLabel->runAction(repeat);
			auto action3 = FadeIn::create(0.5);
			auto action4 = FadeOut::create(0.5);
			scoreLabel->setFontFillColor(Color3B(255, 0, 0), true);
			auto seq1 = Sequence::create(action3, action4, NULL);
			auto repeat1 = RepeatForever::create(seq1);
			scoreLabel->runAction(repeat1);
		}
		else
		{
			nameLabel->setFontFillColor(Color3B(5, 5, 5), true);
			scoreLabel->setFontFillColor(Color3B(5, 5, 5), true);
		}
		nameLabel->setPosition(Point(unit->getContentSize().width * 3 / 9.0, unit->getContentSize().height / 2.0));
		unit->addChild(nameLabel);
		scoreLabel->setPosition(Point(unit->getContentSize().width * 9 / 10.0, unit->getContentSize().height / 2.0));
		unit->addChild(scoreLabel);
		rankList.pop_front();
	}

	auto ok = MenuItemImage::create("okbutton.png", "okbutton_on.png", CC_CALLBACK_1(RankingScene::onClickOK, this));
	ok->setPosition(back->getContentSize().width / 2, winSize.height / 12);

	auto menu = Menu::create(ok, NULL);
	menu->setPosition(Point::ZERO);
	back->addChild(menu);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(RankingScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void RankingScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		onClickOK(this);
		break;
	}
}

void RankingScene::onClickOK(Ref* object)
{
	if (_mode)
	{
		auto Scene = TransitionCrossFade::create(0.5f, GameOverScene::createScene()); // fade out

		Director::getInstance()->replaceScene(Scene);
	}
	else
	{
		auto Scene = TransitionCrossFade::create(0.5f, StartScene::createScene()); // fade out

		Director::getInstance()->replaceScene(Scene);
	}
}