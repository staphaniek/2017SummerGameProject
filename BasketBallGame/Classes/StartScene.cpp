#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
#include "SimpleAudioEngine.h"
#include "Ring.h"

Vec2 INITPOS;
bool r = false;
bool ring1upcheck, ring2upcheck, ring3upcheck, ring4upcheck;

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
	
	auto ring1 = Sprite::create("ring.png");
	ring1->setColor(Color3B(255, 0, 0));
	ring1->setTag(RING1TAG);
	float scale = RING1SIZE / ring1->getContentSize().width;
	ring1->setScale(scale);

	ring1->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height / 2 + origin.y));
	MyBodyParser::getInstance()->parseJsonFile("ring.json");

	auto ring1Body = MyBodyParser::getInstance()->bodyFormJson(ring1, "body", PhysicsMaterial(1.0, 0.1, 0.1));
	ring1Body->setCollisionBitmask(RING1TAG);
	ring1Body->setDynamic(false);
	ring1Body->setContactTestBitmask(true);
	ring1Body->setVelocity(ring1UpSpeed);
	ring1->setPhysicsBody(ring1Body);
	ring1->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring1Up = Sprite::create("ring.png");
	ring1Up->setVisible(false);
	ring1Up->setPosition(Vec2(ring1->getContentSize().width, 0));
	auto ring1UpBody = MyBodyParser::getInstance()->bodyFormJson(ring1Up, "up", PHYSICSBODY_MATERIAL_DEFAULT);
	ring1UpBody->setCollisionBitmask(RING1UPTAG);
	ring1UpBody->setDynamic(false);
	ring1UpBody->setContactTestBitmask(true);
	ring1Up->setPhysicsBody(ring1UpBody);
	ring1Up->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring1Down = Sprite::create("ring.png");
	ring1Down->setVisible(false);
	auto ring1DownBody = MyBodyParser::getInstance()->bodyFormJson(ring1Down, "down", PHYSICSBODY_MATERIAL_DEFAULT);
	ring1DownBody->setCollisionBitmask(RING1DOWNTAG);
	ring1DownBody->setDynamic(false);
	ring1DownBody->setContactTestBitmask(true);
	ring1Down->setPhysicsBody(ring1DownBody);
	ring1Down->setPosition(Vec2(ring1->getContentSize().width, 0));
	ring1Down->setAnchorPoint(Vec2(1.0, 0.0));

	ring1->addChild(ring1Up);

	ring1->addChild(ring1Down);

	this->addChild(ring1, 0);

	auto ring2 = Sprite::create("ring.png");
	ring2->setColor(Color3B(255, 127, 0));
	ring2->setTag(RING2TAG);
	scale = RING2SIZE / ring2->getContentSize().width;
	ring2->setScale(scale);

	ring2->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height / 2 + origin.y));
	
	auto ring2Body = MyBodyParser::getInstance()->bodyFormJson(ring2, "body", PhysicsMaterial(1.0, 0.1, 0.1));
	ring2Body->setCollisionBitmask(RING2TAG);
	ring2Body->setDynamic(false);
	ring2Body->setContactTestBitmask(true);
	ring2Body->setVelocity(ring2UpSpeed);
	ring2->setPhysicsBody(ring2Body);
	ring2->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring2Up = Sprite::create("ring.png");
	ring2Up->setVisible(false);
	ring2Up->setPosition(Vec2(ring2->getContentSize().width, 0));
	auto ring2UpBody = MyBodyParser::getInstance()->bodyFormJson(ring2Up, "up", PHYSICSBODY_MATERIAL_DEFAULT);
	ring2UpBody->setCollisionBitmask(RING2UPTAG);
	ring2UpBody->setDynamic(false);
	ring2UpBody->setContactTestBitmask(true);
	ring2Up->setPhysicsBody(ring2UpBody);
	ring2Up->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring2Down = Sprite::create("ring.png");
	ring2Down->setVisible(false);
	auto ring2DownBody = MyBodyParser::getInstance()->bodyFormJson(ring2Down, "down", PHYSICSBODY_MATERIAL_DEFAULT);
	ring2DownBody->setCollisionBitmask(RING2DOWNTAG);
	ring2DownBody->setDynamic(false);
	ring2DownBody->setContactTestBitmask(true);
	ring2Down->setPhysicsBody(ring2DownBody);
	ring2Down->setPosition(Vec2(ring2->getContentSize().width, 0));
	ring2Down->setAnchorPoint(Vec2(1.0, 0.0));

	ring2->addChild(ring2Up);

	ring2->addChild(ring2Down);

	this->addChild(ring2, 0);

	auto ring3 = Sprite::create("ring.png");
	ring3->setColor(Color3B(255,255,0));
	ring3->setTag(RING3TAG);
	scale = RING3SIZE / ring3->getContentSize().width;
	ring3->setScale(scale);

	ring3->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height / 2 + origin.y));
	
	auto ring3Body = MyBodyParser::getInstance()->bodyFormJson(ring3, "body", PhysicsMaterial(1.0, 0.1, 0.1));
	ring3Body->setCollisionBitmask(RING3TAG);
	ring3Body->setDynamic(false);
	ring3Body->setContactTestBitmask(true);
	ring3Body->setVelocity(ring3UpSpeed);
	ring3->setPhysicsBody(ring3Body);
	ring3->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring3Up = Sprite::create("ring.png");
	ring3Up->setVisible(false);
	ring3Up->setPosition(Vec2(ring3->getContentSize().width, 0));
	auto ring3UpBody = MyBodyParser::getInstance()->bodyFormJson(ring3Up, "up", PHYSICSBODY_MATERIAL_DEFAULT);
	ring3UpBody->setCollisionBitmask(RING3UPTAG);
	ring3UpBody->setDynamic(false);
	ring3UpBody->setContactTestBitmask(true);
	ring3Up->setPhysicsBody(ring3UpBody);
	ring3Up->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring3Down = Sprite::create("ring.png");
	ring3Down->setVisible(false);
	auto ring3DownBody = MyBodyParser::getInstance()->bodyFormJson(ring3Down, "down", PHYSICSBODY_MATERIAL_DEFAULT);
	ring3DownBody->setCollisionBitmask(RING3DOWNTAG);
	ring3DownBody->setDynamic(false);
	ring3DownBody->setContactTestBitmask(true);
	ring3Down->setPhysicsBody(ring3DownBody);
	ring3Down->setPosition(Vec2(ring3->getContentSize().width, 0));
	ring3Down->setAnchorPoint(Vec2(1.0, 0.0));

	ring3->addChild(ring3Up);

	ring3->addChild(ring3Down);

	this->addChild(ring3, 0);

	auto ring4 = Sprite::create("ring.png");
	ring4->setColor(Color3B(0,128,0));
	ring4->setTag(RING4TAG);
	scale = RING4SIZE / ring4->getContentSize().width;
	ring4->setScale(scale);

	ring4->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height / 2 + origin.y));
	
	auto ring4Body = MyBodyParser::getInstance()->bodyFormJson(ring4, "body", PhysicsMaterial(1.0, 0.1, 0.1));
	ring4Body->setCollisionBitmask(RING4TAG);
	ring4Body->setDynamic(false);
	ring4Body->setContactTestBitmask(true);
	ring4Body->setVelocity(ring4UpSpeed);
	ring4->setPhysicsBody(ring4Body);
	ring4->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring4Up = Sprite::create("ring.png");
	ring4Up->setVisible(false);
	ring4Up->setPosition(Vec2(ring4->getContentSize().width, 0));
	auto ring4UpBody = MyBodyParser::getInstance()->bodyFormJson(ring4Up, "up", PHYSICSBODY_MATERIAL_DEFAULT);
	ring4UpBody->setCollisionBitmask(RING4UPTAG);
	ring4UpBody->setDynamic(false);
	ring4UpBody->setContactTestBitmask(true);
	ring4Up->setPhysicsBody(ring4UpBody);
	ring4Up->setAnchorPoint(Vec2(1.0, 0.0));

	auto ring4Down = Sprite::create("ring.png");
	ring4Down->setVisible(false);
	auto ring4DownBody = MyBodyParser::getInstance()->bodyFormJson(ring4Down, "down", PHYSICSBODY_MATERIAL_DEFAULT);
	ring4DownBody->setCollisionBitmask(RING4DOWNTAG);
	ring4DownBody->setDynamic(false);
	ring4DownBody->setContactTestBitmask(true);
	ring4Down->setPhysicsBody(ring4DownBody);
	ring4Down->setPosition(Vec2(ring2->getContentSize().width, 0));
	ring4Down->setAnchorPoint(Vec2(1.0, 0.0));

	ring4->addChild(ring4Up);

	ring4->addChild(ring4Down);

	this->addChild(ring4, 0);

	initBall();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(StartScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

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

	this->scheduleUpdate();

	return true;
}

