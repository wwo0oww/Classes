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
	//��ɫ����
	virtual void die();
	//��ɫ �
	virtual void run(int);//��������
					   //��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
	virtual int GetZOrderY();
private:
	void init();
};