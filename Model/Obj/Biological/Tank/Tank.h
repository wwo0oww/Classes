#pragma once
#include"Model\Obj\Biological\Biological.h"

class Tank : public Biological
{
private:
	
public:
	
private:

public:
	virtual void setDirection(Direction fx);
	virtual Direction getDirection();
	virtual void run();
	//暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);
};