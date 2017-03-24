#pragma once
#include"Obj.h"
class CanHarmObj {
private:
	Obj*self;
public:
	CanHarmObj(Obj*);
	void dearHarm(void*obj_, int x, int y);
	int harm_x_range;
	int harm_y_range;
	int harm;
};