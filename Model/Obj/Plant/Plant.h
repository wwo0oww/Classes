#pragma once
#include"Model\Obj\Obj.h"
class Plant : public  Obj {
private:

public:

	Plant();
	virtual void init();
	//��ɫ����
	virtual void die();
	//virtual Position* SetCoverPosition();
	//��ɫ �
	virtual void run(int);//��������
					   //��¶�ĵ��ö��󷽷��Ľӿ�
	virtual int GetZOrderY();
	virtual void* Method(std::string, void* = NULL);
	virtual void setDirection(Direction);
};