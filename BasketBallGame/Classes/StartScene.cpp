#include "StartScene.h"
#include "GameScene.h"
#include "Obstacle.h"
#include "RankingScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// bg randering
	auto bg = Sprite::create("startbg.png");
	float scale = winSize.width / bg->getContentSize().width;
	bg->setScale(scale);
	bg->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(bg);

	// button rendering
	button[0] = MenuItemImage::create("startbutton.png", "startbutton_on.png", CC_CALLBACK_1(StartScene::onClickStart, this));
	button[0]->setTag(0);
	button[0]->setPosition(Point(winSize.width / 2, 400));
	button[0]->selected();
	//	button1->unselected();
	_select = 0;

	button[1] = MenuItemImage::create("rankingbutton.png", "rankingbutton_on.png", CC_CALLBACK_1(StartScene::onClickRanking, this));
	button[1]->setTag(1);
	button[1]->setPosition(Point(winSize.width / 2, 250));

	button[2] = MenuItemImage::create("exitbutton.png", "exitbutton_on.png", CC_CALLBACK_1(StartScene::onClickExit, this));
	button[2]->setTag(2);
	button[2]->setPosition(Point(winSize.width / 2, 100));

	auto menu = Menu::create(button[0], button[1], button[2], NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto sprite1 = Obstacle::spriteWithFile(1);
	sprite1->setPosition(winSize.width / 6, 150);
	this->addChild(sprite1);

	sprite1->addHandFoot();

	auto sprite2 = Obstacle::spriteWithFile(2);
	sprite2->setPosition(winSize.width * 5 / 6.0, 150);
	this->addChild(sprite2);

	sprite2->addHandFoot();

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void StartScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	log("onKeyPressed %d", key);

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_select != 0)
		{
			button[_select]->unselected();
			button[--_select]->selected();
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_select != 2) {
			button[_select]->unselected();
			button[++_select]->selected();
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		if (_select == 0)StartScene::onClickStart(this);
		else if (_select == 1)StartScene::onClickRanking(this);
		else StartScene::onClickExit(this);
		break;
	default:
		break;
	}
}

void StartScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event)
{
	log("onKeyReleased %d", key);

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_X:
		break;
	default:
		break;
	}
}

void StartScene::onClickStart(Ref* object)
{
	auto Scene = TransitionCrossFade::create(0.5f, GameScene::createScene(1,1,0,5)); // fade out

	Director::getInstance()->replaceScene(Scene);
}

void StartScene::onClickRanking(Ref* object)
{
	auto Scene = TransitionCrossFade::create(0.5f, RankingScene::createScene(false,"",0)); // fade out

	Director::getInstance()->replaceScene(Scene);
}

void StartScene::onClickExit(Ref* object)
{
	Director::getInstance()->popScene();
}