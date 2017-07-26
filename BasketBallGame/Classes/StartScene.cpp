#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
#include "SimpleAudioEngine.h"

bool r = false;
bool ring1upcheck, ring2upcheck, ring3upcheck, ring4upcheck;

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, -98 * 3));

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	float sizeoffset = 0;
	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initSetting();

	// 배경화면 렌더링
	createBG();

	createScore();

	// create ring1
	ring[0] = createRing(2, 0, Color3B(255,0,0) , "c3");

	//create ring2
	ring[1] = createRing(3, 1, Color3B(255, 127, 0), "d3");

	// create ring3
	ring[2] = createRing(4, 2, Color3B(255, 255, 0), "e3");

	// create ring4
	ring[3] = createRing(5, 3, Color3B(0, 128, 0), "f3");

	createBall();

	// collision detection
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(StartScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// keyboard listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	/*
	auto throwButton = MenuItemImage::create("ThrowButton.png", "ThrowButton_on.png", CC_CALLBACK_1(StartScene::onClickThrow, this));
	scale = 100 / throwButton->getContentSize().width;
	throwButton->setScale(scale);
	auto tmp = throwButton->getBoundingBox().size;
	float x = visibleSize.width - tmp.width / 2;
	float y = tmp.height / 2;
	throwButton->setPosition(Point(x, y));

	auto menu = Menu::create(throwButton, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	*/
	this->scheduleUpdate();

	return true;
}

bool StartScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	log("collision %d %d", a->getCollisionBitmask(), b->getCollisionBitmask());

	// check if the bodies have collided
	if (a->getCollisionBitmask() == BGTAG - 1)
	{
		auto tag = b->getCollisionBitmask();
		if (tag == BALLTAG)return false;
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i] != NULL && ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}
	}
	if (b->getCollisionBitmask() == BGTAG - 1)
	{
		auto tag = a->getCollisionBitmask();
		if (tag == BALLTAG)return false;
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i] != NULL && ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}
	}
	if (a->getCollisionBitmask() == BGTAG - 2)
	{
		auto tag = b->getCollisionBitmask();
		if (tag == BALLTAG || tag == BGTAG)return false;
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i] != NULL && !ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}
	}
	if (b->getCollisionBitmask() == BGTAG - 2)
	{
		auto tag = a->getCollisionBitmask();
		if (tag == BALLTAG || tag == BGTAG)return false;
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i] != NULL && !ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}
	}
	if (a->getCollisionBitmask() >= RINGTAG[0] && a->getCollisionBitmask() <= RINGTAG[3] && b->getCollisionBitmask() >= RINGTAG[0] && b->getCollisionBitmask() <= RINGTAG[3])
	{
		// collision between ring
//		log("collision between ring");
		auto tag = std::min(a->getCollisionBitmask(),b->getCollisionBitmask());
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i]!=NULL && !ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}

		tag = std::max(a->getCollisionBitmask(),b->getCollisionBitmask());
		for (int i = 0; i < 4; ++i)
		{
			if (RINGTAG[i] == tag && ring[i] != NULL && ring[i]->_state)
			{
				ring[i]->changeDir();
			}
		}
	}
	/*
	if ((RINGTAG[0] == a->getCollisionBitmask() && BGTAG - 1 == b->getCollisionBitmask()) || (BGTAG-1 == a->getCollisionBitmask() && RINGTAG[0] == b->getCollisionBitmask()))
	{
//		log("collision occured");
		auto body = this->getChildByTag(RINGTAG[0])->getPhysicsBody();
		body->setVelocity(ring1DownSpeed);
	}
	if ((RING1TAG == a->getCollisionBitmask() && RING2TAG == b->getCollisionBitmask()) || (RING2TAG == a->getCollisionBitmask() && RING1TAG == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 1 & ring 2");
		auto body1 = this->getChildByTag(RING1TAG)->getPhysicsBody();
		body1->setVelocity(ring1UpSpeed);
		auto body2 = this->getChildByTag(RING2TAG)->getPhysicsBody();
		body2->setVelocity(ring2DownSpeed);
	}
	if ((RING2TAG == a->getCollisionBitmask() && RING3TAG == b->getCollisionBitmask()) || (RING3TAG == a->getCollisionBitmask() && RING2TAG == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 2 & ring 3");
		auto body2 = this->getChildByTag(RING2TAG)->getPhysicsBody();
		body2->setVelocity(ring2UpSpeed);
		auto body3 = this->getChildByTag(RING3TAG)->getPhysicsBody();
		body3->setVelocity(ring3DownSpeed);
	}
	if ((RING4TAG == a->getCollisionBitmask() && RING3TAG == b->getCollisionBitmask()) || (RING3TAG == a->getCollisionBitmask() && RING4TAG == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 3 & ring 4");
		auto body3 = this->getChildByTag(RING3TAG)->getPhysicsBody();
		body3->setVelocity(ring3UpSpeed);
		auto body4 = this->getChildByTag(RING4TAG)->getPhysicsBody();
		body4->setVelocity(ring4DownSpeed);
	}
	if ((RING4TAG == a->getCollisionBitmask() && BGTAG == b->getCollisionBitmask()) || (BGTAG == a->getCollisionBitmask() && RING4TAG == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 4 & edgebox");
		auto body4 = this->getChildByTag(RING4TAG)->getPhysicsBody();
		body4->setVelocity(ring4UpSpeed);
	}
	*/
	if ((BALLTAG == a->getCollisionBitmask() && BGTAG == b->getCollisionBitmask()) || (BGTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		auto preCallFunc = CallFunc::create([=]() {_score += _ball->_score; _ball->_score = 0; });
		auto action = FadeOut::create(2.0);
		auto callFunc = CallFunc::create([=]() {
			_ball->_actionComplete = true;
			for (int i = 0; i < 4; ++i)
			{
				ring[i]->_goal = false;
			}
		});
		auto sequence = Sequence::create(preCallFunc, action, callFunc, NULL);
		_ball->runAction(sequence);
	}
	if (a->getCollisionBitmask() == BALLTAG && b->getCollisionBitmask() >= RINGUPTAG[0] && b->getCollisionBitmask() <= RINGUPTAG[3])
	{
		auto tag = b->getCollisionBitmask();
		for (int i = 0; i < 4; ++i)
		{
			if (RINGUPTAG[i] == tag)
			{
				ring[i]->setGoalCheck();
			}
		}
		return false;
	}
	if (b->getCollisionBitmask() == BALLTAG && a->getCollisionBitmask() >= RINGUPTAG[0] && a->getCollisionBitmask() <= RINGUPTAG[3])
	{
		auto tag = a->getCollisionBitmask();
		for (int i = 0; i < 4; ++i)
		{
			if (RINGUPTAG[i] == tag)
			{
				ring[i]->setGoalCheck();
			}
		}
		return false;
	}
	if (a->getCollisionBitmask() == BALLTAG && b->getCollisionBitmask() >= RINGDOWNTAG[0] && b->getCollisionBitmask() <= RINGDOWNTAG[3])
	{
		auto tag = b->getCollisionBitmask();
		for (int i = 0; i < 4; ++i)
		{
			if (RINGDOWNTAG[i] == tag && ring[i]->getGoalCheck() && !ring[i]->_goal)
			{
				char tmp[25];
				sprintf(tmp, "sound/xylophone-%s.wav", ring[i]->_melody);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(tmp);
				if (_ball->_score == 0)_ball->_score = 1;
				_ball->_score *= ring[i]->_score;
				ring[i]->_goal = true;
				isScoreChanged = true;
				ring[i]->resetGoalCheck();
			}
		}
		return false;
	}
	if (b->getCollisionBitmask() == BALLTAG && a->getCollisionBitmask() >= RINGDOWNTAG[0] && a->getCollisionBitmask() <= RINGDOWNTAG[3])
	{
		auto tag = a->getCollisionBitmask();
		for (int i = 0; i < 4; ++i)
		{
			if (RINGDOWNTAG[i] == tag && ring[i]->getGoalCheck() && !ring[i]->_goal)
			{
				char tmp[25];
				sprintf(tmp, "sound/xylophone-%s.wav", ring[i]->_melody);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(tmp);
				if (_ball->_score == 0)_ball->_score = 1;
				_ball->_score *= ring[i]->_score;
				ring[i]->_goal = true;
				isScoreChanged = true;
				ring[i]->resetGoalCheck();
			}
		}
		return false;
	}
	return true;
}

void StartScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	auto ball = this->getChildByTag(BALLTAG);
	log("onKeyPressed %d", key);

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		isLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		isUp = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		isDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_X:
		if (!isThrow) {
			isThrow = true;
			onClickThrow(this);
		}
		break;
	default:
		break;
	}
}

void StartScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event)
{
	auto ball = this->getChildByTag(BALLTAG);
	log("onKeyReleased %d", key);

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		isLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		isUp = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		isDown = false;
		break;
	case EventKeyboard::KeyCode::KEY_X:
		break;
	default:
		break;
	}
}

void StartScene::update(float fDelta)
{
	float dist = 5;
	Vec2 v = Vec2();
	auto ball = this->getChildByTag(BALLTAG);
	
	if (isLeft && !r)
	{
		_ball->incAngle(1);
	}
	if (isRight && !r)
	{
		_ball->decAngle(1);
	}
	/*
	움직이는 경우
	if(isUp || isDown)
	{
		ball->getPhysicsBody()->applyImpulse(v);
		ball->getPhysicsBody()->setLinearDamping(0.9);
	}
	*/

	if (r)
	{
		r = false;
		createBall();
	}

	if (_ball->_actionComplete)
	{
		if (isScoreChanged)
		{
			updateScore();
			isScoreChanged = false;
		}
		log("here");
		this->removeChild(_ball, true);
		r = true;
	}

}

