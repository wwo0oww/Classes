#pragma once
//#ifndef android
//#define android
//#endif // !android
//#define DEBUG

#define WIN_32
#ifndef MODE_MAP
#define MODE_MAP
#endif // !MODE_MAP



#include "cocos2d.h"
#include<iostream>
#include<functional>
#include"stdio.h"
#include"Core\functionh.h"
using namespace std;
USING_NS_CC;
#define MAX_PREFIX 40
#define MAP_NUM 1 //地图 行列数
#define POSITION_LIST_X 500 //地图x轴总数
#define POSITION_LIST_Y 500 //地图y轴总数
#define MAX_THREADS 256 //线程总是
#define MAX_TYPE 40 //obj类型总数 
#define MAX_MAP_SIZE 100 //obj地图最大size
#define MAX_SPRITE_SIZE 10 //obj占地地图最大长或宽
#define MAX_HIGH 100 //最大高度 用来处理 显示 层级等
#define OBJ_MAX_SPRITE 5//一个obj拥有的最大sprite
#define MAX_STORAGE_FX 10//obj存储的最大fx
#define MAX_SPRITE_NUM 2000//sprite最多数量
#define MAX_BULLET 2//obj拥有做多子弹
#define UNIT_OBJ_MAP 10//SearchMapNode 对应的map的比例
#define MAX_STATUS 3
#define MAX_DIRECTION 4
#define MY_TOUCH
#define MAX_XBUTTON 2
#define MAX_XMISSILE 10
#define MAX_MINES 20
struct Position {
	float x;
	float y;
};
enum  XButtonType {
	ATTACK_B,
	MOVE_B,
};
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,

};

enum Status
{
	MOVE = 0x0001,
	ATTACK = 0x0002,
	STAND = 0x0004,
};

namespace PrefixInfo {
	
	struct PrefixNode{
		 char prefix_m_up[MAX_PREFIX];

		//前缀
		 char prefix_m_down[MAX_PREFIX];
		//前缀
		 char prefix_m_right[MAX_PREFIX];
		//前缀
		 char prefix_m_left[MAX_PREFIX];
		//前缀
		 char prefix_a_up[MAX_PREFIX];
		//前缀
		 char prefix_a_down[MAX_PREFIX];
		//前缀
		 char prefix_a_right[MAX_PREFIX];
		//前缀
		 char prefix_a_left[MAX_PREFIX];
		//前缀
		 char prefix_ul_turn[MAX_PREFIX];
		 char prefix_ur_turn[MAX_PREFIX];
		//前缀
		 char prefix_dr_turn[MAX_PREFIX];
		 char prefix_dl_turn[MAX_PREFIX];

		 char prefix_s_left[MAX_PREFIX];
		 char prefix_s_right[MAX_PREFIX];
		 char prefix_s_up[MAX_PREFIX];
		 char prefix_s_down[MAX_PREFIX];
		 
		 Vec2 scale_over[4] ;
		 int mrotation[4];
		 int arotation[4];
		 int srotation[4];

		 int prefix_ul_turn_num;
		 int prefix_ur_turn_num;
		//前缀
		 int prefix_dr_turn_num;
		 int prefix_dl_turn_num;

		//转角度
		 int angle_right;
		//转角度
		 int angle_left;
		//转角度
		 int angle_up;
		//转角度
		 int angle_down;
		//转角度
		 int index_up_attack;

		 int index_down_attack;

		 int index_right_attack;

		 int index_left_attack;

		 int index_up_attack_num;

		 int index_down_attack_num;

		 int index_right_attack_num;

		 int index_left_attack_num;

		 int index_up_move_num;

		 int index_down_move_num;

		 int index_right_move_num;

		 int index_left_move_num;

		 int index_up_stand_num;

		 int index_down_stand_num;

		 int index_right_stand_num;

		 int index_left_stand_num;
	};

	class PrefixData {
	public:
		
