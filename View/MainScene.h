#pragma once
#include "cocos2d.h"
#include "ui/UIWidget.h"
USING_NS_CC;
using namespace ui;
class MainScene : public cocos2d::Layer {
public:
public:
	virtual bool init() override;
	static cocos2d::Scene* scene();
	CCSprite* sprite;
	int count = 0;
	void test(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};