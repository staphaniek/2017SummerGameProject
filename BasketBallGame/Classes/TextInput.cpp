#include "TextInput.h"
#include "DatabaseManager.h"
#include "GameOverScene.h"
#include "RankingScene.h"
#include <string>

cocos2d::Scene* TextInput::createScene()
{
	// scene : autorelease object
	auto scene = Scene::create();

	// layer : autorelease object
	auto layer = TextInput::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
TextInput::TextInput()
{
	_select = 0;
	isupper = false;
	iserase = false;
	eraseCnt = 0;
}


TextInput::~TextInput()
{
}

bool TextInput::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// UserDefault를 가져옵니다.
	auto UserDefault = UserDefault::getInstance();
	// UserDefault에서 isFirst의 값을 가져옵니다.
	bool isFirst = UserDefault->getBoolForKey("isFirst", true);
	if (true)
	{
		DatabaseManager::getInstance()->createDB();

		// isFirst의 값을 변경함
		UserDefault->setBoolForKey("isFirst", false);
		// UserDefault의 값을 변경하였으면 flush()를 호출해야 적용됨.
		UserDefault->flush();
	}

	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto back = Sprite::create("textinput_bg.png");
	back->setPosition(winSize.width / 2, winSize.height / 2);
	back->setTag(0);
	this->addChild(back);

	std::string text = "ID를 입력해주세요.";

	// 문자열을 담을 변수
	char utf8Text[255];

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// win32 utf-8
	wchar_t* wChar;

	wChar = new WCHAR[255];

	// wChar에 text를 담는다
	MultiByteToWideChar(CP_ACP, 0, text.c_str(), strlen(text.c_str()) + 1, wChar, 255);

	// wChar를 인코딩하여 utf8Text에 담는다.
	WideCharToMultiByte(CP_UTF8, 0, wChar, -1, utf8Text, 1024, NULL, NULL);
#endif

	// 안드로이드와 아이폰은 파일의 인코딩을 변경하면 한글이 적용됨
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	// win32가 아니라면 utf8Text에 들어온 text를 그냥 넣는다
	sprintf(utf8Text, "%s", text.c_str());
#endif

	CCTextFieldTTF *textfield = CCTextFieldTTF::textFieldWithPlaceHolder(utf8Text, CCSize(480, 30), kCCTextAlignmentCenter, "Arial", 20);
	textfield->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
	textfield->setTag(1);
	back->addChild(textfield);

	Size editBoxSize = CCSize(240, 30);
	/*
	m_pEditID = EditBox::create(editBoxSize, cocos2d::extension::Scale9Sprite::create("editboxbg.png"));;
	m_pEditID->setPosition(Point(back->getContentSize().width / 2, back->getContentSize().height / 2));
	m_pEditID->setPlaceHolder(utf8Text);
	m_pEditID->setMaxLength(20);
	m_pEditID->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditID->setDelegate(this);
	back->addChild(m_pEditID);
	*/
	button1 = MenuItemImage::create("IDSubmit.png", "IDSubmit_on.png", CC_CALLBACK_1(TextInput::onClickSubmit, this));
	button1->setTag(10);
	button1->setPosition(Point(back->getContentSize().width / 4, back->getContentSize().height / 4));
	button1->selected();

	button2 = MenuItemImage::create("IDCancel.png", "IDCancel_on.png", CC_CALLBACK_1(TextInput::onClickCancel, this));
	button2->setTag(11);
	button2->setPosition(Point(back->getContentSize().width * 3 / 4, back->getContentSize().height / 4));

	auto menu = Menu::create(button1, button2, NULL);
	menu->setPosition(Point::ZERO);
	back->addChild(menu);
	
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(TextInput::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(TextInput::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	
	this->scheduleUpdate();

	return true;
}

void TextInput::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("editBox %p DidBegin!", editBox);
}

void TextInput::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("editBox %p DidEnd!", editBox);
}

void TextInput::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s", editBox, text.c_str());
}

void TextInput::editBoxReturn(EditBox* editBox)
{
	log("editBox %p was returned", editBox);
}

void TextInput::update(float delta)
{
	if (iserase) {
		eraseCnt++;
	}
	else eraseCnt = 0;
	if (eraseCnt > 3) {
		eraseOneLetter();
		eraseCnt = 0;
	}
}