void StartScene::onClickThrow(Ref * object)
{
	log("Throw!!");
	auto ball = _ball;
	ball->removeArrow();

	ball->getPhysicsBody()->setGravityEnable(true);
	ball->getPhysicsBody()->setLinearDamping(0);

	float x = ball->_speed * cos(CC_DEGREES_TO_RADIANS(ball->_angle));
	float y = ball->_speed * sin(CC_DEGREES_TO_RADIANS(ball->_angle));
	ball->getPhysicsBody()->applyImpulse(Vec2(x, y));
	ball->getPhysicsBody()->applyTorque(70000);
}

void StartScene::createBG()
{
	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bg = Sprite::create("bg.png");
	float scale = 1024 / bg->getContentSize().width;
	bg->setScale(scale);

	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, -5);

	// edge Body : 테두리
	auto edgeBodySize = Size(visibleSize.width + 2, visibleSize.height);
	auto edgeBody = PhysicsBody::createEdgeBox(edgeBodySize, PhysicsMaterial(1, 0.5, 0.8));
	edgeBody->setCollisionBitmask(BGTAG);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode, -4);

	auto upperBodySize = Size(11, 100);
	auto upperEdgeBody = PhysicsBody::createEdgeBox(upperBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	upperEdgeBody->setCollisionBitmask(BGTAG - 1);
	upperEdgeBody->setContactTestBitmask(true);

	auto upperEdgeNode = Node::create();
	upperEdgeNode->setColor(Color3B(0, 0, 1));
	upperEdgeNode->setPosition(Point(visibleSize.width - upperBodySize.width / 2, visibleSize.height - upperBodySize.height / 2));
	upperEdgeNode->setPhysicsBody(upperEdgeBody);

	this->addChild(upperEdgeNode, -4);

	auto lowerBodySize = Size(11, 50);
	auto lowerEdgeBody = PhysicsBody::createEdgeBox(lowerBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	lowerEdgeBody->setCollisionBitmask(BGTAG - 2);
	lowerEdgeBody->setContactTestBitmask(true);

	auto lowerEdgeNode = Node::create();
	lowerEdgeNode->setColor(Color3B(0, 0, 1));
	lowerEdgeNode->setPosition(Point(visibleSize.width - lowerBodySize.width / 2,lowerBodySize.height / 2));
	lowerEdgeNode->setPhysicsBody(lowerEdgeBody);

	this->addChild(lowerEdgeNode, -4);
}

void StartScene::initSetting()
{
	_score = 0;
	_life = 5;
}

void StartScene::createScore()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 스코어 창
	auto score = Sprite::create("box_score.png");
	score->setPosition(Point(score->getContentSize().width / 2, visibleSize.height - score->getContentSize().height / 2));
	this->addChild(score);

	// 스코어 표시 Label
	char tmp[10];
	sprintf(tmp, "%d", _score);
	_labelScore = LabelTTF::create(tmp, "arial", 20);
	_labelScore->setPosition(Point(score->getContentSize().width / 2, 22));
	// score Sprite에 추가
	score->addChild(_labelScore);
}

