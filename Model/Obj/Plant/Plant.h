#pragma once
#include"Model\Obj\Obj.h"
class Plant : public  Obj {
private:

public:

	Plant();
	virtual void init();
	//角色死亡
	virtual void die();
	//virtual Position* SetCoverPosition();
	//角色 活动
	virtual void run(int);//对象运行
					   //暴露的调用对象方法的接口
	virtual int GetZOrderY();
	virtual void* Method(std::string, void* = NULL);
	virtual void setDirection(Direction);
};