	    PrefixNode * prefixList[MAX_TYPE];
		  PrefixData() {
			init();
			InitStrongTank();//0
			InitSTELLBRIKE();//1
			//plant
			InitFRANGIPANI();//2
			InitXFlower();//3
			InitLANCER();//4
			//weapon
			InitXMISSILE();//20
			InitTEXTURE(); //>=30 <=40
			//prefixList[0]->angle_down;
		
			
		  }
		  void InitTEXTURE() {
			  sprintf(prefixList[30]->prefix_s_left, "texture_1.png");
			  sprintf(prefixList[30]->prefix_s_right, "texture_1.png");
			  sprintf(prefixList[30]->prefix_s_up, "texture_1.png");
			  sprintf(prefixList[30]->prefix_s_down, "texture_1.png");
		  }
		  void init() {
			  for (int i = 0; i < MAX_TYPE; i++) {
				  prefixList[i] =(PrefixNode*)malloc(sizeof(PrefixNode));
				  for (int j = 0; j < 4; j++) {
					  
					  prefixList[i]->scale_over[j] = Vec2(1, 1);
					  prefixList[i]->mrotation[j] = 0;
					  prefixList[i]->arotation[j] = 0;
					  prefixList[i]->srotation[j] = 0;
				  }
			  }
			  
		  }
		  void InitLANCER() {
			  prefixList[4]->index_down_move_num = 10;
			  prefixList[4]->index_down_attack_num = 10;
			  prefixList[4]->index_down_stand_num = 7;
			  prefixList[4]->index_down_attack = 5;
			  sprintf(prefixList[4]->prefix_m_down, "soldier_lancer_m_d");
			  sprintf(prefixList[4]->prefix_a_down, "soldier_lancer_m_d");
			  sprintf(prefixList[4]->prefix_s_down, "soldier_lancer_s_d");

			  prefixList[4]->index_up_move_num = 10;
			  prefixList[4]->index_up_attack_num = 10;
			  prefixList[4]->index_up_stand_num = 7;
			  prefixList[4]->index_up_attack = 5;
			  sprintf(prefixList[4]->prefix_m_up, "soldier_lancer_m_u");
			  sprintf(prefixList[4]->prefix_a_up, "soldier_lancer_m_u");
			  sprintf(prefixList[4]->prefix_s_up, "soldier_lancer_s_u");

			  prefixList[4]->index_right_move_num = 10;
			  prefixList[4]->index_right_attack_num = 10;
			  prefixList[4]->index_right_stand_num = 7;
			  prefixList[4]->index_right_attack = 5;
			  sprintf(prefixList[4]->prefix_m_right, "soldier_lancer_m_r");
			  sprintf(prefixList[4]->prefix_a_right, "soldier_lancer_m_r");
			  sprintf(prefixList[4]->prefix_s_right, "soldier_lancer_s_r");

			  prefixList[4]->index_left_move_num = 10;
			  prefixList[4]->index_left_attack_num = 10;
			  prefixList[4]->index_left_stand_num = 7;
			  prefixList[4]->index_left_attack = 5;
			  sprintf(prefixList[4]->prefix_m_left, "soldier_lancer_m_l");
			  sprintf(prefixList[4]->prefix_a_left, "soldier_lancer_m_l");
			  sprintf(prefixList[4]->prefix_s_left, "soldier_lancer_s_l");
		  }
		  void InitXMISSILE() {
			  //prefixList[20] = (PrefixNode*)malloc(sizeof(PrefixNode));
			  /*UP,
			  RIGHT,
			  DOWN,
			  LEFT,*/
			  // stand move attack 
			  int i = 4;
			 
			  prefixList[20]->mrotation[0] = 270;
			  prefixList[20]->mrotation[1] = 0;
			  prefixList[20]->mrotation[2] = 90;
			  prefixList[20]->mrotation[3] = 180;
			  /*UP,
			  RIGHT,
			  DOWN,
			  LEFT,*/
			  prefixList[20]->index_down_move_num = 4;
			  prefixList[20]->index_down_attack_num = 17;
			  prefixList[20]->index_down_stand_num = 4;
			  prefixList[20]->index_down_attack = 8;
			  sprintf(prefixList[20]->prefix_m_down, "weapon_xmissile_m_r");
			  sprintf(prefixList[20]->prefix_a_down, "weapon_xmissile_a");
			  sprintf(prefixList[20]->prefix_s_down, "weapon_xmissile_m_r");

			  prefixList[20]->index_up_move_num = 4;
			  prefixList[20]->index_up_attack_num = 17;
			  prefixList[20]->index_up_stand_num = 4;
			  prefixList[20]->index_up_attack = 8;
			  sprintf(prefixList[20]->prefix_m_up, "weapon_xmissile_m_r");
			  sprintf(prefixList[20]->prefix_a_up, "weapon_xmissile_a");
			  sprintf(prefixList[20]->prefix_s_up, "weapon_xmissile_m_r");

			  prefixList[20]->index_right_move_num = 4;
			  prefixList[20]->index_right_attack_num = 17;
			  prefixList[20]->index_right_stand_num = 4;
			  prefixList[20]->index_right_attack = 8;
			  sprintf(prefixList[20]->prefix_m_right, "weapon_xmissile_m_r");
			  sprintf(prefixList[20]->prefix_a_right, "weapon_xmissile_a");
			  sprintf(prefixList[20]->prefix_s_right, "weapon_xmissile_m_r");

			  prefixList[20]->index_left_move_num = 4;
			  prefixList[20]->index_left_attack_num = 17;
			  prefixList[20]->index_left_stand_num = 4;
			  prefixList[20]->index_left_attack = 8;
			  sprintf(prefixList[20]->prefix_m_left, "weapon_xmissile_m_r");
			  sprintf(prefixList[20]->prefix_a_left, "weapon_xmissile_a");
			  sprintf(prefixList[20]->prefix_s_left, "weapon_xmissile_m_r");

			  /*UP,
			  RIGHT,
			  DOWN,
			  LEFT,*/
			  prefixList[21]->index_down_move_num = 2;
			  prefixList[21]->index_down_attack_num = 13;
			  prefixList[21]->index_down_stand_num = 2;
			  prefixList[21]->index_down_attack = 5;
			  sprintf(prefixList[21]->prefix_m_down, "weapon_mines");
			  sprintf(prefixList[21]->prefix_a_down, "weapon_mines_a");
			  sprintf(prefixList[21]->prefix_s_down, "weapon_mines");

			  prefixList[21]->index_up_move_num = 2;
			  prefixList[21]->index_up_attack_num = 13;
			  prefixList[21]->index_up_stand_num = 2;
			  prefixList[21]->index_up_attack = 5;
			  sprintf(prefixList[21]->prefix_m_up, "weapon_mines");
			  sprintf(prefixList[21]->prefix_a_up, "weapon_mines_a");
			  sprintf(prefixList[21]->prefix_s_up, "weapon_mines");

			  prefixList[21]->index_right_move_num = 2;
			  prefixList[21]->index_right_attack_num = 13;
			  prefixList[21]->index_right_stand_num = 2;
			  prefixList[21]->index_right_attack = 5;
			  sprintf(prefixList[21]->prefix_m_right, "weapon_mines");
			  sprintf(prefixList[21]->prefix_a_right, "weapon_mines_a");
			  sprintf(prefixList[21]->prefix_s_right, "weapon_mines");

			  prefixList[21]->index_left_move_num = 4;
			  prefixList[21]->index_left_attack_num = 17;
			  prefixList[21]->index_left_stand_num = 4;
			  prefixList[21]->index_left_attack = 8;
			  sprintf(prefixList[21]->prefix_m_left, "weapon_mines");
			  sprintf(prefixList[21]->prefix_a_left, "weapon_mines_a");
			  sprintf(prefixList[21]->prefix_s_left, "weapon_mines");

		  }
		  void InitFRANGIPANI() {
			 // prefixList[2] = (PrefixNode*)malloc(sizeof(PrefixNode));
			  int i = 4;
			  while(--i>=0){
				prefixList[2]->scale_over[i] = Vec2(1,1);
			  }
			  sprintf(prefixList[2]->prefix_s_left, "frangipani.png");
			  sprintf(prefixList[2]->prefix_s_right, "frangipani.png");
			  sprintf(prefixList[2]->prefix_s_up, "frangipani.png");
			  sprintf(prefixList[2]->prefix_s_down, "frangipani.png");
		  }
		  void InitSTELLBRIKE() {
			 // prefixList[1] = (PrefixNode*)malloc(sizeof(PrefixNode));
			  int i = 4;
			  while (--i >= 0) {
				  prefixList[1]->scale_over[i] = Vec2(1, 1);
			  }
			  sprintf(prefixList[1]->prefix_s_left,"brike_steel.png");
			  sprintf(prefixList[1]->prefix_s_right, "brike_steel.png");
			  sprintf(prefixList[1]->prefix_s_up, "brike_steel.png");
			  sprintf(prefixList[1]->prefix_s_down, "brike_steel.png");
		  }

