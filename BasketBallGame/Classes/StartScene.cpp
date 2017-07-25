#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
#include "SimpleAudioEngine.h"

Vec2 INITPOS;
bool r = false;

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
	
	/*
	PointLight *pointLight = PointLight::create(Vec3(0, 1000, 0), Color3B::WHITE,10000000);
	this->addChild(pointLight);
	*/
	
	auto ring1 = Sprite::create("ring1.png");
	ring1->setTag(1);
	float scale = 200 / ring1->getContentSize().width;
	ring1->setScale(scale);

	ring1->setPosition(Vec2(visibleSize.width + origin.x - 200, visibleSize.height / 2 + origin.y));
	MyBodyParser::getInstance()->parseJsonFile("ring1.json");
	auto ring1Body = MyBodyParser::getInstance()->bodyFormJson(ring1, "ring1", PhysicsMaterial(1.0, 0.1, 0.1));
	ring1Body->setCollisionBitmask(1);
	ring1Body->setDynamic(false);
	ring1Body->setContactTestBitmask(true);
	ring1Body->setVelocity(ring1UpSpeed);
	ring1->setPhysicsBody(ring1Body);

	this->addChild(ring1, 0);
	
	auto ring2 = Sprite::create("ring2.png");
	ring2->setTag(2);
	scale = 160 / ring2->getContentSize().width;
	ring2->setScale(scale);

	ring2->setPosition(Vec2(visibleSize.width + origin.x - 192, visibleSize.height / 2 + origin.y));
	MyBodyParser::getInstance()->parseJsonFile("ring1.json");
	auto ring2Body = MyBodyParser::getInstance()->bodyFormJson(ring2, "ring1", PhysicsMaterial(1.0, 0.1, 0.1));
	ring2Body->setCollisionBitmask(2);
	ring2Body->setDynamic(false);
	ring2Body->setContactTestBitmask(true);
	ring2Body->setVelocity(ring2UpSpeed);
	ring2->setPhysicsBody(ring2Body);

	this->addChild(ring2, 0);

	auto ring3 = Sprite::create("ring3.png");
	ring3->setTag(3);
	scale = 120 / ring3->getContentSize().width;
	ring3->setScale(scale);

	ring3->setPosition(Vec2(visibleSize.width + origin.x - 184, visibleSize.height / 2 + origin.y));
	log("%f %f", ring3->getContentSize().width, ring3->getContentSize().height);
	MyBodyParser::getInstance()->parseJsonFile("ring1.json");
	auto ring3Body = MyBodyParser::getInstance()->bodyFormJson(ring3, "ring1", PhysicsMaterial(1.0, 0.1, 0.1));
	ring3Body->setCollisionBitmask(3);
	ring3Body->setDynamic(false);
	ring3Body->setContactTestBitmask(true);
	ring3Body->setVelocity(ring3UpSpeed);
	ring3->setPhysicsBody(ring3Body);

	this->addChild(ring3, 0);
	
	auto ring4 = Sprite::create("ring4.png");
	ring4->setTag(4);
	scale = 100 / ring4->getContentSize().width;
	ring4->setScale(scale);

	ring4->setPosition(Vec2(visibleSize.width + origin.x - 180, visibleSize.height / 2 + origin.y));
	log("%f %f", ring4->getContentSize().width, ring4->getContentSize().height);
	MyBodyParser::getInstance()->parseJsonFile("ring1.json");
	auto ring4Body = MyBodyParser::getInstance()->bodyFormJson(ring4, "ring1", PhysicsMaterial(1.0, 0.1, 0.1));
	ring4Body->setCollisionBitmask(4);
	ring4Body->setDynamic(false);
	ring4Body->setContactTestBitmask(true);
	ring4Body->setVelocity(ring4UpSpeed);
	ring4->setPhysicsBody(ring4Body);

	this->addChild(ring4, 0);
	
