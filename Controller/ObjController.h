#pragma once
#include<stdio.h>
#include"Model\data.h"
#include"System\MyLock.h"
class ObjController {
	//����
private:
	long ID;
	MyLock* id_obj_lc;
	MyLock* id_lc_lc;
	std::map<long, Obj*>id_obj;
	std::map<long, MyLock*>id_lc;
public:
	
	//����
private:
	ObjController();
	//��ʼ��ID
	void InitID();
public:
	//��ȡ����
	static ObjController* GetInstance();
	//��ȡID
	long GetID();
	//���Ӷ���
	void AddObj(Obj *obj);
	//ɾ������
	void DeleteObjByID(long ID);
	//��ȡ����by ID
	Obj* GetObjByID(long ID);
	//��ȡ������by ID 
	MyLock* GetObjLCByID(long ID);

	//���ö��󷽷�
	void* Method(int ID, std::string methName, void * param);
};