		   void InitXFlower() {
			  
			//prefixList[3] = (PrefixNode*)malloc(sizeof(PrefixNode));
			int i = 4;
			while (--i >= 0) {
				if (i == 1) {
					prefixList[3]->scale_over[i] = Vec2(-1, 1);
				}
				else {
					prefixList[3]->scale_over[i] = Vec2(1, 1);
				}
			}
			/*UP,
			RIGHT,
			DOWN,
			LEFT,*/
			prefixList[3]->index_down_move_num = 7;
			prefixList[3]->index_down_attack_num = 11;
			prefixList[3]->index_down_stand_num = 7;
			prefixList[3]->index_down_attack = 8;
			sprintf(prefixList[3]->prefix_m_down, "xflower_s_l");
			sprintf(prefixList[3]->prefix_a_down, "xflower_a_l");
			sprintf(prefixList[3]->prefix_s_down, "xflower_s_l");

			prefixList[3]->index_up_move_num = 7;
			prefixList[3]->index_up_attack_num = 11;
			prefixList[3]->index_up_stand_num = 7;
			prefixList[3]->index_up_attack = 8;
			sprintf(prefixList[3]->prefix_m_up, "xflower_s_l");
			sprintf(prefixList[3]->prefix_a_up, "xflower_a_l");
			sprintf(prefixList[3]->prefix_s_up, "xflower_s_l");

			prefixList[3]->index_right_move_num = 7;
			prefixList[3]->index_right_attack_num = 11;
			prefixList[3]->index_right_stand_num = 7;
			prefixList[3]->index_right_attack = 8;
			sprintf(prefixList[3]->prefix_m_right, "xflower_s_l");
			sprintf(prefixList[3]->prefix_a_right, "xflower_a_l");
			sprintf(prefixList[3]->prefix_s_right, "xflower_s_l");

			prefixList[3]->index_left_move_num = 7;
			prefixList[3]->index_left_attack_num = 11;
			prefixList[3]->index_left_stand_num = 7;
			prefixList[3]->index_left_attack = 8;
			sprintf(prefixList[3]->prefix_m_left, "xflower_s_l");
			sprintf(prefixList[3]->prefix_a_left, "xflower_a_l");
			sprintf(prefixList[3]->prefix_s_left, "xflower_s_l");

		}


