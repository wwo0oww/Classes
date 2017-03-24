#pragma once
#include"Model\Obj\Building\Building.h"
class Brike : public  Building {

public:
	enum class Type {
		STEEL = 1,
	};
	Brike();
	Brike(Type, int, int,bool bAI = true);
	Brike(int, int, int, bool bAI = true);
	//角色死亡
	virtual void die();
	//角色 活动
	virtual void run(int);//对象运行
					   //暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);
	virtual int GetZOrderY();
private:
	void init();
};