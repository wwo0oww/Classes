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
		//GET_NEXT,//��ȡ����
		SET,//���õ���
		CONFIRM_NEXT,//��֤����
	};
	
	//�洢obj��ͼ��Ϣ
	struct ObjMapNode {
		int key;//��Щ���� ����ı��ˣ����ǵ�ռ��mapҲ��ı䣬key����Ϊʶ��
		Position * coverMap[MAX_MAP_SIZE];//�洢ռ�ص�ͼ
		int coverMapSize;
		Position * leftGetMap[MAX_MAP_SIZE];//�洢����Ҫ��õ�ͼ
		int leftGetMapSize;
		Position * rightGetMap[MAX_MAP_SIZE];//�洢����Ҫ��õ�ͼ
		int rightGetMapSize;
		Position * upGetMap[MAX_MAP_SIZE];//�洢����Ҫ��õ�ͼ
		int upGetMapSize;
		Position * downGetMap[MAX_MAP_SIZE];//�洢����Ҫ��õ�ͼ
		int downGetMapSize;

		Position * leftLoseMap[MAX_MAP_SIZE];//�洢����Ҫʧȥ��ͼ
		int leftLoseMapSize;
		Position * rightLoseMap[MAX_MAP_SIZE];//�洢����Ҫʧȥ��ͼ
		int rightLoseMapSize;
		Position * upLoseMap[MAX_MAP_SIZE];//�洢����Ҫʧȥ��ͼ
		int upLoseMapSize;
		Position * downLoseMap[MAX_MAP_SIZE];//�洢����Ҫʧȥ��ͼ
		int downLoseMapSize;
		ObjMapNode* next;//��һ�� key��ͬ

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
	
	
	//����� �ƶ�����true ���Ҹ��µ�ͼ��Ϣ�����򷵻�false
	static void* probelMap(void*,int fx = -1,bool bnMove = false);
	//����false ��ʾ����ڵ㲻���� true ���� param:weather delete the old data
	static bool changeMap(int x,int y, AreaNode ** p, void *obj, Type type, int& param);

	static void dearHarm(void *Obj,int x,int y);
	//����obj��ͼ��Ϣ�ڵ�
	//index type����
	//ID obj id
	//len list����
	//list ռ������
	//free �Ƿ��ͷ�list�ڴ�
	static void importMap(void *, int len, Position *list,bool free=false);

	

	static void ClearMap(void *);

	static bool canBuild(int x, int y, int x_range, int y_range);
private :
	static void getOffset(int fx, int&xoffset, int&yoffset);
};