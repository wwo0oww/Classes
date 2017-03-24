#pragma once
#include"Model\Obj\Plant\Plant.h"
class Flower : public  Plant {
private:

public:
	enum class Type {
		FRANGIPANI = 2,
		XFLOWER = 3,
	};
	Flower();
	Flower(Type type, int x, int y, bool bAI );
	Flower( int type,int x, int y );
	virtual void init();
	virtual void setDirection(Direction);
	//角色死亡
	virtual void die();
	//virtual Position* SetCoverPosition();
	//角色 活动
	virtual void run(int);//对象运行
					   //暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);
	virtual int GetZOrderY();
};