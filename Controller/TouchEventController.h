#pragma once
#include"cocos2d.h"
#include"Core\Controller.h"

class TouchEventController :public Controller {
public:
	
	struct AreaNode {
		float x;
		float y;
		float x_range;
		float y_range;
		void(*fun)();
		AreaNode*next;
	};

	static int clickPosition_x, clickPosition_y;
	static AreaNode* areahead;
	static bool MoveTouch(Touch* touch, Event* event);
	static void addListenArea(float x,float x_range,float y , float y_range, void(*fun)());
};