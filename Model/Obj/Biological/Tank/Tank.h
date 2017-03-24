#pragma once
#include"Model\Obj\Biological\Biological.h"
#include"Model\Obj\CanSendBulletObj.h"
#include"Model\Obj\Weapon\Weapon.h"
#include"Model\Obj\CanScanningObj.h"
#include"Model\Obj\CanAttackObj.h"

class Tank : public Biological ,public CanSendBulletObj,public CanScanningObj,public CanAttackObj
{
private:
	
public:
	enum class Type {
		STRONG = 0,
	};
	static bool bInitSpriteFrame;
	static int num;
	int bullet_aim_x = -1;
	int bullet_aim_y = -1;
private:
	void init();
public:
	
	/*Weapon *bulletList[MAX_BULLET];*/
	//bool canSendBullet;
	//int now_bullet_num;
	virtual void setDirection(Direction fx);
	virtual void setStatus(Status);
	virtual void die();
	virtual void resetAttack();
	virtual Direction getDirection();
	Tank(Type, int, int, bool bAI = true);
	Tank(int, int, int, bool bAI = true);
	virtual void dearSonDeath(Obj*);
	virtual void run(int);
	virtual void dearShowObj();
	virtual int GetZOrderY();
	virtual void ShowObj();
	virtual void doSendBullet(Obj*obj);
//	virtual void sendBullet();
	virtual void afterAttack();
	virtual void dearCollision(Obj*);
	virtual void sendBullet(Obj*);
//	virtual void dearSendBullet();
	//暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);

	virtual bool canAttack();
	virtual void doAttack(int x, int y);

	virtual void initSpriteFrame(void*p);
	static void g_dearSonDeath(Obj*obj,Obj*param);
};