#include"EventController.h"
#include"View\MainScene.h"
EventController* EventController::m_Instance = new EventController();
EventController* EventController::getInstance() {
	return m_Instance;
}
void EventController::EventListener(Ref *pSender, TouchEventType type , Key key) {
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
}
void EventController::dearTouchEventBegin(Ref *pSender, Key key) {
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
}
void EventController::dearTouchEventMove(Ref *pSender, Key key) {
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
}
void EventController::dearTouchEventEnded(Ref *pSender, Key key) {
	int i = 0;
	switch (key)
	{
	case EventController::Key::SINGLEPLAYER:
		Director::getInstance()->replaceScene(MainScene::scene());
		break;
	case EventController::Key::MULTIPLAYER:
		break;
	case EventController::Key::SETTING:
		break;
	default:
		break;
	}
}
void EventController::dearTouchEventCanceled(Ref *pSender, Key key) {
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
}
 