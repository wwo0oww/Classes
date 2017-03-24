#include"TouchEventController.h"
#include"ObjController.h"
#include"Core\UI\Message.h"
#include"GameController.h"
#include"MainSceneController.h"
#include"Model\Obj\CanSendBulletObj.h"
TouchEventController::AreaNode *TouchEventController::areahead = NULL;
int TouchEventController::clickPosition_x = 0;
int TouchEventController::clickPosition_y = 0;
bool TouchEventController::MoveTouch(Touch* touch, Event* event) {
	// 获取事件所绑定的 target   
	//auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 vec2 = GameController::getScreenUnitSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float screenx = (touch->getStartLocation().x - origin.x) / vec2.x;
	float screeny = (touch->getStartLocation().y - origin.y) / vec2.y;
	int x = screenx + GameController::zero_x;
	int y = screeny + GameController::zero_y;
	clickPosition_x = x;
	clickPosition_y = y;
#ifdef MY_TOUCH
	AreaNode*p =  areahead;
	while (p != NULL) {
		if (p->x <= screenx&&p->x + p->x_range > screenx&&p->y <= screenx&&p->y + p->y_range > screeny) {
			p->fun();
			return true;
		}
		p = p->next;
	}
#endif
	Direction fx = Direction::DOWN;
	char ch[200];
	switch (MainSceneController::xButtonType) {
	case XButtonType::ATTACK_B:
		ObjController::PlayerObj->sendBullet(ObjController::PlayerObj);
		break;
	case XButtonType::MOVE_B:
		
		ObjController::PlayerObj->setAim(x, y);
		break;
	}
	
	
	/*Message*message = Message::create(Message::Type::TEXT, MainSceneController::nowScene);
	char ch1[10];
	sprintf(ch1,"%d %d",x,y);
	message->setText(string(ch1));
	message->show(300);*/
	return true;
}
void TouchEventController::addListenArea(float x, float x_range, float y, float y_range, void(*fun)()) {
	AreaNode * p = areahead;
	if (p == NULL) {
		p = (AreaNode*)malloc(sizeof(AreaNode));
		p->x = x;
		p->y = y;
		p->x_range = x_range;
		p->y_range = y_range;
		p->fun = fun;
		p->next = NULL;
		areahead = p;
		return;
	}
	while (p != NULL) {
		if (p->fun == fun) return;
		if (p->next == NULL) {
			p->next = (AreaNode*)malloc(sizeof(AreaNode));
			p->next->x = x;
			p->next->y = y;
			p->next->x_range = x_range;
			p->next->y_range = y_range;
			p->next->fun = fun;
			p->next->next = NULL;
			return;
		}
		p = p->next;
	}
}