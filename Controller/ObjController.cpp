#include"ObjController.h"

ObjController::ObjController() {
	this->InitID();
}
//��ʼ��ID
void ObjController::InitID() {
}
//��ȡ����
ObjController* ObjController::GetInstance() {
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
		result = it->second;
	}
	this->id_obj_lc->UnLock();
	return result;
}
//��ȡ������by ID 
MyLock* ObjController::GetObjLCByID(long ID) {
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
	MyLock * lock = this->GetObjLCByID(ID);
	if (lock != NULL) {
		lock->Lock();
		Obj* obj = GetObjByID(ID);
		obj->Method(methName, param);
		lock->UnLock();
	}
	return NULL;
}