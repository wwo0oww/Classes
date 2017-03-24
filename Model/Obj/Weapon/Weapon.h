#pragma once
#include"Model\Obj\Obj.h"
#include"Model\Obj\CanHarmObj.h"
class Weapon :public Obj,public CanHarmObj {
public:
	Obj*parent;
	int max_move_n;
	int now_move_n;
	
	Weapon();
	void* bullet_index;
	virtual void dearCollision(Obj*);
	//Missile(int type, int x, int y);
	virtual void init();

	//
	virtual void boom(Obj*);
	//virtual void before_die();
	virtual bool unableMove(Obj*);
	//virtual void completeAIM();
	virtual void afterMove();
	//处理移动
	virtual void objMove();
	//角色死亡
	virtual void die();
	//virtual Position* SetCoverPosition();
	virtual void afterAttack();
	virtual void dearHarm();
	//角色 活动
	virtual void run(int);//对象运行
						  //暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);

	virtual string getName();

	virtual bool stepMove(Direction fx, Vec2 next_position, int& now_move_num, bool& crossSearchMap);
	//virtual int GetZOrderY();
};