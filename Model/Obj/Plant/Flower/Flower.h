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
	//��ɫ����
	virtual void die();
	//virtual Position* SetCoverPosition();
	//��ɫ �
	virtual void run(int);//��������
					   //��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
	virtual int GetZOrderY();
};