#include"EventController.h"
#include"View\MainScene.h"
#include"GameController.h"
#include"ObjController.h"
#include"View\HelloWorldScene.h"
#include"MainSceneController.h"
#include"Model\Obj\Obj.h"
#include"Core\UI\Message.h"
#include"ObjController.h"
#include"Model\Obj\Biological\Tank\Tank.h"
#ifdef ANDROID
#include"TouchEventController.h"
#endif
#include"TouchEventController.h"
#include"Model\Obj\CanSendBulletObj.h"
EventController* EventController::m_Instance = new EventController();
EventController::EventNode*EventController::playerEHead = NULL;
MyLock * EventController::PEventlock = new MyLock();
int EventController::now_status = -1;
int EventController::max_sprite_num = 4000;
int EventController::now_fx = -1;
EventController* EventController::GetInstance() {
	return m_Instance;
}
void EventController::EventListener(Ref *pSender, TouchEventType type , Key key) {
#ifdef DEBUG
	CCLOG("EventListener start");
#endif
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		dearTouchEventBegin(pSender, key);
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		dearTouchEventMove(pSender, key);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:
		dearTouchEventEnded(pSender, key);
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		dearTouchEventCanceled(pSender, key);
		break;

	default:
		break;
	}
#ifdef DEBUG
	CCLOG("EventListener end");
#endif
}
void EventController::dearTouchEventBegin(Ref *pSender, Key key) {
#ifdef DEBUG
	CCLOG("dearTouchEventBegin start");
#endif
	switch (key)
	{
	case EventController::Key::SINGLEPLAYER:

		break;
	case EventController::Key::MULTIPLAYER:
		break;
	case EventController::Key::SETTING:
		break;
	default:
		break;
	}
#ifdef DEBUG
	CCLOG("dearTouchEventBegin end");
#endif
}
void EventController::dearTouchEventMove(Ref *pSender, Key key) {
#ifdef DEBUG
	CCLOG("dearTouchEventMove start");
#endif
	switch (key)
	{
	case EventController::Key::SINGLEPLAYER:
		break;
	case EventController::Key::MULTIPLAYER:
		break;
	case EventController::Key::SETTING:
		break;
	default:
		break;
	}
#ifdef DEBUG
	CCLOG("dearTouchEventMove end");
#endif
}
void EventController::dearTouchEventEnded(Ref *pSender, Key key) {
#ifdef DEBUG
	CCLOG("dearTouchEventEnded start");
#endif
	int i = 0;
	switch (key)
	{
	case EventController::Key::SINGLEPLAYER:	
		GameController::changeScene(MainScene::scene());//HelloWorld;MainScene::scene());
		break;
	case EventController::Key::MULTIPLAYER:
		break;
	case EventController::Key::SETTING:
		break;
	default:
		break;
	}
#ifdef DEBUG
	CCLOG("dearTouchEventEnded end");
#endif
}

void* EventController::dearEventThread(void* args) {
#ifdef DEBUG
	CCLOG("DearCollision start");
#endif
	int tid = int(args);
	while (MainSceneController::bMainGameRunnig) {
#ifdef ANDROID
		usleep(10000);
#else
#ifdef WIN_32
		Sleep(10);
#endif
#endif
		if (MainSceneController::bThreadRuning[tid] == 0) {
			continue;
		}
		//do sth
		EventNode* p = playerEHead;
		PEventlock->Lock();
		while (p != NULL) {
			if (p->used) {
				if ((int)p->event_ < 4) {
					ObjController::PlayerObj->changeFX((Direction)p->event_);
					ObjController::PlayerObj->setStatus(Status::MOVE);
				}
				else if ((int)p->event_ == 4) {
					ObjController::PlayerObj->setStatus(Status::STAND);
				}
				else if (p->event_ == PlayerEvent::SENDBULLET) {
					((CanSendBulletObj*)ObjController::PlayerObj)->sendBullet(ObjController::PlayerObj);
				}
				p->used = false;
			}
			p = p->next;
		}
		PEventlock->UnLock();
		MainSceneController::bThreadRuning[tid] = 0;
}
	return NULL;
 }
