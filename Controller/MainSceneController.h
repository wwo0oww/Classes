#pragma once
#include"Core\Controller.h"
#include "ui/UIWidget.h"
#include "pthread.h"
#include"TouchEventController.h"
#include"Model\Obj\Building\Texture\Texture.h"
#pragma comment(lib, "pthreadVC2.lib")
#ifdef ANDROID
#include <unistd.h>
#endif // ANDROID
struct threadP {
	int start;
	int end;
};

class MainSceneController : public Controller {
	//属性
public:
	struct TextureNode {
		int x;
		int y;
		Texture*node;
	};
	CCSprite* sprite[100];
	int count[100];
	CCArray* arr;
	static pthread_t tids[MAX_THREADS];//存储 线程id;
	static threadP threadParam[MAX_THREADS];//存储线程参数【数据】;
	static int bThreadRuning[MAX_THREADS];// 某线程 是否开始运作 0未运作 1进入运作 2正在运作;
	static bool bMainGameRunnig;//当前scene是否在运作;
	static int now_threadTop;
	static Scene* nowScene;
	static bool bUseful[MAX_THREADS];
	static int tankNum;
	static int now_thread_Num;
	static bool startGame;
	static CCSprite*button;
	static Label*xButtonName;
	static string xButtonStr[2];
	static XButtonType xButtonType;
	static TextureNode*textureList[35];
	static int last_player_texture_x;
	static int last_player_texture_y;
	static int gold_num ;
private:
	static MainSceneController * m_Instance;
public:
	//方法
	static MainSceneController* GetInstance();
	static bool mainGameFinish;
	void freeData();
	int myCreateThread(int index, pthread_t * tid,
		const pthread_attr_t * attr,
		void *(*start) (void *),
		void *arg);
	static void clearDeath(void*);
	void test(float dt);
	void RunGame(float dt);
	void afterInit(float dt);
	void dearMutiThread();
	void dearSprite(float dt);
	void dearGameController();
	void addTools();
	static void* RunGameThread(void* args);
	static void* MainThread(void* args);
	static void* DearCollision(void* args);
	static void dearEvent();
	static void CreateTexture();
private:
	static void updateTexture();


};