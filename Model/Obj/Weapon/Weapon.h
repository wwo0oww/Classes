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
	//�����ƶ�
	virtual void objMove();
	//��ɫ����
	virtual void die();
	//virtual Position* SetCoverPosition();
	virtual void afterAttack();
	virtual void dearHarm();
	//��ɫ �
	virtual void run(int);//��������
						  //��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);

	virtual string getName();

	virtual bool stepMove(Direction fx, Vec2 next_position, int& now_move_num, bool& crossSearchMap);
	//virtual int GetZOrderY();
};