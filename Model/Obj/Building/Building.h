#pragma once
#include"Model\Obj\Obj.h"
class Building : public  Obj {
private:
	
public:

	Building();
	virtual int GetZOrderY();
	virtual void init();
	//��ɫ����
	virtual void die();
	virtual void dearCollision(Obj*);
	//��ɫ �
	virtual void run(int);//��������
//��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
};