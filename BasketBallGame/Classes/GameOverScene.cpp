#include "GameOverScene.h"
#include "GameScene.h"
#include "StartScene.h"

USING_NS_CC;

GameOverScene::GameOverScene()
{
	_select = 0;
}


GameOverScene::~GameOverScene()
{
}

Scene* GameOverScene::createScene()
{
	// scene : autorelease object
	auto scene = Scene::create();

	// layer : autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameover = Sprite::create("gameover.png");
	float scale = 1024 / gameover->getContentSize().width;
	gameover->setScale(scale);
	gameover->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(gameover);

	button1 = MenuItemImage::create("RestartButton.png", "RestartButton_on.png", CC_CALLBACK_1(GameOverScene::onClickRestart, this));
	button1->setTag(0);
	button1->setPosition(Point(winSize.width / 2, 300));
	button1->selected();
//	button1->unselected();

	button2 = MenuItemImage::create("HomeButton.png", "HomeButton_on.png", CC_CALLBACK_1(GameOverScene::onClickHome, this));
	button2->setTag(1);
	button2->setPosition(Point(winSize.width / 2, 150));

	auto menu = Menu::create(button1, button2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameOverScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameOverScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}

void GameOverScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	log("onKeyPressed %d", key);

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_select == 1) {
			button2->unselected();
			button1->selected();
			_select = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_select == 0) {
			button1->unselected();
			button2->selected();
			_select = 1;
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		if (_select == 0)GameOverScene::onClickRestart(this);
		else if (_select == 1)GameOverScene::onClickHome(this);
		break;
	default:
		break;
	}
}

void GameOverScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event)
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

void GameOverScene::onClickRestart(Ref *object)
{
	auto Scene = TransitionCrossFade::create(0.5f, GameScene::createScene()); // fade out

	Director::getInstance()->replaceScene(Scene);
}

void GameOverScene::onClickHome(Ref *object)
{
	auto Scene = TransitionCrossFade::create(0.5f, StartScene::createScene()); // fade out

	Director::getInstance()->replaceScene(Scene);
}