#pragma once
#include"Obj.h"
class CanHaveGold {
private:
	Obj*self;
public:
	CanHaveGold(Obj*);
	int gold;
};