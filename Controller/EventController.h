#pragma once
#include"Core\Controller.h"
#include"cocos2d.h"
#include "ui/UIWidget.h"
USING_NS_CC;
using namespace ui;
class EventController : public Controller {
private:
	static EventController * m_Instance;
public:

public:
	enum class Key {
		SINGLEPLAYER,
		MULTIPLAYER,
		SETTING,
	};
	void EventListener(Ref *pSender, TouchEventType type,Key key);
	static EventController* getInstance();
private:
	void dearTouchEventBegin(Ref *pSender, Key key);
	void dearTouchEventMove(Ref *pSender, Key key);
	void dearTouchEventEnded(Ref *pSender, Key key);
	void  dearTouchEventCanceled(Ref *pSender, Key key);
};