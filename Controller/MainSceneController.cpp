#include"MainSceneController.h"
#include"Controller\EventController.h"
#include"Controller\GameController.h"
#include"Model\Obj\Biological\Tank\Tank.h"
#include"Model\Obj\Building\Brike\Brike.h"
#include"Controller\ObjController.h"
#include"Controller\ErrorController.h"
#include"Controller\SpriteController.h"
#include"Model\Obj\Plant\Flower\Flower.h"
#include"MapBuildController.h"
#include"Core\UI\Message.h"
#include"Model\Obj\Weapon\Missile.h"
#include"Model\Obj\Biological\Soldier\Soldier.h"
#include"Controller\TouchEventController.h"
#include"Controller\CollisionController.h"


MainSceneController * MainSceneController::m_Instance = new  MainSceneController();
Scene* MainSceneController::nowScene;
bool MainSceneController::bMainGameRunnig = true;
bool MainSceneController::startGame = false;
threadP MainSceneController::threadParam[MAX_THREADS];
int MainSceneController::bThreadRuning[MAX_THREADS];
pthread_t MainSceneController::tids[MAX_THREADS];
int MainSceneController::now_threadTop = 0;
bool MainSceneController::bUseful[MAX_THREADS];
int MainSceneController::tankNum = 200;
int MainSceneController::now_thread_Num = -1;
CCSprite*MainSceneController::button;
Label*MainSceneController::xButtonName;
XButtonType MainSceneController::xButtonType = XButtonType::MOVE_B;
MainSceneController::TextureNode*MainSceneController::textureList[35];
 int MainSceneController::last_player_texture_x;
 int MainSceneController::last_player_texture_y;
 string MainSceneController::xButtonStr[2];