void TextInput::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	log("%d", key);
	std::string tmp;
	switch (key){
	case EventKeyboard::KeyCode::KEY_SHIFT:
		isupper = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		if (isupper)tmp = "A";
		else tmp = "a";
		break;
	case EventKeyboard::KeyCode::KEY_B:
		if (isupper)tmp = "B";
		else tmp = "b";
		break;
	case EventKeyboard::KeyCode::KEY_C:
		if (isupper)tmp = "C";
		else tmp = "c";
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if (isupper)tmp = "D";
		else tmp = "d";
		break;
	case EventKeyboard::KeyCode::KEY_E:
		if (isupper)tmp = "E";
		else tmp = "e";
		break;
	case EventKeyboard::KeyCode::KEY_F:
		if (isupper)tmp = "F";
		else tmp = "f";
		break;
	case EventKeyboard::KeyCode::KEY_G:
		if (isupper)tmp = "G";
		else tmp = "g";
		break;
	case EventKeyboard::KeyCode::KEY_H:
		if (isupper)tmp = "H";
		else tmp = "h";
		break;
	case EventKeyboard::KeyCode::KEY_I:
		if (isupper)tmp = "I";
		else tmp = "i";
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (isupper)tmp = "J";
		else tmp = "j";
		break;
	case EventKeyboard::KeyCode::KEY_K:
		if (isupper)tmp = "K";
		else tmp = "k";
		break;
	case EventKeyboard::KeyCode::KEY_L:
		if (isupper)tmp = "L";
		else tmp = "l";
		break;
	case EventKeyboard::KeyCode::KEY_M:
		if (isupper)tmp = "M";
		else tmp = "m";
		break;
	case EventKeyboard::KeyCode::KEY_N:
		if (isupper)tmp = "N";
		else tmp = "n";
		break;
	case EventKeyboard::KeyCode::KEY_O:
		if (isupper)tmp = "O";
		else tmp = "o";
		break;
	case EventKeyboard::KeyCode::KEY_P:
		if (isupper)tmp = "P";
		else tmp = "p";
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		if (isupper)tmp = "Q";
		else tmp = "q";
		break;
	case EventKeyboard::KeyCode::KEY_R:
		if (isupper)tmp = "R";
		else tmp = "r";
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (isupper)tmp = "S";
		else tmp = "s";
		break;
	case EventKeyboard::KeyCode::KEY_T:
		if (isupper)tmp = "T";
		else tmp = "t";
		break;
	case EventKeyboard::KeyCode::KEY_U:
		if (isupper)tmp = "U";
		else tmp = "u";
		break;
	case EventKeyboard::KeyCode::KEY_V:
		if (isupper)tmp = "V";
		else tmp = "v";
		break;
	case EventKeyboard::KeyCode::KEY_W:
		if (isupper)tmp = "W";
		else tmp = "w";
		break;
	case EventKeyboard::KeyCode::KEY_X:
		if (isupper)tmp = "X";
		else tmp = "x";
		break;
	case EventKeyboard::KeyCode::KEY_Y:
		if (isupper)tmp = "Y";
		else tmp = "y";
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		if (isupper)tmp = "Z";
		else tmp = "z";
		break;
	case EventKeyboard::KeyCode::KEY_0:
		if (isupper)tmp = ")";
		else tmp = "0";
		break;
	case EventKeyboard::KeyCode::KEY_1:
		if (isupper)tmp = "J";
		else tmp = "j";
		break;
	case EventKeyboard::KeyCode::KEY_2:
		if (isupper)tmp = "@";
		else tmp = "2";
		break;
	case EventKeyboard::KeyCode::KEY_3:
		if (isupper)tmp = "#";
		else tmp = "3";
		break;
	case EventKeyboard::KeyCode::KEY_4:
		if (isupper)tmp = "$";
		else tmp = "4";
		break;
	case EventKeyboard::KeyCode::KEY_5:
		if (isupper)tmp = "%";
		else tmp = "5";
		break;
	case EventKeyboard::KeyCode::KEY_6:
		if (isupper)tmp = "^";
		else tmp = "6";
		break;
	case EventKeyboard::KeyCode::KEY_7:
		if (isupper)tmp = "&";
		else tmp = "7";
		break;
	case EventKeyboard::KeyCode::KEY_8:
		if (isupper)tmp = "*";
		else tmp = "8";
		break;
	case EventKeyboard::KeyCode::KEY_9:
		if (isupper)tmp = "(";
		else tmp = "9";
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		//eraseOneLetter();
		iserase = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		tmp = " ";
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		if (!_select)onClickSubmit(this);
		else onClickCancel(this);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_select == 1) {
			button2->unselected();
			button1->selected();
			_select = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_select == 0) {
			button1->unselected();
			button2->selected();
			_select = 1;
		}
		break;
	default:
		break;
	}
	CCTextFieldTTF* textfield = (CCTextFieldTTF *)this->getChildByTag(0)->getChildByTag(1);
	std::string origin = textfield->getString();
	textfield->setString(origin + tmp);
}
void TextInput::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	if (key == EventKeyboard::KeyCode::KEY_SHIFT)isupper = false;
	else if (key == EventKeyboard::KeyCode::KEY_BACKSPACE)iserase = false;
}

void TextInput::eraseOneLetter()
{
	CCTextFieldTTF* textfield = (CCTextFieldTTF *)this->getChildByTag(0)->getChildByTag(1);
	std::string origin = textfield->getString();
	if(origin.length()>0)origin.pop_back();
	textfield->setString(origin);
}

void TextInput::onClickSubmit(Ref *object)
{
	CCTextFieldTTF* textfield = (CCTextFieldTTF *)this->getChildByTag(0)->getChildByTag(1);
	if (DatabaseManager::getInstance()->insertDB(textfield->getString(), _score))
	{
		log("submit");
		auto Scene = TransitionCrossFade::create(0.5f, RankingScene::createScene(1)); // fade out
		Director::getInstance()->replaceScene(Scene);
	}
}

void TextInput::onClickCancel(Ref *object)
{
	log("Cancel");
	auto Scene = TransitionCrossFade::create(0.5f, GameOverScene::createScene(_score)); // fade out
	Director::getInstance()->replaceScene(Scene);
}