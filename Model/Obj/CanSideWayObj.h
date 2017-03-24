#pragma once
#include"Obj.h"
class CanSideWayObj {
public:
	bool canSideWay = false;
	int aim_x, aim_y;
	int start_index = 0;
	int now_start_index = 0;
	/*
	Vec2 next_poisition;*/
	
	Direction sideWayFX_x = (Direction)-1;
	Direction sideWayFX_y = (Direction)-1;
	/*int now_moveNum = 0;
	bool CrossSearchMap = false;*/
	virtual bool isStatSideWay(bool);
	virtual void run();
	virtual bool doSideWay(Obj *);
	virtual void setSideWayAim(int x,int y);
	virtual bool stepMove(Obj * self, Direction fx, Vec2 next_position_, int& now_move_num, bool& crossSearchMap_);
	/*virtual void completeAIM(Obj *);
	virtual void before_die(Obj *);
	virtual void clearData();*/
	
};