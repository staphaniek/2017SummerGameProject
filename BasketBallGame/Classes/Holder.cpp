#include "Holder.h"

USING_NS_CC;

Holder::Holder()
{
	_ani = 0;
}

Holder::Holder(int lifeBonus)
{
	_lifeBonus = lifeBonus;
	_ani = 0;
}

Holder::~Holder()
{
}

Holder* Holder::spriteWithFile(const char* fileName, int lifeBonus)
{
	Holder* sprite = new Holder(lifeBonus);
	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease();
		sprite->setOpacity(200);
/*		auto fadeOut = FadeOut::create(1);
		auto callFunc = CallFunc::create([=]() {
			sprite->setColor(rainbow[sprite->_ani]);
			sprite->setOpacity(50);
			sprite->_ani = (sprite->_ani + 1) % 7;
		});
		auto fadeIn = FadeIn::create(1);
		auto seq = Sequence::create(fadeOut, callFunc, fadeIn, NULL);
		auto repeatforever = RepeatForever::create(seq);
		sprite->runAction(repeatforever);
*/		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}