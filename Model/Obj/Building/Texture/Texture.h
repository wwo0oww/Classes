#pragma once
#include"Model\Obj\Building\Building.h"
class Texture : public  Building {

public:
	enum class Type {
		GREEN = 30,
	};
	Texture();
	Texture(Type, int, int, bool bAI = true);
	Texture(int, int, int, bool bAI = true);
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