#pragma once
#pragma once
#include"Model\Obj\Biological\Biological.h"
#include"Model\Obj\Weapon\Weapon.h"
#include"Model\Obj\CanSendBulletObj.h"
class Soldier : public  Biological,public CanSendBulletObj {
private:

public:
	enum class Type {
		LANCER = 4,
	};
	Soldier();
	Soldier(Type type, int x, int y, bool bAI);
	Soldier(int type, int x, int y);
	virtual void sendBullet(Obj*);
	virtual void init();
	//角色死亡
	virtual void die();
	//virtual Position* SetCoverPosition();
	//virtual void changeFX(Direction fx);
	
	void picChange();
	virtual void setStatus(Status);
	virtual void setDirection(Direction fx);
	virtual void doSendBullet(Obj*obj);
	virtual void dearSonDeath(Obj*);
	virtual void afterAttack();
	//角色 活动
	virtual void run(int);//对象运行
						  //暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);
	virtual int GetZOrderY();
};