//	auto ball = Ball::spriteWithFile("ball.png");
//	auto ball = Ball::create("ball.png");
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

	// check if the bodies have collided
	if ((1 == a->getCollisionBitmask() && 99 == b->getCollisionBitmask()) || (99 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
//		log("collision occured");
		auto body = this->getChildByTag(1)->getPhysicsBody();
		body->setVelocity(ring1DownSpeed);
	}
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 1 & ring 2");
		auto body1 = this->getChildByTag(1)->getPhysicsBody();
		body1->setVelocity(ring1UpSpeed);
		auto body2 = this->getChildByTag(2)->getPhysicsBody();
		body2->setVelocity(ring2DownSpeed);
	}
	if ((2 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 2 & ring 3");
		auto body2 = this->getChildByTag(2)->getPhysicsBody();
		body2->setVelocity(ring2UpSpeed);
		auto body3 = this->getChildByTag(3)->getPhysicsBody();
		body3->setVelocity(ring3DownSpeed);
	}
	if ((4 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 3 & ring 4");
		auto body3 = this->getChildByTag(3)->getPhysicsBody();
		body3->setVelocity(ring3UpSpeed);
		auto body4 = this->getChildByTag(4)->getPhysicsBody();
		body4->setVelocity(ring4DownSpeed);
	}
	if ((4 == a->getCollisionBitmask() && 100 == b->getCollisionBitmask()) || (100 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()))
	{
//		log("collision occured : ring 4 & edgebox");
		auto body4 = this->getChildByTag(4)->getPhysicsBody();
		body4->setVelocity(ring4UpSpeed);
	}
	if ((10 == a->getCollisionBitmask() && 100 == b->getCollisionBitmask()) || (100 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask()))
	{
		auto action = FadeOut::create(2.0);
		auto callFunc = CallFunc::create([=]() {_ball->_actionComplete = true; });
		auto sequence = Sequence::create(action, callFunc, NULL);
		_ball->runAction(sequence);

	}
	if ((10 == a->getCollisionBitmask() && 99 == b->getCollisionBitmask()) || (99 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask()))
	{
		return false;
	}
	return true;
}

void StartScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	auto ball = this->getChildByTag(0);
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
	auto ball = this->getChildByTag(0);
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
	auto ball = this->getChildByTag(0);
	
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
	edgeBody->setCollisionBitmask(100);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode, -4);

	auto upperBodySize = Size(210, 200);
	auto upperEdgeBody = PhysicsBody::createEdgeBox(upperBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	upperEdgeBody->setCollisionBitmask(99);
	upperEdgeBody->setContactTestBitmask(true);

	auto upperEdgeNode = Node::create();
	upperEdgeNode->setColor(Color3B(0, 0, 1));
	upperEdgeNode->setPosition(Point(visibleSize.width - upperBodySize.width / 2, visibleSize.height - upperBodySize.height / 2));
	upperEdgeNode->setPhysicsBody(upperEdgeBody);

	this->addChild(upperEdgeNode, -4);

	auto lowerBodySize = Size(210, 50);
	auto lowerEdgeBody = PhysicsBody::createEdgeBox(lowerBodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	lowerEdgeBody->setCollisionBitmask(100);
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

	INITPOS = Vec2(getRandomNumber(visibleSize.width / 2 + origin.x), getRandomNumber(origin.y + visibleSize.height / 2));
	_ball = createBall(INITPOS);

	this->addChild(_ball, -1);

	_ball->initArrow();
}

Ball* StartScene::createBall(Vec2 &pos)
{
	Ball* ball = Ball::spriteWithFile("ball.png");

	ball->setTag(0);

	ball->setPosition(pos);
	float scale = 30 / ball->getContentSize().width;
	ball->setScale(scale);
	ball->setAnchorPoint(Point(0.5f, 0.5f));

	attachBallbody(ball);
	return ball;
}

void StartScene::attachBallbody(Ball* ball)
{
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0.1));

	ballBody->setGravityEnable(false);
	ballBody->setCollisionBitmask(10);
	ballBody->setContactTestBitmask(true);
	ball->setPhysicsBody(ballBody);
}