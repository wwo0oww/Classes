#pragma once
#include"Core\Controller.h"
#include"Model\Obj\Obj.h"
#include"Core\MyLock.h"
class ObjController : public Controller
{
private:
	MyLock* id_obj_lc;//
	MyLock* id_lc_lc;//
	std::map<long, Obj*> id_obj;
	std::map<long, MyLock*> id_lc;
	long ID;
public:
private:
	ObjController();
	void InitID();
public:
	long GetID();
	void AddObj(Obj *);
	void DeleteObjByID(long );
	Obj*GetObjByID(long );
	MyLock* GetObjLCByID(long);
	void* Method(int ID, std::string methName, void * param);
};
