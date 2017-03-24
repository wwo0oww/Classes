#pragma once
#include"Core\Controller.h"
#include "ui/UIWidget.h"


using namespace ui;
class EventController : public Controller {
private:
	static EventController * m_Instance;
	static MyLock * PEventlock;
	static int now_status ;
	static int now_fx ;

public:
	static int max_sprite_num;
public:
	enum class Key {
		SINGLEPLAYER,//单人游戏
		MULTIPLAYER,//多人游戏
		SETTING,//设置
	};
	
	enum class PlayerEvent {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		STOP_M,
		SENDBULLET,
		UPSCREEN,
		DOWNSCREEN,
	};
	struct EventNode {
		bool used;
		PlayerEvent event_;
		EventNode*next;
	};
	static void EventListener(Ref *pSender, TouchEventType type,Key key);
	static EventController* GetInstance();
	static void setObjActionEvent();
	static EventNode*playerEHead;
	static void* dearEventThread(void* args);
	static void XButtonCLick();
	/*static void dearEvent();*/
private:
	static void dearTouchEventBegin(Ref *pSender, Key key);
	static void dearTouchEventMove(Ref *pSender, Key key);
	static void dearTouchEventEnded(Ref *pSender, Key key);
	static void dearTouchEventCanceled(Ref *pSender, Key key);
	
	static void addPlayerEvent(EventController::PlayerEvent event_);

	
	
};