bool StartScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

//	log("collision %d %d\n", a->getCollisionBitmask(), b->getCollisionBitmask());

	// check if the bodies have collided
	if ((RING1TAG == a->getCollisionBitmask() && BGTAG - 1 == b->getCollisionBitmask()) || (BGTAG-1 == a->getCollisionBitmask() && RING1TAG == b->getCollisionBitmask()))
	{
//		log("collision occured");
		auto body = this->getChildByTag(RING1TAG)->getPhysicsBody();
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
	if ((BALLTAG == a->getCollisionBitmask() && BGTAG == b->getCollisionBitmask()) || (BGTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		auto action = FadeOut::create(2.0);
		auto callFunc = CallFunc::create([=]() {_ball->_actionComplete = true; });
		auto sequence = Sequence::create(action, callFunc, NULL);
		_ball->runAction(sequence);

	}
	if ((BALLTAG == a->getCollisionBitmask() && BGTAG - 1 == b->getCollisionBitmask()) || (BGTAG - 1 == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING1UPTAG == b->getCollisionBitmask()) || (RING1UPTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		ring1upcheck = true;
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING1DOWNTAG == b->getCollisionBitmask()) || (RING1DOWNTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		if (ring1upcheck)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/xylophone-c3.wav");
			ring1upcheck = false;
		}
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING2UPTAG == b->getCollisionBitmask()) || (RING2UPTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		ring2upcheck = true;
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING2DOWNTAG == b->getCollisionBitmask()) || (RING2DOWNTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		if (ring2upcheck)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/xylophone-d3.wav");
			ring2upcheck = false;
		}
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING3UPTAG == b->getCollisionBitmask()) || (RING3UPTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		ring3upcheck = true;
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING3DOWNTAG == b->getCollisionBitmask()) || (RING3DOWNTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		if (ring3upcheck)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/xylophone-e3.wav");
			ring3upcheck = false;
		}
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING4UPTAG == b->getCollisionBitmask()) || (RING4UPTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		ring4upcheck = true;
		return false;
	}
	if ((BALLTAG == a->getCollisionBitmask() && RING4DOWNTAG == b->getCollisionBitmask()) || (RING4DOWNTAG == a->getCollisionBitmask() && BALLTAG == b->getCollisionBitmask()))
	{
		if (ring4upcheck)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/xylophone-f3.wav");
			ring4upcheck = false;
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
		isJump = true;
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
		isJump = false;
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
	
	if (isLeft)
	{
		_ball->incAngle(1);
	}
	if (isRight)
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
		initBall();
		_ball->setPosition(INITPOS);
	}

	if (_ball->_actionComplete)
	{
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
	auto edgeBodySize = Size(visibleSize.width, visibleSize.height);
	auto edgeBody = PhysicsBody::createEdgeBox(edgeBodySize, PhysicsMaterial(1, 0.5, 0.8));
	edgeBody->setCollisionBitmask(BGTAG);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode, -4);

	auto upperBodySize = Size(210, 150);
	auto upperEdgeBody = PhysicsBody::createEdgeBox(upperBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	upperEdgeBody->setCollisionBitmask(BGTAG - 1);
	upperEdgeBody->setContactTestBitmask(true);

	auto upperEdgeNode = Node::create();
	upperEdgeNode->setColor(Color3B(0, 0, 1));
	upperEdgeNode->setPosition(Point(visibleSize.width - upperBodySize.width / 2, visibleSize.height - upperBodySize.height / 2));
	upperEdgeNode->setPhysicsBody(upperEdgeBody);

	this->addChild(upperEdgeNode, -4);

	auto lowerBodySize = Size(210, 50);
	auto lowerEdgeBody = PhysicsBody::createEdgeBox(lowerBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	lowerEdgeBody->setCollisionBitmask(BGTAG);
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
	_labelScore = LabelTTF::create("0", "arial", 20);
	_labelScore->setPosition(Point(score->getContentSize().width / 2, 22));
	_labelScore->setTag(0);
	// score Sprite에 추가
	score->addChild(_labelScore);
}

int getRandomNumber(int x)
{
	srand(time(NULL));
	return rand() % x + 1;
}

void StartScene::initBall()
{
	Size winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	INITPOS = Vec2(getRandomNumber(visibleSize.width / 2 + origin.x - BALLSIZE) + BALLSIZE, getRandomNumber(origin.y + visibleSize.height / 2 - BALLSIZE) + BALLSIZE);
	_ball = createBall(INITPOS);

	this->addChild(_ball, -1);

	_ball->initArrow();
}

Ball* StartScene::createBall(Vec2 &pos)
{
	Ball* ball = Ball::spriteWithFile("ball.png");

	ball->setTag(BALLTAG);

	ball->setPosition(pos);
	float scale = BALLSIZE / ball->getContentSize().width;
	ball->setScale(scale);
	ball->setAnchorPoint(Point(0.5f, 0.5f));

	attachBallbody(ball);
	return ball;
}

void StartScene::attachBallbody(Ball* ball)
{
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0.1));

	ballBody->setGravityEnable(false);
	ballBody->setCollisionBitmask(BALLTAG);
	ballBody->setContactTestBitmask(true);
	ball->setPhysicsBody(ballBody);
}