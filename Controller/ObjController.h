#pragma once
#include<stdio.h>
#include"Model\data.h"
#include"System\MyLock.h"
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
	MyLock* GetObjLCByID(long ID);

	//调用对象方法
	void* Method(int ID, std::string methName, void * param);
};