		  void InitStrongTank() {
			  
			//prefixList[0] = (PrefixNode*)malloc(sizeof(PrefixNode));
			int i = 4;
			while (--i >= 0) {
				prefixList[0]->scale_over[i] = Vec2(1, 1);
			}
			prefixList[0]->index_down_move_num = 10;
			prefixList[0]->index_down_attack_num = 13;
			prefixList[0]->index_down_stand_num = 10;
			prefixList[0]->index_down_attack = 6;
			sprintf(prefixList[0]->prefix_m_down, "tank_str_m_d");
			sprintf(prefixList[0]->prefix_a_down, "tank_str_a_d");
			sprintf(prefixList[0]->prefix_s_down, "tank_str_m_d");

			prefixList[0]->index_up_move_num = 11;
			prefixList[0]->index_up_attack_num = 12;
			prefixList[0]->index_up_stand_num = 9;
			prefixList[0]->index_up_attack = 6;
			sprintf(prefixList[0]->prefix_m_up, "tank_str_m_u");
			sprintf(prefixList[0]->prefix_a_up, "tank_str_a_u");
			sprintf(prefixList[0]->prefix_s_up, "tank_str_m_u");

			prefixList[0]->index_right_move_num = 9;
			prefixList[0]->index_right_attack_num = 15;
			prefixList[0]->index_right_stand_num = 9;
			prefixList[0]->index_right_attack = 9;
			sprintf(prefixList[0]->prefix_m_right, "tank_str_m_r");
			sprintf(prefixList[0]->prefix_a_right, "tank_str_a_r");
			sprintf(prefixList[0]->prefix_s_right, "tank_str_m_r");

			prefixList[0]->index_left_move_num = 9;
			prefixList[0]->index_left_attack_num = 15;
			prefixList[0]->index_left_stand_num = 9;
			prefixList[0]->index_left_attack = 9;
			sprintf(prefixList[0]->prefix_m_left, "tank_str_m_l");
			sprintf(prefixList[0]->prefix_a_left, "tank_str_a_l");
			sprintf(prefixList[0]->prefix_s_left, "tank_str_m_l");



			sprintf(prefixList[0]->prefix_dr_turn, "tank_str_rd");
			prefixList[0]->prefix_dr_turn_num = 1;
			sprintf(prefixList[0]->prefix_dl_turn, "tank_str_ld");
			prefixList[0]->prefix_dl_turn_num = 1;
			sprintf(prefixList[0]->prefix_ur_turn, "tank_str_ru");
			prefixList[0]->prefix_ur_turn_num = 1;
			sprintf(prefixList[0]->prefix_ul_turn, "tank_str_lu");
			prefixList[0]->prefix_ul_turn_num = 1;
		}
		 void DeletePrefixList() {
			for (int i = 0; i < MAX_TYPE; i++) {
				if(prefixList[i] != NULL)
				delete prefixList[i];
			}
		}

	};
	static const  PrefixData * prefixData = new PrefixData();
	
}