void EventController::addPlayerEvent(EventController::PlayerEvent event_) {
	PEventlock->Lock();
	EventNode * p = playerEHead;
	if (playerEHead == NULL) {
		playerEHead = (EventNode*)malloc(sizeof(EventNode));
		playerEHead->used = true;
		playerEHead->next = NULL;
		playerEHead->event_ = event_;
		PEventlock->UnLock();
		return;
		
	}
	while (p != NULL) {
		if (!p->used) {
			break;
		}
		if (p->next == NULL) {
			p->next = (EventNode*)malloc(sizeof(EventNode));
			p->next->used = false;
			p->next->next = NULL;
			p = p->next;
			break;
		}
		p = p->next;
	}
	p->used = true;
	p->event_ = event_;
	PEventlock->UnLock();
}
void EventController::dearTouchEventCanceled(Ref *pSender, Key key) {
#ifdef DEBUG
	CCLOG("dearTouchEventCanceled start");
#endif
	switch (key)
	{
	case EventController::Key::SINGLEPLAYER:
		break;
	case EventController::Key::MULTIPLAYER:
		break;
	case EventController::Key::SETTING:
		break;
	default:
		break;
	}
#ifdef DEBUG
	CCLOG("dearTouchEventCanceled end");
#endif
}
void EventController::setObjActionEvent() {
#ifdef DEBUG
	CCLOG("setObjActionEvent start");
#endif
	auto dispatcher = Director::getInstance()->getEventDispatcher();
#ifdef WIN_32
	auto listenerKeyPad = EventListenerKeyboard::create();
	listenerKeyPad->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event) {
		//CCLOG("onKeyPressed");
		now_status = -1;
		now_fx = -1;
		switch (keycode) {
		case  EventKeyboard::KeyCode::KEY_J:
			addPlayerEvent(PlayerEvent::SENDBULLET);
			break;
		case  EventKeyboard::KeyCode::KEY_UP_ARROW:
		case  EventKeyboard::KeyCode::KEY_W:
			if (now_status == Status::MOVE&&now_fx == Direction::UP) {}
			else
			{
				now_status = Status::MOVE;
				now_fx = Direction::UP;
				addPlayerEvent(PlayerEvent::UP);
			}
			//if(ObjController::PlayerObj->)
			/*ObjController::Method(ObjController::PlayerID, "setDirection",new ClassData::ObjData(Direction::UP));
			ObjController::Method(ObjController::PlayerID, "setStatus", new ClassData::ObjData(Status::MOVE));
			*/break;
		case  EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case	EventKeyboard::KeyCode::KEY_S:
			if (now_status == Status::MOVE && now_fx == Direction::DOWN) {}
			else
			{
				now_status = Status::MOVE;
				now_fx = Direction::DOWN;
				addPlayerEvent(PlayerEvent::DOWN);
			}
			break;
		case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			if (now_status == Status::MOVE && now_fx == Direction::LEFT) {}
			else
			{
				now_status = Status::MOVE;
				now_fx = Direction::LEFT;
				addPlayerEvent(PlayerEvent::LEFT);
			}
			break;
		case  EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (now_status == Status::MOVE && now_fx == Direction::RIGHT) {}
			else
			{
				now_status = Status::MOVE;
				now_fx = Direction::RIGHT;
				addPlayerEvent(PlayerEvent::RIGHT);
			}
			break;
		/*case  EventKeyboard::KeyCode::KEY_1:
				addPlayerEvent(PlayerEvent::UPSCREEN);
			break;
		case  EventKeyboard::KeyCode::KEY_3:
			addPlayerEvent(PlayerEvent::DOWNSCREEN);
			break;*/
		}
	};
	listenerKeyPad->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event) {
		switch (keycode) {
		case  EventKeyboard::KeyCode::KEY_UP_ARROW:
		case  EventKeyboard::KeyCode::KEY_W:
		case  EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case	EventKeyboard::KeyCode::KEY_S:
		case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
		case  EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (ObjController::PlayerObj->status & Status::MOVE)
			{
				now_status = Status::MOVE;
				addPlayerEvent(PlayerEvent::STOP_M);
			}
			//ObjController::Method(ObjController::PlayerID, "setStatus", new ClassData::ObjData(Status::STAND));
			break;
		}

	};
	//将事件添加到事件调度中，设定优先级
	dispatcher->addEventListenerWithFixedPriority(listenerKeyPad, 2);
#else 
#ifdef ANDROID
#endif
#endif
	{
		auto androidlistener = EventListenerTouchOneByOne::create();
		// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没  
		androidlistener->setSwallowTouches(true);
		// onTouchBegan 事件回调函数  
		androidlistener->onTouchBegan = [](Touch* touch, Event* event)->bool {
			return TouchEventController::MoveTouch(touch, event);
			
			
			return true;
		};
		// onTouchMoved 事件回调函数  
		androidlistener->onTouchMoved = [](Touch* touch, Event* event) {
		};
		// onTouchEnded 事件回调函数  
		androidlistener->onTouchEnded = [](Touch* touch, Event* event) {
		};

		// 注册监听器  
		dispatcher->addEventListenerWithFixedPriority(androidlistener, 2);
	}
#ifdef DEBUG
	CCLOG("setObjActionEvent end");
#endif
}
void EventController::XButtonCLick() {
	//Direction s = Direction::DOWN;
	MainSceneController::xButtonType = (XButtonType)(((int)MainSceneController::xButtonType + 1)%MAX_XBUTTON);
	MainSceneController::xButtonName->setString(MainSceneController::xButtonStr[MainSceneController::xButtonType]);
	/*EventController::addPlayerEvent(PlayerEvent::SENDBULLET);*/
}
 