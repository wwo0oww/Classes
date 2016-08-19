#pragma once
#include<stdio.h>
#include"Model\data.h"
#include"System\Lock.h"
class ObjController {
	//属性
private:
	long ID;
	MyLock* id_obj_lc;
	MyLock* id_lc_lc;
	std::map<long, Obj*>id_obj;
	std::map<long, MyLock*>id_lc;
public:
	
	//方法
private:
	ObjController();
	//初始化ID
	void InitID();
public:
	//获取单例
	static ObjController* GetInstance();
	//获取ID
	long GetID();
	//增加对象
	void AddObj(Obj *obj);
	//删除对象
	void DeleteObjByID(long ID);
	//获取对象by ID
	Obj* GetObjByID(long ID);
	//获取对象锁by ID 
	MyLock* GetObjCSByID(long ID);

	//调用对象方法
	void* Method(int ID, std::string methName, void * param);
};
ObjController::ObjController() {
	this->InitID();
}
//初始化ID
void ObjController::InitID() {
}
//获取单例
ObjController* ObjController::GetInstance(){
	static ObjController* instance = new ObjController();
	return instance;
}
//获取ID
long ObjController::GetID() {
	return this->ID;
}
//增加对象
void ObjController::AddObj(Obj *obj) {
}
//删除对象
void ObjController::DeleteObjByID(long ID) {
}
//获取对象by ID
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
//获取对象锁by ID 
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

//调用对象方法
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