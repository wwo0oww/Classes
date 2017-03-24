#pragma once
#include"Core\Controller.h"
#include"Core\MyLock.h"

class MapController : public Controller {
public:
	struct PointNode {
		int ID;
		void*obj;
		PointNode*next;
	};
	struct MapNode {
		int ID;
		void*obj;
		MapNode*next;
		MapNode*last;
		/*int x;
		int y;*/
	};
	struct SearchMapNode {
		MapNode*head;
		MapNode*tail;
	};
	
	static SearchMapNode* objMap[MAP_NUM * POSITION_LIST_X / UNIT_OBJ_MAP][MAP_NUM*POSITION_LIST_Y / UNIT_OBJ_MAP];
	struct AreaNode {
		//PointNode* map[POSITION_LIST_X][POSITION_LIST_Y];
		PointNode* map[POSITION_LIST_X][POSITION_LIST_Y];
		int ID;
		AreaNode*next;
		AreaNode*last;
		long x_start;
		long x_end;
		long y_start;
		long y_end;
	};

	struct SynInfo {
		int x;
		int y;
		void* obj;
		int start_high;
		int high;
	};
	
	enum class Type {
		//GET_NEXT,//获取将来
		SET,//设置当下
		CONFIRM_NEXT,//验证将来
	};
	
	//存储obj地图信息
	struct ObjMapNode {
		int key;//有些对象 方向改变了，他们的占地map也会改变，key即作为识别
		Position * coverMap[MAX_MAP_SIZE];//存储占地地图
		int coverMapSize;
		Position * leftGetMap[MAX_MAP_SIZE];//存储左移要获得地图
		int leftGetMapSize;
		Position * rightGetMap[MAX_MAP_SIZE];//存储右移要获得地图
		int rightGetMapSize;
		Position * upGetMap[MAX_MAP_SIZE];//存储上移要获得地图
		int upGetMapSize;
		Position * downGetMap[MAX_MAP_SIZE];//存储下移要获得地图
		int downGetMapSize;

		Position * leftLoseMap[MAX_MAP_SIZE];//存储左移要失去地图
		int leftLoseMapSize;
		Position * rightLoseMap[MAX_MAP_SIZE];//存储右移要失去地图
		int rightLoseMapSize;
		Position * upLoseMap[MAX_MAP_SIZE];//存储上移要失去地图
		int upLoseMapSize;
		Position * downLoseMap[MAX_MAP_SIZE];//存储下移要失去地图
		int downLoseMapSize;
		ObjMapNode* next;//下一个 key不同

	};
	static ObjMapNode* objMapinfoList[MAX_TYPE];
	//static
	static MyLock* mapLock;
#ifdef DOUBLE_LIST
#endif

private :
	static MapController* m_Instance;
	static AreaNode * head;
	static MyLock * lc_list;

#ifdef DOUBLE_LIST
	AreaNode * headRead;
	AreaNode * headwrite;
	SynInfo * headInfo;
	MyLock * lc_DataSyn;
	MyLock * lc_writeList;
#endif

public :
	
	MapController();
	static void ObjMap_add(void*obj);
	static void ObjMap_delete(void *boj);
	static MapController * Getinstance();
	static void initMapData();
	static void initSearchMap();
	~MapController();
	#ifdef DOUBLE_LIST
	static void DataSyn();
#endif
	static void deleteData();
	
	
	//如果能 移动返回true 并且更新地图信息，否则返回false
	static void* probelMap(void*,int fx = -1,bool bnMove = false);
	//返回false 表示这个节点不能用 true 能用 param:weather delete the old data
	static bool changeMap(int x,int y, AreaNode ** p, void *obj, Type type, int& param);

	static void dearHarm(void *Obj,int x,int y);
	//生成obj地图信息节点
	//index type类型
	//ID obj id
	//len list长度
	//list 占地数组
	//free 是否释放list内存
	static void importMap(void *, int len, Position *list,bool free=false);

	

	static void ClearMap(void *);

	static bool canBuild(int x, int y, int x_range, int y_range);
private :
	static void getOffset(int fx, int&xoffset, int&yoffset);
};