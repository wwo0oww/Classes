#pragma once
#include<stdio.h>
#include"Model\data.h"
#include"System\Lock.h"
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
	MyLock* GetObjCSByID(long ID);

	//���ö��󷽷�
	void* Method(int ID, std::string methName, void * param);
};
ObjController::ObjController() {
	this->InitID();
}
//��ʼ��ID
void ObjController::InitID() {
}
//��ȡ����
ObjController* ObjController::GetInstance(){
	static ObjController* instance = new ObjController();
	return instance;
}
//��ȡID
long ObjController::GetID() {
	return this->ID;
}
//���Ӷ���
void ObjController::AddObj(Obj *obj) {
}
//ɾ������
void ObjController::DeleteObjByID(long ID) {
}
//��ȡ����by ID
Obj* ObjController::GetObjByID(long ID) {
	Obj*result = NULL;
	this->id_obj_lc->Lock();
	std::map<long, Obj*>::iterator it = this->id_obj.find(ID);
	if (it != id_obj.end()) {
		result=  it->second;
	}
	this->id_obj_lc->UnLock();
	return result;
}
//��ȡ������by ID 
MyLock* ObjController::GetObjCSByID(long ID) {
	MyLock * result = NULL;
	this->id_lc_lc->Lock();
	std::map<long, MyLock*>::iterator it = this->id_lc.find(ID);
	if (it != id_lc.end()) {
		return it->second;
	}
	this->id_lc_lc->UnLock();
	return result;
}

//���ö��󷽷�
void* ObjController::Method(int ID, std::string methName, void * param) {
	MyLock * lock = this->GetObjCSByID(ID);
	if (lock != NULL) {
		lock->Lock();
		Obj* obj = GetObjByID(ID);
		obj->Method(methName,param);
		lock->UnLock();
	}
	return NULL;
}