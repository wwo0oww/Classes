#pragma once
#include"Model\Obj\Obj.h"
class Building : public  Obj {
private:
	
public:

	Building();
	virtual int GetZOrderY();
	virtual void init();
	//角色死亡
	virtual void die();
	virtual void dearCollision(Obj*);
	//角色 活动
	virtual void run(int);//对象运行
//暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);
};