int getRandomNumber(int x)
{
	srand(time(NULL));
	return rand() % x + 1;
}

void StartScene::createBall()
{
	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 INITPOS = Vec2(getRandomNumber(visibleSize.width / 2 + origin.x - BALLSIZE) + BALLSIZE, getRandomNumber(origin.y + visibleSize.height / 2 - BALLSIZE) + BALLSIZE);
	_ball = initBall(INITPOS);

	isThrow = false;

	this->addChild(_ball, -1);

	_ball->initArrow();
}

Ball* StartScene::initBall(Vec2 &pos)
{
	Ball* ball = Ball::spriteWithFile("ball.png");

	ball->setTag(BALLTAG);

	ball->setPosition(pos);
	float scale = BALLSIZE / ball->getContentSize().width;
	ball->setScale(scale);
	ball->setAnchorPoint(Point(0.5f, 0.5f));

	// attach ball body
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0.1));

	ballBody->setGravityEnable(false);
	ballBody->setCollisionBitmask(BALLTAG);
	ballBody->setContactTestBitmask(true);
	ball->setPhysicsBody(ballBody);

	return ball;
}

Ring* StartScene::createRing(int score, int index, Color3B color, const char* melody)
{
	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float offset = 10;

	auto object = Ring::spriteWithFile("ring.png", ringSpeed[index], melody);
	object->setColor(color);
	object->setTag(RINGTAG[index]);
	float scale = RINGSIZE[index] / object->getContentSize().width;
	object->setScale(scale);

	object->setPosition(Vec2(visibleSize.width - offset + origin.x, visibleSize.height / 2 + origin.y));
	MyBodyParser::getInstance()->parseJsonFile("ring.json");

	auto objectBody = MyBodyParser::getInstance()->bodyFormJson(object, "body", PhysicsMaterial(1.0, 0.1, 0.1));
	objectBody->setCollisionBitmask(RINGTAG[index]);
	objectBody->setDynamic(false);
	objectBody->setContactTestBitmask(true);
	objectBody->setVelocity(object->upSpeed);
	object->setPhysicsBody(objectBody);
	object->setAnchorPoint(Vec2(1.0, 0.0));
	
	object->_score = score;

	attachGoal(object, index, "up");
	attachGoal(object, index, "down");

	this->addChild(object, 0);

	return object;
}

void StartScene::attachGoal(Ring* ring, int index, const char* mode)
{
	auto object = Sprite::create("ring.png");
	object->setVisible(false);
	object->setPosition(Vec2(ring->getContentSize().width, 0));
	auto objectBody = MyBodyParser::getInstance()->bodyFormJson(object, mode, PHYSICSBODY_MATERIAL_DEFAULT);
	if(mode[0]=='u')objectBody->setCollisionBitmask(RINGUPTAG[index]);
	else objectBody->setCollisionBitmask(RINGDOWNTAG[index]);
	objectBody->setDynamic(false);
	objectBody->setContactTestBitmask(true);
	object->setPhysicsBody(objectBody);
	object->setAnchorPoint(Vec2(1.0, 0.0));

	ring->addChild(object);
}

void StartScene::updateScore()
{
	char scoreChar[20];
	sprintf(scoreChar, "%d", _score);
	_labelScore->setString(scoreChar);
}