#pragma once
#include "cocos2d.h"
#include "ui/UIWidget.h"
USING_NS_CC;
using namespace ui;
class BeiginScene : public cocos2d::Layer
{
public:
public:
	virtual bool init() override;
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	void onSinglePlayer(Ref *pSender, TouchEventType type);
	void onMultiPlayer(Ref *pSender, TouchEventType type);
	void onSetting(Ref *pSender, TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(BeiginScene);

};