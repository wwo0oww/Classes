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
	//��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
};