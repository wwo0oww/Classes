#pragma once
#include"Weapon.h"
#include"Model\Obj\CanSideWayObj.h"
class Missile :public Weapon,public CanSideWayObj {
public:
	enum class Type {
		XMISSILE = 20,
		MINES = 21,
	};
	
	Missile(Type type, int x, int y, bool bAI,Direction fx = Direction::RIGHT);
	//Missile(int type, int x, int y);
	virtual void init();

	virtual void dearCollision(Obj*);
	//
	virtual void boom(Obj*);
/*
	virtual void completeAIM();

	virtual void before_die();*/

	virtual void setSideWayAim(int x, int y);
	virtual bool stepMove(Direction fx, Vec2 next_position, int& now_move_num, bool& crossSearchMap);
	//�����ƶ�
	virtual void objMove();
	//virtual Position* SetCoverPosition();
	virtual void dearHarm();
	//��ɫ �
	virtual void run(int);//��������
						  //��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
	//virtual int GetZOrderY();
};