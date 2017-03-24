#pragma once
#include"Obj.h"
class CanAttackObj {
private:
	Obj*self;
public:
	CanAttackObj(Obj*);
	
	Obj::AttackObj*attackObj = NULL;
	
	int send_bullet_time = 10;
	int send_bullet_now_time = 0;

	
	virtual void AttackObjDie(Obj*);
	virtual void run();
	virtual void resetAttackTime();
	virtual bool CanAttack();
};
