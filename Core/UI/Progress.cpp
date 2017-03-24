#include "Progress.h"
#include"Controller\SpriteController.h"
 char Progress::cbg[50] = "player-progress-fill.png";
 char Progress::cfill[50] = "player-progress-bg.png";
 Progress::Progress() {
	 this->fill = NULL;
	 this->progress = NULL;
 }
bool Progress::init(const char* background, const char* fillname)
{
	this->progress->initWithSpriteFrameName(background);
	fill = ProgressTimer::create(Sprite::createWithSpriteFrameName(fillname));
	this->setFill(fill);
	this->progress->addChild(fill);

	fill->setType(ProgressTimer::Type::BAR);
	fill->setMidpoint(Point(0, 0.5));
	fill->setBarChangeRate(Point(1.0, 0));
	fill->setPosition(this->progress->getContentSize() / 2);
	fill->setPercentage(100);
	return true;
}
bool Progress::initbg(CCSprite*sprite) {
	
	this->progress = sprite;
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cbg);
	//auto frame = SpriteController::getSpriteFrame(0, cbg);
	this->progress->setDisplayFrame(frame);
	this->progress->setAnchorPoint(Vec2(0.5, 0.5));
	return true;
}

bool Progress::initfill(CCSprite*sprite) {
	
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cfill);
	sprite->setDisplayFrame(frame);// SpriteController::getSpriteFrame(0, cfill));
	fill = ProgressTimer::create(sprite);
	fill->setType(ProgressTimer::Type::BAR);
	fill->setMidpoint(Point(0, 0.5));
	fill->setBarChangeRate(Point(1.0, 0));
	fill->setPosition(this->progress->getContentSize() / 2);
	fill->setPercentage(100);
	this->progress->addChild(fill);
	return true;

}
Progress* Progress::create(const char* background, const char* fillname)
{
	Progress* progress = new Progress();
	if (progress && progress->init(background, fillname))
	{
		progress->progress->autorelease();
		return progress;
	}
	else
	{
		delete progress;
		progress = NULL;
		return NULL;
	}
}