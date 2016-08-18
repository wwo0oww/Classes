#pragma once
#include"Singleton.h"
#include<stdio.h>
class ObjController :Singleton{
protected:
	ObjController() {
		((ObjController*)this->m_Instance)->InitID();
	}
private:
	void InitID() {
		printf("test");
	}
public:
	static long GetID()
	{

	}
};