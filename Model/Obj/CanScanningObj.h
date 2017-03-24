#pragma once
#include"Model\Obj\Obj.h"
class CanScanningObj {
public:
	CanScanningObj(Obj*self);
	Obj*self;
	int scannig_range = 2;
	int attack_range = 40;
	Obj::AttackObj*attackObj = NULL;
	int* friendList ;
	int friend_len = 1;
	int enemy_num = 5;
	int scanning_time = 10;
	int scanning_now_time = 0;
	virtual void initAttackObj(Obj::AttackObj*);
	virtual void scanning_map();
	virtual void OutScanning();
	virtual void attackEnemy_simple();
	virtual void run();
	virtual int getMaxOffset(Obj*,int&);
	virtual bool canAttack();
	virtual void doAttack(int x,int y);
	static void delete_scanning_death_obj(Obj*obj,Obj*param);
};