namespace CoverInfo {
	class CoverData{
	private:
		Position*coverList[MAX_TYPE][MAX_STATUS][MAX_DIRECTION];
		Vec2 picData[MAX_TYPE][MAX_STATUS][MAX_DIRECTION];
		Position* picOffset[MAX_TYPE][MAX_STATUS][MAX_DIRECTION];
	public:
		Vec2 coverData[MAX_TYPE];
		
		 Position* getCoverList(int type,Status status,Direction fx) const {
			int now_status = 0;
			if (status&Status::ATTACK) {
				now_status = 0;
			}else if (status&Status::MOVE) {
				now_status = 1;
			}
			else if (status&Status::STAND) {
				now_status = 2;
			}
			return coverList[type][now_status][fx];
		}
		 Position* getPicOffset(int type, Status status, Direction fx) const {
			 int now_status = 0;
			 if (status&Status::ATTACK) {
				 now_status = 0;
			 }
			 else if (status&Status::MOVE) {
				 now_status = 1;
			 }
			 else if (status&Status::STAND) {
				 now_status = 2;
			 }
			 return picOffset[type][now_status][fx];
		 }
		 Vec2 getPicList(int type, Status status, Direction fx) const {
			 int now_status = 0;
			 if (status&Status::ATTACK) {
				 now_status = 0;
			 }
			 else if (status&Status::MOVE) {
				 now_status = 1;
			 }
			 else if (status&Status::STAND) {
				 now_status = 2;
			 }
			 return picData[type][now_status][fx];
		 }
		 void initCoverList() {
			 for (int i = 0; i < MAX_TYPE; i++) {
				 for (int j = 0; j < MAX_STATUS; j++)
				 {
					 for (int z = 0; z < MAX_DIRECTION; z++) {
						 if (coverData[i].x != 0) {
							 coverList[i][j][z] = setCoverList(i);
						 }
					 }
				 }
			 }
			 //xflower
			// int index = 0;
			// for (int i = -coverData[3].x / 2; i <= ceil(coverData[3].x / 2.0) - 1; i++) {
			//	 for (int j = -coverData[3].y / 2 - 1; j <= ceil(coverData[3].y / 2.0) - 2; j++) {
			//		 for (int i = 0; i < MAX_STATUS; i++) {
			//			 for (int j = 0; j < MAX_DIRECTION; j++)
			//			 {
			//				 coverList[3][i][j][index].x = i;
			//				 coverList[3][i][j][index].y = j;
			//				
			//			 }
			//		 }
			//		 index++;
			//	 }
			// }
		 //
			////FRANGIPANI
			//for (int i = 0; i < MAX_STATUS; i++)
			//{
			//	for (int j = 0; j < MAX_DIRECTION; j++) {
			//		coverList[2][i][j][0].x = 0;
			//		coverList[2][i][j][0].y = -3;
			//		
			//		coverList[2][i][j][1].x = 0;
			//		coverList[2][i][j][1].y = -4;
			//		
			//		coverList[2][i][j][2].x = 1;
			//		coverList[2][i][j][2].y = -3;
			//		
			//		coverList[2][i][j][3].x = 1;
			//		coverList[2][i][j][3].y = -4;
			//	}
			//}
			////XMISSILE
			//for (int i = 0; i < MAX_STATUS; i++)
			//{
			//	//上下
			//	{
			//		coverList[20][i][0][0].x = coverList[20][i][2][0].x = 0;
			//		coverList[20][i][0][0].y = coverList[20][i][2][0].y = 0;

			//		coverList[20][i][0][1].x = coverList[20][i][2][1].x = 0;
			//		coverList[20][i][0][1].y = coverList[20][i][2][1].y = 1;

			//		coverList[20][i][0][2].x = coverList[20][i][2][2].x = 0;
			//		coverList[20][i][0][2].y = coverList[20][i][2][2].y = -1;

			//		coverList[20][i][0][3].x = coverList[20][i][2][3].x = 0;
			//		coverList[20][i][0][3].y = coverList[20][i][2][3].y = -2;
			//	}
			//	//左右
			//	{
			//		coverList[20][i][1][0].x = coverList[20][i][3][0].x = 0;
			//		coverList[20][i][1][0].y = coverList[20][i][3][0].y = 0;

			//		coverList[20][i][1][1].x = coverList[20][i][3][1].x = 1;
			//		coverList[20][i][1][1].y = coverList[20][i][3][1].y = 0;

			//		coverList[20][i][1][2].x = coverList[20][i][3][2].x = -1;
			//		coverList[20][i][1][2].y = coverList[20][i][3][2].y = 0;

			//		coverList[20][i][1][3].x = coverList[20][i][3][3].x = -2;
			//		coverList[20][i][1][3].y = coverList[20][i][3][3].y = 0;
			//	}

			//}
			//coverList[0].x = 0;
			//			coverList[0].y = 0;
			//			
			//			coverList[1].x = 0;
			//			coverList[1].y = 1;
			//
			//			coverList[2].x = 0;
			//			coverList[2].y = -1;
			//			coverList[3].x = 0;
			//			coverList[3].y = -2;
			//			break;
			//		case Direction::RIGHT:
			//			
			//		case Direction::LEFT:
			//			coverList[0].x = 0;
			//			coverList[0].y = 0;
			//
			//			coverList[1].x = 1;
			//			coverList[1].y = 0;
			//
			//			coverList[2].x = -1;
			//			coverList[2].y = 0;
			//			coverList[3].x = -2;
			//			coverList[3].y = 0;
			
		}
		Position* setCoverList(int type) {
			Position*coverList = (Position*)malloc
				((coverData[type].x*coverData[type].y)*sizeof(Position));
			int index = 0;
			for (int i = -coverData[type].x / 2; i <= ceil(coverData[type].x / 2.0) - 1; i++) {
				for (int j = -coverData[type].y / 2; j <= ceil(coverData[type].y / 2.0) - 1; j++) {
					coverList[index].x = i;
					coverList[index].y = j;
					index++;
				}
			}
			return coverList;
		}
		void initPic() {
			for (int i = 0; i < MAX_STATUS; i++)
				for (int j = 0; j < MAX_DIRECTION; j++) {
					picData[0][i][j].x = 5;//tank str
					picData[0][i][j].y = 5;
					picData[1][i][j].x = 3;//brike
					picData[1][i][j].y = 3;
					picData[2][i][j].x = 6;
					picData[2][i][j].y = 9;
					picData[3][i][j].x = 4;
					picData[3][i][j].y = 6;
					picData[30][i][j].x = 30.25;
					picData[30][i][j].y = 30.25;
				}
			picData[20][0][0].x = picData[20][0][1].x = picData[20][0][2].x = picData[20][0][3].x = 6;
			picData[20][0][0].y = picData[20][0][1].y = picData[20][0][2].y = picData[20][0][3].y = 12;
			picData[20][1][1].x = picData[20][1][3].x = 4;
			picData[20][1][1].y = picData[20][1][3].y = 1;

			picData[20][1][0].x = picData[20][1][2].x = 4;
			picData[20][1][0].y = picData[20][1][2].y = 1;
			//
			picData[21][0][0].x = picData[21][0][1].x = picData[21][0][2].x = picData[21][0][3].x = 1.5;
			picData[21][0][0].y = picData[21][0][1].y = picData[21][0][2].y = picData[21][0][3].y = 1;
			
			picData[21][2][0].x = picData[21][2][1].x = picData[21][2][2].x = picData[21][2][3].x = 2;
			picData[21][2][0].y = picData[21][2][1].y = picData[21][2][2].y = picData[21][2][3].y = 1;

			picData[4][1][0].x = picData[4][1][2].x = 2;//lancer
			picData[4][1][0].y = picData[4][1][2].y = 4;
			picData[4][1][1].x = picData[4][1][3].x = 4;//lancer
			picData[4][1][1].y = picData[4][1][3].y = 4;

			picData[4][0][0].x = picData[4][0][2].x = 2;//lancer
			picData[4][0][0].y = picData[4][0][2].y = 4;
			picData[4][0][1].x = picData[4][0][3].x = 4;//lancer
			picData[4][0][1].y = picData[4][0][3].y = 4;

			picData[4][2][0].x = picData[4][2][2].x = 2;//lancer
			picData[4][2][0].y = picData[4][2][2].y = 4;
			picData[4][2][1].x = picData[4][2][3].x = 1;//lancer
			picData[4][2][1].y = 4;
			picData[4][2][3].y = 5;

			
		}
		void initPicOffset() {
			for (int i = 0; i < MAX_TYPE; i++) {
				for (int j = 0; j < MAX_STATUS; j++)
				{
					for (int z = 0; z < MAX_DIRECTION; z++) {
						if (coverData[i].x != 0) {
							picOffset[i][j][z] = (Position*)malloc(sizeof(Position));
							picOffset[i][j][z]->x = 0;
							picOffset[i][j][z]->y = 0;
						}
					}
				}
			}
			for (int i = 0; i < MAX_STATUS; i++) {
				for (int j = 0; j < MAX_DIRECTION; j++) {
					picOffset[0][i][j]->x = 0;
					picOffset[0][i][j]->y = 0;
					picOffset[1][i][j]->x = 0;
					picOffset[1][i][j]->y = 0;
					picOffset[2][i][j]->x = 0;
					picOffset[2][i][j]->y = -0.5;
					picOffset[3][i][j]->x = 0;
					picOffset[3][i][j]->y = 1;
					picOffset[4][i][j]->x = 0;
					picOffset[4][i][j]->y = 0;
					
					picOffset[20][i][j]->x = 0;
					picOffset[20][i][j]->y = 0;
					
				}
			}
			picOffset[20][0][0]->x = picOffset[20][0][1]->x = picOffset[20][0][2]->x = picOffset[20][0][3]->x = 0;
			picOffset[20][0][0]->y = picOffset[20][0][1]->y =  picOffset[20][0][3]->y = 9;
			picOffset[20][0][2]->y = 11;
			picOffset[20][1][0]->x = 0;
			picOffset[20][1][0]->y = -1;
			picOffset[20][1][2]->x = 0;
			picOffset[20][1][2]->y = 1;

			picOffset[20][1][1]->x = -1;
			picOffset[20][1][1]->y = 0;

			picOffset[20][1][1]->x = 1;
			picOffset[20][1][1]->y = 0;

			picOffset[21][0][0]->x = picOffset[21][0][1]->x = picOffset[21][0][2]->x = picOffset[21][0][3]->x = 0;
			picOffset[21][0][0]->y = picOffset[21][0][1]->y = picOffset[21][0][2]->x = picOffset[21][0][3]->y = 0;
		}
		void initCover() {
			for (int i = 0; i < MAX_TYPE; i++) {
				coverData[i].x = coverData[i].y = 0;
			}
			coverData[0].x = 5;//tank str
			coverData[0].y = 5;
			coverData[1].x = 3;//brike
			coverData[1].y = 2;
			coverData[2].x = 1;
			coverData[2].y = 1;
			coverData[3].x = 2;
			coverData[3].y = 2;
			coverData[4].x = 2;//lancer
			coverData[4].y = 1;
			coverData[20].x = 1;
			coverData[20].y = 1;

			coverData[21].x = 2;
			coverData[21].y = 1;

			coverData[30].x = 1;
			coverData[30].y = 1;
		}
		CoverData() {
			initCover();
			initPic();
			initPicOffset();
			initCoverList();
			
		}
	};
	static const  CoverData* coverData = new CoverData();

}

namespace EnumData {
	enum LogType
	{
		WORD = 0x0001,
		PER
	};
}
namespace ObjINI {
	
	//void initObj(int i,Obj *obj) {
	//	switch (i) {
	//	case 0x000001:// tank strong

	//		break;
	//	}
	//}
}
namespace ClassData {
	class ObjData {
	public:
		/*struct RemoveNodeData {
			std::vector<Obj*>* srcList;
			std::vector<int> deleteList;
		};*/
		//struct RemoveNodeData _RemoveNodeData;
		//Direction _direction;
		int _int;
		float _float;
		long _long;
		float _x;
		float _y;
		ObjData(int p) {
			this->_int = p;
		}
		ObjData(float p) {
			this->_float = p;
		}
		ObjData(long p) {
			this->_long = p;
		}
		/*ObjData(Direction p) {
			this->_direction = p;
		}*/
		ObjData(float p1, float p2) {
			this->_x = p1;
			this->_y = p2;
		}
		/*ObjData(RemoveNodeData p) {
			this->_RemoveNodeData = p;
		}*/
	};
}