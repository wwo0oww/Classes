#include"ObjController.h"
#include"SpriteController.h"
#include"MapController.h"
#include"Model\Obj\Weapon\Missile.h"
 MyLock* ObjController::id_obj_lc = new MyLock();//
 MyLock* ObjController::id_lc_lc = new MyLock();//
map<long, MyLock*> ObjController::id_lc;
map<long, Obj*> ObjController::id_obj;
float ObjController::position_x = 0;
float ObjController::position_y = 0;
void*ObjController::deleteObjList[MAX_SPRITE_NUM];
int ObjController::now_deleteobj_num = 0;
int ObjController::thread_size = 300;
int ObjController::PlayerID = 0;
Obj* ObjController::PlayerObj;
long ObjController::ID = 1;

ObjController* ObjController::m_Instance = new ObjController();

ObjController* ObjController::GetInstance() {
	return m_Instance;
}
void ObjController::addDeleteObj(Obj*obj) {
	//return;
	bool bFind = false;
	for (int i = 0; i < ObjController::now_deleteobj_num; i++) {
		if (ObjController::deleteObjList[i] == NULL) {
			ObjController::deleteObjList[i] = obj;
			bFind = true;
			break;
		}
	}
	if (!bFind) {
		ObjController::deleteObjList[ObjController::now_deleteobj_num++] = obj;
	}
}
void ObjController::clearDeathObj() {
	for (int i = 0; i < ObjController::now_deleteobj_num; i++) {
		Obj * obj = (Obj*)ObjController::deleteObjList[i];
		if (obj != NULL&&obj->bAlive == -1) {
			obj->before_die();
			obj->die();
			obj->bAlive = 0;
		}
	}
}
void* ObjController::getDeleteObj(int type) {
	for (int i = 0; i < ObjController::now_deleteobj_num; i++) {
		if (ObjController::deleteObjList[i] != NULL&&((Obj*)ObjController::deleteObjList[i])->bAlive == 0&&((Obj*)ObjController::deleteObjList[i])->type == type) {
			auto p = ObjController::deleteObjList[i];
			ObjController::deleteObjList[i] = NULL;

			return p;
		}
	}
	return NULL;
}
ObjController::ObjController() {
	this->InitID(0);
	this->InitData();
}
ObjController::~ObjController() {
	deleteData();
}
void ObjController::deleteData() {
	delete id_obj_lc;
	delete id_lc_lc;
}
//初始化ID
void ObjController::InitID(long ID) {
	ObjController::ID = ID;
}
void ObjController::InitData() {
	
	map<long, Obj*>::iterator it = id_obj.begin();
	while (it != id_obj.end()) {
		delete it->second;
	}

	map<long, MyLock*>::iterator it_ = id_lc.begin();
	while (it_ != id_lc.end()) {
		delete it_->second;
	}
}
////获取单例
//ObjController* ObjController::GetInstance() {
//	static ObjController* instance = new ObjController();
//	return instance;
//}
//获取ID
long ObjController::GetID() {
	return ++ObjController::ID;
}
void ObjController::reloadObj(Obj*obj) {
	Position* p = CoverInfo::coverData->getCoverList(obj->type, obj->status, obj->fx); //obj->SetCoverPosition();
	MapController::importMap(obj, obj->W*obj->H, p);
}
//增加对象
void ObjController::AddObj(Obj *obj) {
#ifdef DEBUG
	CCLOG("AddObj start");
#endif
	obj->SetID(ObjController::GetID());
	ObjController::id_obj.insert(pair<long, Obj*>(obj->GetID(),obj));
	//ObjController::id_lc.insert(pair<long,MyLock*>(obj->GetID(), new MyLock()));
#ifdef MODE_MAP
	if (obj->bCover) {
		Position* p = CoverInfo::coverData->getCoverList(obj->type, obj->status, obj->fx);//CoverInfo::coverData;// CoverInfo::coverData->getCoverList(obj->type,obj->status,obj->fx);// obj->SetCoverPosition();//CoverInfo::coverData
		MapController::importMap(obj, obj->W*obj->H, p);
	}
#endif
#ifdef DEBUG
	CCLOG("AddObj end");
#endif
}
void ObjController::test() {
	ObjController::create<Missile, Missile::Type>(Missile::Type::XMISSILE, 33, 33, true,Direction::RIGHT);
}
template<class T, class Type>
void*ObjController::create(Type type, int x, int y, bool bAI,Direction fx_) {
	T* obj = (T*)ObjController::getDeleteObj((int)type);
	if (obj != NULL) {
		
		obj->X = x;
		obj->Y = y;
		obj->bAI = bAI;
		obj->bNew = false;
		if (fx_ != -1)
			obj->setDirection(fx_);
		obj->init();
		
		
	}
	else {
		if (fx_ != -1)
			obj = new T(type, x, y, bAI,fx_);
		else
		obj = new T(type, x, y, bAI);
	}
	return obj;
}
//删除对象
void ObjController::DeleteObjByID(long ID) {
}
//获取对象by ID
Obj* ObjController::GetObjByID(long ID) {
#ifdef DEBUG
	CCLOG("GetObjByID start");
#endif
	Obj*result = NULL;
	ObjController::id_obj_lc->Lock();
	std::map<long, Obj*>::iterator it = ObjController::id_obj.find(ID);
	if (it != id_obj.end()) {
		result = it->second;
	}
	ObjController::id_obj_lc->UnLock();
#ifdef DEBUG
	CCLOG("GetObjByID end");
#endif
	return result;
}
//获取对象锁by ID 
MyLock* ObjController::GetObjLCByID(long ID) {
#ifdef DEBUG
	CCLOG("GetObjLCByID start");
#endif
	MyLock * result = NULL;
	ObjController::id_lc_lc->Lock();
	std::map<long, MyLock*>::iterator it = ObjController::id_lc.find(ID);
	if (it != id_lc.end()) {
		result = it->second;
	}
	ObjController::id_lc_lc->UnLock();
#ifdef DEBUG
	CCLOG("GetObjLCByID end");
#endif
	return result;
}

//调用对象方法
void* ObjController::Method(int ID, std::string methName, void * param) {
	MyLock * lock = ObjController::GetObjLCByID(ID);
	ClassData::ObjData* data;
	if (lock != NULL) {
		lock->Lock();
		Obj* obj = GetObjByID(ID);
		 data = (ClassData::ObjData*)obj->Method(methName, param);
		lock->UnLock();
	}
	return data;
}
//游戏结束
void ObjController::deleteObjs() {
	////废弃
	//std::map<string, map<string, CCSpriteFrame*>*>::iterator it = SpriteController::spriteFrameRoute.begin();
	//while (it != SpriteController::spriteFrameRoute.end()) {
	//	std::map<string, CCSpriteFrame*>::iterator it_ = it->second->begin();
	//	while(it_ != it->second->end()){
	//		CC_SAFE_DELETE(it_->second);
	//	}
	//	delete it->second;
	//	it->second->clear();
	//}
	SpriteController::spriteFrameRoute.clear();
	vector<SpriteController::SpritesNode*>::iterator it = SpriteController::spriteList.begin();
	while (it != SpriteController::spriteList.end()) {
		for (int i = 0; i < (*it)->len;i++)
		CC_SAFE_DELETE((*it)->list[i]);
		free(*it);
	}
	SpriteController::spriteList.clear();
}