#include"MapController.h"
#include"GameController.h"
#include"Model\Obj\Obj.h"
#include"ObjController.h"
#include"CollisionController.h"
MapController* MapController::m_Instance = new MapController();
MyLock *MapController:: mapLock = new MyLock();
 MyLock * MapController::lc_list;
 MapController::AreaNode * MapController::head;
 MapController::ObjMapNode*  MapController::objMapinfoList[MAX_TYPE];
MapController::~MapController() {
#ifdef DOUBLE_LIST
	delete this->lc_DataSyn;
	delete this->lc_writeList;
#endif
	delete this->lc_list;
}
MapController::SearchMapNode* MapController::objMap[MAP_NUM * POSITION_LIST_X / UNIT_OBJ_MAP][MAP_NUM*POSITION_LIST_Y / UNIT_OBJ_MAP];
bool MapController::canBuild(int x,int y,int x_range,int y_range) {
	for (int i = x - x_range; i < x + x_range; i++)
		for (int j = y - y_range; j < y + y_range; j++) {
			AreaNode * p = head;
			while (p != NULL) {

				if (p->x_start <= i && i < p->x_end && p->y_start <= j && j < p->y_end) {
					if (p->map[i % POSITION_LIST_X][j % POSITION_LIST_Y] != NULL&&p->map[i % POSITION_LIST_X][j % POSITION_LIST_Y]->ID !=0) {
						return false;
					}
				}
				p = p->next;
			}
		}
	return true;

}
void MapController::importMap(void* obj_,  int len, Position*list,bool bFree) {
#ifdef DEBUG
	CCLOG("importMap start");
#endif
	Obj*obj = (Obj*)obj_;
	ObjMap_add(obj);
	int index = obj->type;
	int id = obj->ID;
	int X = obj->X;
	int Y = obj->Y;
	AreaNode * p = head;
	for (int i = 0; i < len; i++) {
		int param = 0;
		changeMap(list[i].x + X,list[i].y + Y, &p,obj,MapController::Type::SET,param);
	}
	ObjMapNode*now_objmap = objMapinfoList[index];
	if (now_objmap != NULL) {
		bool bFind = false;
		while (now_objmap != NULL) {
			if (now_objmap->key == obj->now_key) {
				bFind = true;
			}
			now_objmap = now_objmap->next;
		}
		if(bFind)
		return; 
	}
	
	if (objMapinfoList[index] != NULL) {
		objMapinfoList[index]->next = (ObjMapNode*)malloc(sizeof(ObjMapNode));
		now_objmap = objMapinfoList[index]->next;
		now_objmap->next = NULL;
	}
	else {
		objMapinfoList[index] = (ObjMapNode*)malloc(sizeof(ObjMapNode));
		objMapinfoList[index]->next = NULL;
		now_objmap = objMapinfoList[index];
	}
	
	
	now_objmap->key = obj->now_key;
	now_objmap->coverMapSize = 0;
	now_objmap->downGetMapSize = 0;
	now_objmap->downLoseMapSize = 0;
	now_objmap->leftGetMapSize = 0;
	now_objmap->leftLoseMapSize = 0;
	now_objmap->rightGetMapSize = 0;
	now_objmap->rightLoseMapSize = 0;
	now_objmap->upGetMapSize = 0;
	now_objmap->upLoseMapSize = 0;
	//注：
	//  目前占地地图以 方块为准(TYPE_FULL)，即 占地范围内是填满的
	//   00000 
	//   0***0
	//   0***0
	//   0***0
	//   00000
	//，如果可以不填满(TYPE_NFULL)
	//   00000 
	//   0***0
	//   00*00
	//   0***0
	//   00000
	//情况要重新考虑

	int minX = list[0].x,minY = list[0].y,maxX = list[0].x,maxY = list[0].y;
	//<!--对数据进行排序 start-->
	//排序结果为 (-2,-2),(-2,-1),(-2,0),(-2,1),(-2,2)   (-1,-2),(-1,-1)..etc
	//<!--选择排序 start-->
	for (int i = 0; i < len; i++) {

		
		for (int j = i + 1; j < len; j++) {
			if (list[i].x > list[j].x) {
				int tmpx = list[i].x;
				int tmpy = list[i].y;
				list[i].x = list[j].x;
				list[i].y = list[j].y;
				list[j].x = tmpx;
				list[j].y = tmpy;
			}
		}
	}
	for (int i = 0; i < len; i++) {
		if (minX > list[i].x) {
			minX = list[i].x;
		}
		if (minY > list[i].y) {
			minY = list[i].y;
		}
		if (maxX < list[i].x) {
			maxX = list[i].x;
		}
		if (maxY < list[i].y) {
			maxY = list[i].y;
		}
	}
	//<!--选择排序 end-->
	int start = 0;//记录同一值的x开始位置
	//example 
	//0)=>>(-1,1) (-1,-1),(-1,0),(0,1),(0,-1),(0,0)
	//1)=>> x = -1 to 0 
	//2)=>>x=-1 j=0 对y进行选择排序 记录下到3位置
	//3)=>>(-1,-1) (-1,0),(-1,1),(0,1),(0,-1),(0,0)
	//4)=>>x=0  j=3   对y进行选择排序
	for (int i = list[0].x; i < list[len - 1].x; i++) {
		for (int j = start; j < len; j++) {
			if (list[j].x < i)continue;
			if (list[j].x > i) { 
				start = j;
				break; 
			}
			for (int z = j + 1; z < len; z++) {
				if (list[z].x > i)break;
				if (list[j].y > list[z].y) {
					int tmpx = list[z].x;
					int tmpy = list[z].y;
					list[z].x = list[j].x;
					list[z].y = list[j].y;
					list[j].x = tmpx;
					list[j].y = tmpy;
				}
			}
		}
	}
	//<!--对数据进行排序 end-->
	
	//<!--将占地数据存入map节点 start-->
	for (int i = 0; i < len; i++) {
		now_objmap->coverMap[i] = (Position*)malloc(sizeof(Position));
		now_objmap->coverMap[i]->x = list[i].x;
		now_objmap->coverMap[i]->y = list[i].y;
		now_objmap->coverMapSize++;
	}
	//<!--将占地数据存入map节点 end-->
	//
	for (int i = 0; i < len; i++) {
		//<!--右移 & 左移 start-->
		if (now_objmap->coverMap[i]->x == minX) {
			now_objmap->rightLoseMap[now_objmap->rightLoseMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->rightLoseMap[now_objmap->rightLoseMapSize]->x =
				now_objmap->coverMap[i]->x;
			now_objmap->rightLoseMap[now_objmap->rightLoseMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->rightLoseMapSize++;

			now_objmap->leftGetMap[now_objmap->leftGetMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->leftGetMap[now_objmap->leftGetMapSize]->x =
				now_objmap->coverMap[i]->x - 1;
			now_objmap->leftGetMap[now_objmap->leftGetMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->leftGetMapSize++;
		}
		
		if (now_objmap->coverMap[i]->x == maxX) {
			now_objmap->rightGetMap[now_objmap->rightGetMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->rightGetMap[now_objmap->rightGetMapSize]->x =
				now_objmap->coverMap[i]->x + 1;
			now_objmap->rightGetMap[now_objmap->rightGetMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->rightGetMapSize++;

			now_objmap->leftLoseMap[now_objmap->leftLoseMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->leftLoseMap[now_objmap->leftLoseMapSize]->x =
				now_objmap->coverMap[i]->x;
			now_objmap->leftLoseMap[now_objmap->leftLoseMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->leftLoseMapSize++;
		}
		//<!--右移 & 左移 end-->


		//<!--上移 & 下移 start-->
		if (now_objmap->coverMap[i]->y == minY) {
			now_objmap->upLoseMap[now_objmap->upLoseMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->upLoseMap[now_objmap->upLoseMapSize]->x =
				now_objmap->coverMap[i]->x;
			now_objmap->upLoseMap[now_objmap->upLoseMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->upLoseMapSize++;

			now_objmap->downGetMap[now_objmap->downGetMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->downGetMap[now_objmap->downGetMapSize]->x =
				now_objmap->coverMap[i]->x ;
			now_objmap->downGetMap[now_objmap->downGetMapSize]->y =
				now_objmap->coverMap[i]->y - 1;
			now_objmap->downGetMapSize++;
		}

		if (now_objmap->coverMap[i]->y == maxY) {
			now_objmap->upGetMap[now_objmap->upGetMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->upGetMap[now_objmap->upGetMapSize]->x =
				now_objmap->coverMap[i]->x;
			now_objmap->upGetMap[now_objmap->upGetMapSize]->y =
				now_objmap->coverMap[i]->y + 1;
			now_objmap->upGetMapSize++;

			now_objmap->downLoseMap[now_objmap->downLoseMapSize] =
				(Position*)malloc(sizeof(Position));
			now_objmap->downLoseMap[now_objmap->downLoseMapSize]->x =
				now_objmap->coverMap[i]->x;
			now_objmap->downLoseMap[now_objmap->downLoseMapSize]->y =
				now_objmap->coverMap[i]->y;
			now_objmap->downLoseMapSize++;
		}
		//<!--上移 & 下移 end-->

	}
	if (bFree) {
		free(list);
	}
#ifdef DEBUG
	CCLOG("importMap end");
#endif
}

MapController::MapController() {
#ifdef DOUBLE_LIST
	this->headInfo = NULL;
	this->headRead = NULL;
	this->headwrite = NULL;
	this->lc_DataSyn = new MyLock();
	this->lc_writeList = new MyLock();
#endif
	this->lc_list = new MyLock();
	this->head = NULL;
	initMapData();
	initSearchMap();
}

void MapController::initSearchMap() {
	objMap[MAP_NUM * POSITION_LIST_X / UNIT_OBJ_MAP][MAP_NUM*POSITION_LIST_Y / UNIT_OBJ_MAP];
	for (int i = 0; i < MAP_NUM * POSITION_LIST_X / UNIT_OBJ_MAP; i++)
		for (int j = 0; j < MAP_NUM*POSITION_LIST_Y / UNIT_OBJ_MAP; j++) {
			objMap[i][j] = (SearchMapNode*)malloc(sizeof(SearchMapNode));
			objMap[i][j]->head = NULL;
			objMap[i][j]->tail = NULL;
		}
}

void MapController::ObjMap_add(void*obj_) {
	Obj* obj = (Obj*)obj_;
	/*if (objMap[obj->X / UNIT_OBJ_MAP][obj->Y / UNIT_OBJ_MAP] == NULL) {
		objMap[obj->X / UNIT_OBJ_MAP][obj->Y / UNIT_OBJ_MAP] = (SearchMapNode*)malloc(sizeof(SearchMapNode));
		objMap[obj->X / UNIT_OBJ_MAP][obj->Y / UNIT_OBJ_MAP]->head = NULL;
		objMap[obj->X / UNIT_OBJ_MAP][obj->Y / UNIT_OBJ_MAP]->tail = NULL;
	}*/
	SearchMapNode*p = objMap[obj->X / UNIT_OBJ_MAP][obj->Y / UNIT_OBJ_MAP];
	if (p->head != NULL) {
		if (p->tail->ID == 0) {
			p->tail->ID = obj->ID;
			p->tail->obj = obj;
			obj->objMapNode = p->tail;
			obj->searchMapNode = p;
		}
		else {
			if (p->tail->next == NULL) {
				p->tail->next = (MapNode*)malloc(sizeof(MapNode));
				p->tail->next->next = NULL;
			}
			p->tail->next->last = p->tail;
			p->tail->next->ID = obj->ID;
			p->tail->next->obj = obj;
			obj->objMapNode = p->tail->next;
			obj->searchMapNode = p;
			p->tail = p->tail->next;
		}

	}
	else {
		p->head = (MapNode*)malloc(sizeof(MapNode));
		p->head->last = NULL;
		p->head->next = NULL;
		p->head->ID = obj->ID;
		p->head->obj = obj;
		obj->objMapNode = p->head;
		obj->searchMapNode = p;
		p->tail = p->head;
	}

	
	
}

void MapController::ObjMap_delete(void*obj_) {
	Obj* obj = (Obj*)obj_;
	/*if (obj->objMapNode == NULL)
		return;*/
	MapNode* mapNode = obj->objMapNode;
	SearchMapNode* searchMapNode = obj->searchMapNode;
	if (mapNode->last == NULL) {
		if (searchMapNode->head == searchMapNode->tail) {
			
		}
		else {
			MapNode* tmp =searchMapNode->head->next;
			if(searchMapNode->tail->next != NULL)
			searchMapNode->tail->next->last = searchMapNode->head;
			searchMapNode->head->next = searchMapNode->tail->next;

			searchMapNode->tail->next = searchMapNode->head;
			searchMapNode->head->last = searchMapNode->tail;
			searchMapNode->head = tmp;
			searchMapNode->head->last = NULL;
		}
	}
	else {
		if (mapNode != searchMapNode->tail) {
			mapNode->last->next = mapNode->next;
			if (mapNode->next != NULL)
				mapNode->next->last = mapNode->last;
			MapNode* tmp = searchMapNode->tail->next;
			searchMapNode->tail->next = mapNode;
			mapNode->last = searchMapNode->tail;
			mapNode->next = tmp;
			if (tmp != NULL)
				tmp->last = mapNode;
		}
		else {
			searchMapNode->tail = searchMapNode->tail->last;
		}
	}
	obj->objMapNode->ID = 0;
	/*if (objMap[obj->X / POSITION_LIST_X][obj->Y / POSITION_LIST_Y][obj->X % POSITION_LIST_X][obj->Y % POSITION_LIST_Y] != NULL) {
		SearchMapNode*p = objMap[obj->X / POSITION_LIST_X][obj->Y / POSITION_LIST_Y][obj->X % POSITION_LIST_X][obj->Y % POSITION_LIST_Y];
		PointNode*tmp = p->head;
		while (tmp != NULL) {
			if(tmp->ID == )
			tmp = tmp->next;
		}
	}*/

}
/*
map id排列 
15 14 13 12
 8  7  6 11
 3  2  5 10
 0  1  4  9
*/
void MapController::initMapData() {
#ifdef DEBUG
	CCLOG("initMapData start");
#endif
	AreaNode * p = NULL;
	//生成映射
	std::map<int, Vec2*>rangeList;
	int i = 0;//     ^    当前要进行步数
			  //     |
			  //  0 ->
	int tmpid = 0;//当前node id
	while (i < MAP_NUM) {
		int x = i, y = 0; 
		int now_index = i;//当前已经经过步数
		rangeList.insert(std::pair<int, Vec2*>(tmpid++, new Vec2(x, 0)));
		//上移
		while (now_index-- > 0) {
			rangeList.insert(std::pair<int, Vec2*>(tmpid++, new Vec2(x, ++y)));
		}
		//左移
		now_index = i;
		while (now_index-- > 0) {
			rangeList.insert(std::pair<int, Vec2*>(tmpid++, new Vec2(--x, y)));
		}
		i++;
	}
	//std::cout << "生成映射完毕!" << std::endl;
	//std::cout << "正在建立节点..." << std::endl;
	for (int i = 0; i < MAP_NUM *MAP_NUM; i++) {
		AreaNode*node = (AreaNode*)malloc(sizeof(AreaNode));
		node->ID = i;
		node->last = p;
		if (p != NULL)
			p->next = node;
		node->next = NULL;
		int x = rangeList.find(i)->second->x;
		int y = rangeList.find(i)->second->y;
		node->x_start = x * POSITION_LIST_X;
		node->x_end = (x + 1) * POSITION_LIST_X;
		node->y_start = y * POSITION_LIST_Y;
		node->y_end = (y + 1) * POSITION_LIST_Y;
		for (int ii = 0; ii < POSITION_LIST_X;ii++)
			for (int jj = 0; jj < POSITION_LIST_X; jj++) {
				node->map[ii][jj] = (PointNode*)malloc(sizeof(PointNode));
				node->map[ii][jj]->ID = 0;
				node->map[ii][jj]->next = NULL;
				node->map[ii][jj]->obj = NULL;
			}
		if (head == NULL) {
			head = node;
		}
		p = node;
	
	}
	//std::cout << "建立节点完毕..." << std::endl;
#ifdef DEBUG
	CCLOG("initMapData end");
#endif
}

MapController * MapController::Getinstance() {
	return m_Instance;
}
#ifdef DOUBLBE_LIST
//废弃 用来新线程同步 读 和 写 数据
void MapController::DataSyn() {
	if (this->headInfo = NULL) {
		return;
	}
	this->lc_DataSyn->Lock();
	SynInfo* p = this->headInfo;
	while (p) {
		SynInfo * tmp = p;
		p = p->next;
		delete tmp;
	}
	this->headInfo = NULL;
	this->lc_DataSyn->UnLock();
}
#endif

void MapController::getOffset(int fx,int&xoffset,int&yoffset) {

	switch (fx) {
	case Direction::DOWN:
		xoffset = 0;
		yoffset = -1;
		break;
	case Direction::UP:
		xoffset = 0;
		yoffset = 1;
		break;
	case Direction::LEFT:
		xoffset = -1;
		yoffset = 0;
		break;
	case Direction::RIGHT:
		xoffset = 1;
		yoffset = 0;
		break;
	default:
		return;
		break;
	}
}


//如果能 移动返回true 并且更新地图信息，否则返回false
void* MapController::probelMap(void*obj_, int fx_,bool bnotMove) {
	/*static bool map[5][5];
	static int px = 22, py = 22, pnx = 22, pny = 22;*/
	
#ifdef DEBUG
	CCLOG("probelMap start");
#endif
	Obj*obj = (Obj*)obj_;
	
	/*if (obj->ID == 2) {
		int ii = 2;
	}*/
	ObjMapNode*node = objMapinfoList[obj->type];
	while (node != NULL) {
		if (node->key == obj->now_key) {
			break;
		}
		node = node->next;
	}
	if (node == NULL)return NULL;
	int getLen = 0,loseLen = 0;
	Position** getmap = NULL;
	Position** losemap = NULL;
	int X = obj->X;
	int Y = obj->Y;
	int fx = fx_ == -1 ? obj->fx : fx_;//不等于-1 说明是主动探查某方向
	static int max_x = (GameController::mapX / 30)*30 - 2;//取值30是因为背景块texture大小为30*30，防止越出
	static int max_y = (GameController::mapY / 30)*30 - 2;
	//fx = (fx + PrefixInfo::prefixData->prefixList[obj->type]->rotation[obj->fx]/90)%4;
	switch (fx) {
	case Direction::RIGHT:
		if (obj->X >= max_x - 2 - obj->W / 2) {
			return (void*)-1;
		}
		getLen = node->rightGetMapSize;
		loseLen = node->rightLoseMapSize;
		getmap = node->rightGetMap;
		losemap = node->rightLoseMap;
		//pnx++;
		break;
	case Direction::LEFT:
		if (obj->X <= 1 + obj->W / 2) {
			return (void*)-1;
		}
		getLen = node->leftGetMapSize;
		loseLen = node->leftLoseMapSize;
		getmap = node->leftGetMap;
		losemap = node->leftLoseMap;
		//pnx--;
		break;
	case Direction::DOWN:
		if (obj->Y <= 1 + obj->H / 2) {
			return (void*)-1;
		}
		getLen = node->downGetMapSize;
		loseLen = node->downLoseMapSize;
		getmap = node->downGetMap;
		losemap = node->downLoseMap;
		//pny--;
		break;
	case Direction::UP:
		if (obj->Y >= max_y - 2 - obj->W / 2) {
			return (void*)-1;
		}
		getLen = node->upGetMapSize;
		loseLen = node->upLoseMapSize;
		getmap = node->upGetMap;
		losemap = node->upLoseMap;
		//pny++;
		break;
	}
	
	AreaNode * p = head;
	
	//can move?
	for (int i = 0; i < getLen; i++) {
		int param = 0;
		if (!changeMap(getmap[i]->x + X, getmap[i]->y + Y , &p, obj, Type::CONFIRM_NEXT, param)) {
			if (obj->type >= 20 && obj->type < 30 && obj->harmType == ((Obj*)param)->harmType)
				continue;
			return (Obj*)param;
		}
	}
	if (bnotMove)return 0;
	//delete the old position
	
	for (int i = 0; i < loseLen; i++) {
		int param = 1;
		
		changeMap(losemap[i]->x + X, losemap[i]->y + Y, &p, obj, Type::SET, param);
		
	}
	
	//set the new position
	for (int i = 0; i < getLen; i++) {
		int param = 0;
		int tmpX = getmap[i]->x + X;
		int tmpY = getmap[i]->y + Y;
		
		changeMap(tmpX, tmpY, &p, obj, Type::SET, param);
		
	}
	
#ifdef DEBUG
	CCLOG("probelMap end");
#endif
	
	
	return 0;
	
}
//返回false 表示这个节点不能用 true 能用 param:weather delete the old data
bool MapController::changeMap(int  x, int y, AreaNode ** p_, void*obj_, Type type, int& param) {
	
	//mapLock->Lock();
	
#ifdef DEBUG
	CCLOG("changeMap start");
#endif
	Obj*obj = (Obj*)obj_;
	
	//< !--{用于存储 实现 碰撞的数据结构和数据 start}-->
	
	struct TmpNode {
		Obj*obj;
		bool used;
		TmpNode*next;
	};
	
	static TmpNode*heads[MAX_THREADS];
	int tid = obj->tid<0|| obj->tid >= MAX_THREADS ?0: obj->tid;
	
	if (heads[tid] == NULL) {
		heads[tid] = (TmpNode*)malloc(sizeof(TmpNode));
		heads[tid]->next = NULL;
		heads[tid]->used = false;
	}
	
	TmpNode* tmphead = heads[tid];
	static bool bPromap[MAX_THREADS] ;//是否运行探索地图 先验证 
									 //获得 要碰撞的obj列表，在加入到碰撞列表中去
	//< !--{用于存储 实现 碰撞的数据结构和数据 end}-->
	
	bool result = false;
	
	AreaNode * p = *p_;
	bool bFind = (p == head);
	MapController::PointNode* tmp = NULL;
	
	while (p != NULL) {

		if (p->x_start <=x && x < p->x_end && p->y_start <= y && y < p->y_end) {
			switch (type)
			{
			case MapController::Type::SET:
				
				//重新设置
				if(!param){
					
					//没有一个节点 根节点不存在
					PointNode * pointNode = NULL;
					if (p->map[x % POSITION_LIST_X][y % POSITION_LIST_Y] == NULL) {
						MapController::PointNode* tmp_ = (MapController::PointNode*)malloc(sizeof(MapController::PointNode));
						
						tmp_->ID = obj->ID;
						tmp_->obj = obj;
						tmp_->next = NULL;
						p->map[x % POSITION_LIST_X][y % POSITION_LIST_Y] = tmp_;
						pointNode = tmp_;//存储 pointnode 用于碰撞 存入
					}
					//存在根节点 
					else {
						
						MapController::PointNode* tmp_ = p->map[x % POSITION_LIST_X][y % POSITION_LIST_Y];
						bool bnew = true;
						//找到尾节点 或 没有使用的节点

						while (tmp_ != NULL) {
							if (tmp_->ID == obj->ID) {

								//mapLock->UnLock();
								return 0; 
							}
							if (tmp_->ID == 0)
							{
								bnew = false;
								break;
							}
							//防止先加入节点 与链表丢失 联系
							if (tmp_->next == NULL) {
								break;
							}
							tmp_ = tmp_->next;
						}
						//是否存在没使用的节点
						if (bnew) {
							
							//新建节点存储 
							MapController::PointNode*tmp1 = (MapController::PointNode*)malloc(sizeof(MapController::PointNode));
							tmp1->ID = obj->ID;
							tmp1->obj = obj;
							tmp1->next = NULL;
							
							tmp_->next = tmp1;
							
							pointNode = tmp1;//存储pointnode节点 用于碰撞 存入
						}
						//存在没使用的节点
						else {
						
							tmp_->ID = obj->ID;
							tmp_->obj = obj;
							pointNode = tmp_;//存储pointnode节点 用于碰撞 存入
						}
					}
					//加入到碰撞列表
					if (bPromap[tid]&&pointNode != NULL) {
						tmphead = heads[tid];
						while (tmphead != NULL) {
							if (!tmphead->used)break;
							CollisionController::addNode(obj, tmphead->obj, pointNode);
							tmphead->used = false;
							tmphead = tmphead->next;
						}
					}
					bPromap[tid] = false;
				}
				//清空原来 数据  保留节点
				else {
					bool hasOther = false;
					tmp = p->map[x % POSITION_LIST_X][y % POSITION_LIST_Y];
					//遍历节点
					while (tmp != NULL) {
						//找到
						if (tmp->ID == obj->ID) {
							//清除碰撞
							if(hasOther)
							CollisionController::RemoveNode(tmp,obj);
							tmp->ID = 0;
							tmp->obj = NULL;
							param = 111;
							
						}
						if (tmp->ID != 0) {
							hasOther = true;
						}
						tmp = tmp->next;
					}
				}		 
				*p_ = p;

				//mapLock->UnLock();
				return true;
				break;
			case MapController::Type::CONFIRM_NEXT:
				
				 tmp = p->map[x % POSITION_LIST_X][y % POSITION_LIST_Y];
				 bPromap[tid] = true;
				 
				 //遍历这个节点的obj这个节点
				while (tmp != NULL) {
					//忽视未使用节点
					if (tmp->ID == 0) {
						tmp = tmp->next;
						continue;
					}
					//找到异类
					if (tmp->ID != obj->ID) {
						
						int high = ((Obj*)tmp->obj)->GetHigh();
						int bottomHigh = ((Obj*)tmp->obj)->GetBottomHigh();
						//ClassData::ObjData* data1 = (ClassData::ObjData*)ObjController::Method(tmp->ID,"GetHigh",NULL);
						//ClassData::ObjData* data = (ClassData::ObjData*)ObjController::Method(tmp->ID, "GetBottomHigh", NULL);
						if (obj->start_high + obj->high < bottomHigh
							|| obj->start_high >= bottomHigh + high) {
							while (tmphead != NULL) {
								if (!tmphead->used)break;
								tmphead = tmphead->next;
							}
							if (tmphead == NULL) {
								tmphead = (TmpNode*)malloc(sizeof(TmpNode));
								tmphead->next = NULL;
								tmphead->used = false;
							}
							tmphead->obj = ((Obj*)tmp->obj);
							tmphead->used = true;
						}
						else
						{
							param = (int)tmp->obj;
							//不是自己 且无法容纳自己
							/*delete data;
							delete data1;*/
#ifdef DEBUG
	CCLOG("changeMap end");
#endif
							//mapLock->UnLock();
							return false;
						}/*
						delete data;
						delete data1;*/
					}
					tmp = tmp->next;
				}
#ifdef DEBUG
	CCLOG("changeMap end");
#endif
				//mapLock->UnLock();
				return true;
				
				break;
			default:
				break;
			}
			
			bFind = true;//A找到
			p = p->next;
		}
		else {
			
			p = p->next;//没找到换到下一块区域
			if (bFind) {//A找到，B没找到
				p = head;//从头找过
				bFind = false;//B没找到
			}
		}
		
		
	}
	
#ifdef DEBUG
	CCLOG("changeMap end");
#endif
	//mapLock->UnLock();
	return result;
	
}

void MapController::deleteData() {
	MapController::AreaNode* node = MapController::head;
	while (node != NULL) {
		for (int i = 0; i < POSITION_LIST_X;i++)
			for (int j = 0; j < POSITION_LIST_X; j++) {
				if (node->map[i][j] != NULL) {
					auto p = node->map[i][j];
					while (p != NULL) {
						auto tmp = p;
						p = p->next;
						free(tmp);
					}
					node->map[i][j] = NULL;
				}
				
			}
		
		MapController::AreaNode*tmp = node;
		node = node->next;
		free(node);
	}
	
	for (int i = 0; i < MAX_TYPE; i++) {
		if (objMapinfoList[i] != NULL) {
			for (int j = 0; j < objMapinfoList[i]->coverMapSize;j++) {
				free(objMapinfoList[i]->coverMap[j]);
				objMapinfoList[i]->coverMap[j] = NULL;
			}
			objMapinfoList[i]->coverMapSize = 0;
			for (int j = 0; j < objMapinfoList[i]->downGetMapSize; j++) {
				free(objMapinfoList[i]->downGetMap[j]);
				objMapinfoList[i]->downGetMap[j] = NULL;
			}
			objMapinfoList[i]->downGetMapSize = 0;
			for (int j = 0; j < objMapinfoList[i]->downLoseMapSize; j++) {
				free(objMapinfoList[i]->downLoseMap[j]);
				objMapinfoList[i]->downLoseMap[j] = NULL;
			}
			objMapinfoList[i]->downLoseMapSize = 0;

			for (int j = 0; j < objMapinfoList[i]->upGetMapSize; j++) {
				free(objMapinfoList[i]->upGetMap[j]);
				objMapinfoList[i]->upGetMap[j] = NULL;
			}
			objMapinfoList[i]->upGetMapSize = 0;
			for (int j = 0; j < objMapinfoList[i]->upLoseMapSize; j++) {
				free(objMapinfoList[i]->upLoseMap[j]);
				objMapinfoList[i]->upLoseMap[j] = NULL;
			}
			objMapinfoList[i]->upLoseMapSize = 0;

			for (int j = 0; j < objMapinfoList[i]->rightGetMapSize; j++) {
				free(objMapinfoList[i]->rightGetMap[j]);
				objMapinfoList[i]->rightGetMap[j] = NULL;
			}
			objMapinfoList[i]->rightGetMapSize = 0;
			for (int j = 0; j < objMapinfoList[i]->rightLoseMapSize; j++) {
				free(objMapinfoList[i]->rightLoseMap[j]);
				objMapinfoList[i]->rightLoseMap[j] = NULL;
			}
			objMapinfoList[i]->rightLoseMapSize = 0;

			for (int j = 0; j < objMapinfoList[i]->leftGetMapSize; j++) {
				free(objMapinfoList[i]->leftGetMap[j]);
				objMapinfoList[i]->leftGetMap[j] = NULL;
			}
			objMapinfoList[i]->leftGetMapSize = 0;
			for (int j = 0; j < objMapinfoList[i]->leftLoseMapSize; j++) {
				free(objMapinfoList[i]->leftLoseMap[j]);
				objMapinfoList[i]->leftLoseMap[j] = NULL;
			}
			objMapinfoList[i]->leftLoseMapSize = 0;

			free(objMapinfoList[i]);
			objMapinfoList[i] = NULL;
		}
	}
}


void MapController::ClearMap(void *obj_) {

	Obj*obj = (Obj*)obj_;
	ObjMap_delete(obj);
	Position* list= CoverInfo::coverData->getCoverList(obj->type, obj->status, obj->fx);
	AreaNode* p= head;
	for (int i = 0; i < obj->W*obj->H; i++) {
		int param = 1;
		changeMap(list[i].x + obj->X, list[i].y + obj->Y, &p, obj, Type::SET, param);
	}
}