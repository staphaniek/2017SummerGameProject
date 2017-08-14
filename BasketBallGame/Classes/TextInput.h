#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "DevConf.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TextInput : public Layer, public extension::EditBoxDelegate
{
public:
	static cocos2d::Scene* createScene(int score);

	TextInput();
	~TextInput();

	int _select;
	bool isupper;
	bool iserase;
	int eraseCnt;

	MenuItemImage* button1;
	MenuItemImage* button2;

	virtual bool init();

	CREATE_FUNC(TextInput);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	cocos2d::extension::EditBox* m_pEditID;

	void eraseOneLetter();

	void onClickSubmit(Ref *object);
	void onClickCancel(Ref *object);
	void update(float delta);
};