int MainSceneController::gold_num = 1000;
bool MainSceneController::mainGameFinish = true;
 MainSceneController* MainSceneController::GetInstance() {
	 return m_Instance;
}
 void* MainSceneController::DearCollision(void* args) {
#ifdef DEBUG
	 CCLOG("DearCollision start");
#endif
	 int tid = int(args);
	 while (MainSceneController::bMainGameRunnig) {
#ifdef ANDROID
		 usleep(10000);
#else
#ifdef WIN_32
		 Sleep(10);
#endif
#endif
		 if (MainSceneController::bThreadRuning[tid] == 0) {
			 continue;
		 }
		 CollisionController::dearCollision();
		 MainSceneController::bThreadRuning[tid] = false;
	 }
	 return NULL;
 }
 void* MainSceneController::RunGameThread(void* args) {
	 int tid = int(args);

	 while (MainSceneController::bMainGameRunnig) {
#ifdef ANDROID
		 usleep(10000);
#else
#ifdef WIN_32
		 Sleep(10);
#endif
#endif
		 if (!MainSceneController::bThreadRuning[tid]) {
			 continue;
		 }
		 MainSceneController::bThreadRuning[tid] = 2;
		 if (tid == 0 || tid == 1) {
			 int i = 0;
		 }
#define MOD_2
#ifdef MOD_2
		 int start = MainSceneController::threadParam[tid].start;
		 int end = MainSceneController::threadParam[tid].end;
		 Obj*obj = NULL;
		 for (int i = start+1; i < end+1; i++) {
			  obj = ObjController::id_obj[i];
			  if (obj == NULL)continue;
			 if (obj->ID != ObjController::PlayerID && obj->bAlive == 1) {
				 obj->run(tid);
			 }
			 else if (obj->bAlive == -1) {
				 clearDeath(obj);
			 }
		 }
		 MainSceneController::bThreadRuning[tid] = 0;
#endif
#ifdef MOD_1
		 map<long, Obj*>::iterator it = ObjController::id_obj.begin();
		 int count = MainSceneController::threadParam[tid].start;
		 while (it != ObjController::id_obj.end()) {
			 if (count-- <= 0)break;
			 it++;
		 }

		// std::advance(it, MainSceneController::threadParam[tid].start);
		 int nowIndex = MainSceneController::threadParam[tid].start;

		 while (nowIndex++ < MainSceneController::threadParam[tid].end&&it != ObjController::id_obj.end()) {
			 // ObjController::Method(it++->first, "run", NULL);
			 if (it->first != ObjController::PlayerID && ((Obj*)it->second)->bAlive == 1) {
				 it->second->run(tid);
			 }
			 else if (((Obj*)it->second)->bAlive == -1) {
				 clearDeath(it->second);
			 }
			 it++;

			 //(*it)->Method("run", NULL);
		 }
		 MainSceneController::bThreadRuning[tid] = 0;
#endif

	 }
#ifdef DEBUG
	 CCLOG("DearCollision end");
#endif
	 return NULL;
 }

 void MainSceneController::dearMutiThread() {
#ifdef DEBUG
	 CCLOG("dearMutiThread start");
#endif
	 if (now_thread_Num == -1) {
		 now_thread_Num = ObjController::id_obj.size() / ObjController::thread_size;
		 now_thread_Num = ObjController::id_obj.size() % ObjController::thread_size == 0 ?
			 now_thread_Num : (now_thread_Num + 1);
		 if (now_thread_Num > MAX_THREADS) {
			 ErrorController::dearError(ErrorController::CODE::THREAD_OVER);
		 }
	 }
	 ObjController::PlayerObj->run(0);
	 for (int i = 0; i < now_thread_Num; i++) {
		 
		 MainSceneController::threadParam[i].start = i * ObjController::thread_size;

		 MainSceneController::threadParam[i].end = (i + 1) * ObjController::thread_size;
		 MainSceneController::threadParam[i].end = ObjController::id_obj.size() < MainSceneController::threadParam[i].end ?
			 ObjController::id_obj.size() : MainSceneController::threadParam[i].end;
		 MainSceneController::bThreadRuning[i] = 1;
		 int ret = myCreateThread(i, &tids[i], NULL, MainSceneController::RunGameThread, (void*)i);
		
	 }

	 //<!--{其他非处理obj的线程 start}-->
	 // tip 0 处理 碰撞事件 1 event
	 MainSceneController::bThreadRuning[now_thread_Num] = 1;
	 int ret = myCreateThread(now_thread_Num, &tids[now_thread_Num], NULL, MainSceneController::DearCollision, (void*)now_thread_Num);

	 //MainSceneController::bThreadRuning[num + 1] = 1;
	 //ret = myCreateThread(num + 1, &tids[num + 1], NULL, EventController::dearEventThread, (void*)(num + 1));

	 //<!--{其他非处理obj的线程 end}-->

	 for (int i = 0; i < MainSceneController::now_threadTop; i++) {
		 int count = 5;
		 while (MainSceneController::bThreadRuning[i]) {
			 if (count-- <= 0) {
#ifdef DEBUG
				 CCLOG("%d 线程异常退出",i);
#endif
				 bUseful[i] = false;
				 
				 break;
			}
#ifdef ANDROID
			 usleep(10000);
#else
#ifdef WIN_32
			 Sleep(10);
#endif
#endif
		 }
	 }
	// CCLOG("all end");
#ifdef DEBUG
	 CCLOG("dearMutiThread end");
#endif
 }
 
 void  MainSceneController::dearEvent() {
	 EventController::EventNode* p = EventController::playerEHead;

	 while (p != NULL){//!ObjController::PlayerObj->Movelock&&p != NULL) {
		 if (p->used) {
			 if ((int)p->event_ < 4) {
				 ObjController::PlayerObj->changeFX((Direction)p->event_);
				 ObjController::PlayerObj->setStatus(Status(Status::STAND|Status::MOVE));
			 }
			 else if ((int)p->event_ == 4) {
				 ObjController::PlayerObj->setStatus(Status::STAND);
			 }
			 else if (p->event_ == EventController::PlayerEvent::SENDBULLET) {
				 ((Tank*)ObjController::PlayerObj)->sendBullet(ObjController::PlayerObj);
			 }
			/* else if (p->event_ == EventController::PlayerEvent::UPSCREEN) {
				 GameController::upScreen();
			 }
			 else if (p->event_ == EventController::PlayerEvent::DOWNSCREEN) {
				 GameController::downScreen();
			 }*/
			 p->used = false;
		 }
		 p = p->next;
 }
}

 void MainSceneController::dearSprite(float dt) {
#ifdef DEBUG
	 CCLOG("dearSprite start");
#endif
	 static bool first = true;
	 if (!mainGameFinish&&!first)return;
	 first = false;
	
	 //如果有新的要显示
	 if (SpriteController::bNewSprite) {
		 SpriteController::bNewSprite = false;
		
		 static int i = 0;
		 map<long, void*>::iterator it = SpriteController::spriteUsedList.begin();
		 while (it != SpriteController::spriteUsedList.end()) {
			 if (!((Obj*)it->second)->bShow) {
				 ((Obj*)it->second)->bShow = true;
				 SpriteController::createSprites((Obj*)it->second);
			 }
			 it++;
		 }
		
	 }
									// 主线程 渲染obj

	 map<long, void*>::iterator it = SpriteController::spriteUsedList.begin();
	 while (it != SpriteController::spriteUsedList.end()) {
		
		 if (((Obj*)it->second)->bAlive == 1&&((Obj*)it->second)->bUI)//如果需要渲染
		 {
			 SpriteController::changeSpritesPic(it->second);//渲染
		 }
		 it++;
	 }

	 Message::schedule();
	 dearEvent();
	
	 this->dearGameController();
#ifdef DEBUG
	 CCLOG("dearSprite end");
#endif
	 mainGameFinish = false;
 }
 
 void MainSceneController::dearGameController() {
	 if (GameController::bSreeenChange) {
		 GameController::bSreeenChange = false;
	 }
	// GameController::positionSreenCenter(Vec2(100,100),Vec2(0.3,0.3));
 }
 
 void MainSceneController::clearDeath(void* obj_) {
	 ObjController::addDeleteObj((Obj*)obj_);
 }
 
 void MainSceneController::RunGame(float dt) {
#ifdef DEBUG
	 CCLOG("RunGame start");
#endif
	 this->dearMutiThread();
	 ObjController::clearDeathObj();
	 /*this->dearSprite(0);*/

	GameController::timestamp > 10000? (GameController::timestamp = GameController::timestamp % 10000): ++GameController::timestamp;
	updateTexture();
#ifdef DEBUG
	CCLOG("RunGame end");
#endif
	
 }

 int MainSceneController::myCreateThread(int index, pthread_t * tid,
	 const pthread_attr_t * attr,
	 void *(*start) (void *) ,
	 void *arg) {
	 if (index >= MainSceneController::now_threadTop||!bUseful[index]) {
		 if(index >= MainSceneController::now_threadTop)
		 MainSceneController::now_threadTop++;
		 bUseful[index] = true;
		 
		 return  pthread_create(&tids[index], NULL, start, (void*)index);
	 }

	 return -1;

 }

 void MainSceneController::freeData() {
	 MainSceneController::bMainGameRunnig = false;
	 for (int i = 0; i < MAX_THREADS; i++) {
		 pthread_join(MainSceneController::tids[i], NULL);
	 }
	 MainSceneController::now_threadTop = 0;
 }

 void MainSceneController::test(float dt) {
	 for (int i = 0; i < 800; i++) {
		 //this->sprite[i]->retain();
		 this->count[i] = count[i] % 13 + 1;
		 char name[30];
		 sprintf(name, "tank_str_a_d (%d).png", this->count[i]);
		 CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		 this->sprite[i]->setDisplayFrame(frame);
	 }
 }
 void MainSceneController::addTools() {
	 button = CCSprite::createWithSpriteFrameName("box.png");
	 Vec2 unit = GameController::getScreenUnitSize();
	 Vec2 vec = Vec2(GameController::screenSizeW / 8.0 * unit.x, GameController::screenSizeH / 8.0 * unit.y);
	 button->setPosition(vec + Director::getInstance()->getVisibleOrigin());
	 Size size = button->getSpriteFrame()->getRect().size;
	 button->setScaleX(unit.x *  GameController::screenSizeW / 4.0 / size.width);
	 button->setScaleY(unit.y *  GameController::screenSizeH / 4.0 / size.height);
	 nowScene->addChild(button,90);
	 xButtonStr[0] = string("attack");
	 xButtonStr[1] = string("move");
	 xButtonName = Label::createWithSystemFont(xButtonStr[xButtonType], "Arial", GameController::wUnit * GameController::screenSizeW / 16);
	 xButtonName->setColor(Color3B::GREEN);
	 xButtonName->setPosition(vec + Director::getInstance()->getVisibleOrigin());
	 nowScene->addChild(xButtonName,100);
#ifdef MY_TOUCH
	 TouchEventController::addListenArea(0, GameController::screenSizeW / 4.0, 0, GameController::screenSizeH / 4.0,
		 EventController::XButtonCLick);
#endif
 }
 void MainSceneController::CreateTexture() {
	 last_player_texture_x = ObjController::PlayerObj->X / 30 > 3? ObjController::PlayerObj->X / 30:3;
	 last_player_texture_y = ObjController::PlayerObj->Y / 30 > 2 ? ObjController::PlayerObj->Y / 30:2;
	 if(last_player_texture_x != 3)
	 last_player_texture_x = ObjController::PlayerObj->X / 30 < MAP_NUM * POSITION_LIST_X / 30 - 4 ? ObjController::PlayerObj->X / 30 : MAP_NUM * POSITION_LIST_X / 30 - 4;
	 if (last_player_texture_y != 2)
	 last_player_texture_y = ObjController::PlayerObj->Y / 30 < MAP_NUM * POSITION_LIST_Y / 30 - 3 ? ObjController::PlayerObj->Y / 30 : MAP_NUM * POSITION_LIST_Y / 30 - 3;
	 for (int m = 0, i = last_player_texture_x - 3; i <= last_player_texture_x + 3; m++,i++)
		 for (int n = 0, j = last_player_texture_y - 2; j <= last_player_texture_y + 2; n++,j++) {
			 int index = m * 5 + n;
			 textureList[index] = (TextureNode*)malloc(sizeof(TextureNode));
			 textureList[index]->node =	 new Texture(Texture::Type::GREEN, 15 + i * 30, 15 + j * 30, true);
			 textureList[index]->x = i;
			 textureList[index]->y = j;
		 }
 }
 void MainSceneController::updateTexture() {
	 int tmpx = ObjController::PlayerObj->X / 30, tmpy = ObjController::PlayerObj->Y / 30;
	 int xtmpx = MAP_NUM * POSITION_LIST_X / 30 - 4, xtmpy = MAP_NUM * POSITION_LIST_Y / 30 - 3;
	 int x = tmpx > 3 ? tmpx : 3;
	 int y = tmpy > 2 ? tmpy : 2;
	 if(x != 3)
	 x = tmpx < xtmpx ? tmpx : xtmpx;
	 if(y != 2)
	 y = tmpy < xtmpy ? tmpy : xtmpy;
	 if (x - last_player_texture_x > 1 || (x - last_player_texture_x > 0 && tmpx > xtmpx)) {
		 for (int i = 0; i < 35; i++) {
			 if (textureList[i]->x == last_player_texture_x - 3) {
				 textureList[i]->x = last_player_texture_x + 4;
				 textureList[i]->node->X = (last_player_texture_x + 4) * 30 + 15;
			 }
		 }
		 last_player_texture_x++;
	 }
	 else if (last_player_texture_x - x > 1 || (last_player_texture_x  - x> 0  && tmpx < 3)) {
		 for (int i = 0; i < 35; i++) {
			 if (textureList[i]->x == last_player_texture_x + 3) {
				 textureList[i]->x = last_player_texture_x - 4;
				 textureList[i]->node->X = (last_player_texture_x - 4) * 30 + 15;
			 }
		 }
		 last_player_texture_x--;
	 }
	 else if (last_player_texture_y - y > 1 || (last_player_texture_y - y> 0 && tmpy < 2)) {
		 for (int i = 0; i < 35; i++) {
			 if (textureList[i]->y == last_player_texture_y + 2) {
				 textureList[i]->y = last_player_texture_y - 3;
				 textureList[i]->node->Y = (last_player_texture_y - 3) * 30 + 15;
			 }
		 }
		 last_player_texture_y--;
	 }
	 else if (y - last_player_texture_y > 1|| (y - last_player_texture_y > 0 && tmpy > xtmpy)) {
		 for (int i = 0; i < 35; i++) {
			 if (textureList[i]->y == last_player_texture_y - 2) {
				 textureList[i]->y = last_player_texture_y + 3;
				 textureList[i]->node->Y = (last_player_texture_y + 3) * 30 + 15;
			 }
		 }
		 last_player_texture_y++;
	 }
 }
 void* MainSceneController::MainThread(void* args) {
	 while (true) {
		 while (mainGameFinish);
		 ((MainSceneController*)args)->RunGame(0);
		 mainGameFinish = true;
		
#ifdef ANDROID
		 //usleep(10000);
#else
#ifdef WIN_32
		// Sleep(20);
#endif
#endif
	 }
 }


 void MainSceneController::afterInit(float dt) {
#ifdef DEBUG
	 CCLOG("afterInit start");
#endif
	 static  bool once = true;
	 if (GameController::scene == MainSceneController::nowScene&&once) {
		 MainSceneController::nowScene->unschedule(SEL_SCHEDULE(&MainSceneController::afterInit));
		 once = false;
		 addTools();
		// Flower* flower1 = new Flower(Flower::Type::XFLOWER, 35, 35, false);
		
		// Tank* tank2 = new Tank(Tank::Type::STRONG, 27, 40);
		//// tank2->setStatus(Status::STAND);
		// Tank* tank3 = new Tank(Tank::Type::STRONG, 35, 40);
		//// tank3->setStatus(Status::STAND);
		// Tank* tank4 = new Tank(Tank::Type::STRONG, 40, 40);
		//// tank4->setStatus(Status::STAND);
		// Tank* tank5 = new Tank(Tank::Type::STRONG, 45, 40);
		 //tank5->setStatus(Status::STAND);
		 Tank* tank1 = new Tank(Tank::Type::STRONG, 40, 40, false);
		 tank1->harmType = 25;
		 Tank* tank__ = new Tank(Tank::Type::STRONG, 50, 40, true);
		 tank__->harmType = 2;
		 //Missile* mi = new Missile(Missile::Type::MINES, 20, 20,true);
		for (int i = 1; i < 11;i+=5)
			for (int j = 1; j < 11; j+=5)
		Missile* mi1 = new Missile(Missile::Type::MINES, 10 * i, j * 10, true);
		 //Flower* f = new Flower(Flower::Type::XFLOWER, 40, 40, false);
		 //Soldier*s1 = new Soldier(Soldier::Type::LANCER, 16, 6, false);
		//Soldier*s2 = new Soldier(Soldier::Type::LANCER, 22, 22, true);
		//s2->PATROL_set(22,22,10);
		//s2->setStatus(Status::STAND);
		//s2->changeFX(Direction::RIGHT);
		//Soldier*s3 = new Soldier(Soldier::Type::LANCER, 40, 30, false);
		/*s3->setWay(Obj::WayFindType::WANDERING);*/
		/*s3->setStatus(Status::STAND);
		s3->changeFX(Direction::LEFT);*/
		 /*for (int j = 0; j < 20; j+=4)
		 for (int i = 0; i < 20;i++)
			 Tank* tank5 = new Tank(Tank::Type::STRONG, 5 + i*5, 5 + j*5, true);*/
		 for (int i = 2; i < 10; i+=2) {
			 for (int j = 2; j <10; j+=2) {
				//Tank* tank = new Tank(Tank::Type::STRONG, i*5, j*5, true);
			 }
		 }
		 /*Tank* tank4 = new Tank(Tank::Type::STRONG, 35, 40, true);
		 Tank* tank = new Tank(Tank::Type::STRONG, 35, 30, true);
		 Tank* tank11 = new Tank(Tank::Type::STRONG, 25, 30, true);
		 Tank* tank2 = new Tank(Tank::Type::STRONG, 35, 35, true);
		 Tank* tank3 = new Tank(Tank::Type::STRONG, 25, 30, true);*/
		// Flower* flower = new Flower(Flower::Type::FRANGIPANI, 30, 30, true);
		 //Brike* brike = new Brike(Brike::Type::STEEL, 40, 30);
		int nBrike = MapBuildController::MakeMapRange<Brike, Brike::Type>(Brike::Type::STEEL, 20, 200, 10, 200, 100);
		int nflower1= MapBuildController::MakeMapRange<Flower,Flower::Type>(Flower::Type::FRANGIPANI, 10, 100, 10, 100, 100);
		//int nTank = MapBuildController::MakeMapRange<Tank, Tank::Type>(Tank::Type::STRONG, 10, 480, 20, 480, 100);
		
		 int nflower = MapBuildController::MakeMapRange<Flower, Flower::Type>(Flower::Type::FRANGIPANI, 10, 100, 10, 100, 30);
		 auto visibleSize = Director::getInstance()->getVisibleSize();
		 auto origin = Director::getInstance()->getVisibleOrigin();
		 Brike* brik2 = new Brike(Brike::Type::STEEL,50,50);
		 Brike* brik3 = new Brike(Brike::Type::STEEL, 55, 50);
		 Brike* brik4 = new Brike(Brike::Type::STEEL, 50, 55);
		 Brike* brik5 = new Brike(Brike::Type::STEEL, 45, 50);
		 Brike* brik6 = new Brike(Brike::Type::STEEL, 45, 45);
		 auto t = Director::getInstance()->getVisibleSize();
		 for (int i = 0; i < 10; i++)
			 for (int j = 0; j < 10; j++) {
				 if (i == 8 || j == 9) {
					// if ((i == 8 && j == 2))continue;
					 //Brike* brike6 = new Brike(Brike::Type::STEEL, i * 3, j * 2);
				 }
			 }
		
		/* Brike* brike0 = new Brike(Brike::Type::STEEL, 3, 15);
		 Brike* brike1 = new Brike(Brike::Type::STEEL, 6, 15);
		 Brike* brike11 = new Brike(Brike::Type::STEEL, 15, 12);
		 Brike* brike12 = new Brike(Brike::Type::STEEL, 15, 10);
		 Brike* brike3 = new Brike(Brike::Type::STEEL, 15, 8);
		 Brike* brike4 = new Brike(Brike::Type::STEEL, 15, 6);
		 Brike* brike5 = new Brike(Brike::Type::STEEL, 15, 4);
		 Brike* brike6 = new Brike(Brike::Type::STEEL, 15, 2);*/
		 //后面2个参数x,y坐标，
		 //对应屏幕scale为10，即(1,1)=>(10,10)
		 int n = 42;
		// Brike* brike = new Brike(Brike::Type::STEEL, 122, 115);
		 for (int i = 4; i < n; i++)
			 for (int j = 4; j < n; j++) {
				 if (i == 4 || j == 4 || i == 41 || j == 41) 
					 //if (i == 15  || i == 25 || j == 35)
				 {
					// if((i == 1&&j ==1) ||(i == 2 && j == 1)|| (i == 3 && j == 1))
					 //Brike* brike = new Brike(Brike::Type::STEEL, i * 3 , j * 2 );
				 }
			 }
		// int nTank = MapBuildController::MakeMapRange<Tank, Tank::Type>(Tank::Type::STRONG, 13, 110, 8, 70, 10);
		 //for (int i = 0; i < 10; i++)
		// for (int j = 0; j < 10;j++)
		//	 if(i == j)
		// Brike* brike = new Brike(Brike::Type::STEEL, 1 +3*i, 1 + 3 * j + 10);
		 EventController::setObjActionEvent();
		 pthread_t id_1;
		 pthread_create(&id_1, NULL, MainSceneController::MainThread, (void*)this);

		 CreateTexture();
		 this->nowScene->schedule(SEL_SCHEDULE(&MainSceneController::dearSprite), GameController::timeInterval);
	 }
#ifdef DEBUG
	 CCLOG("afterInit end");
#endif
 }


