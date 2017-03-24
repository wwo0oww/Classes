#pragma once

#include"Core\Controller.h"
#include"Model\Obj\Obj.h"



class ObjController : public Controller
{

	
public:
	struct SpriteNode {
		void * obj;//
		SpriteNode * next;//下一个
		bool used;//是否在使用
		//Sprite* sprite;
	}*PSpriteNode;
	static std::map<long, Obj*> id_obj;
	static float position_x;
	static float position_y;
	static int thread_size;
	static int PlayerID;
	static Obj* PlayerObj;
private:
	static MyLock* id_obj_lc;//
	static MyLock* id_lc_lc;//
	static void*deleteObjList[MAX_SPRITE_NUM];
	static int now_deleteobj_num;
	static std::map<long, MyLock*> id_lc;
	static long ID;
	static ObjController * m_Instance;
private:
	ObjController();
	~ObjController();
	static void InitID(long ID);
	static void InitData();
	static void deleteData();
public:
	static void addDeleteObj(Obj*);
	static void clearDeathObj();
	static void reloadObj(Obj*);
	static void* getDeleteObj(int type);
	static long GetID();
	static void AddObj(Obj *);
	static void DeleteObjByID(long );
	static ObjController * GetInstance();
	static Obj*GetObjByID(long );
	static MyLock* GetObjLCByID(long);
	static void deleteObjs();
	static void* Method(int ID, std::string methName, void * param);
	template<class T, class Type>
	static void*create(Type type, int x, int y, bool bAI , Direction fx_=(Direction)-1);
	static void test();
};
