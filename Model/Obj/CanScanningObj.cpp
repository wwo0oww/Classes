#include"CanScanningObj.h"
#include"Controller\MapController.h"
#include"Controller\ObjController.h"
CanScanningObj::CanScanningObj(Obj*self) {
	this->friendList = (int*)malloc(sizeof(int));
	this->friendList[0] = 1;
	this->self = self;
}
void CanScanningObj::initAttackObj(Obj::AttackObj*attackObj) {
	this->attackObj = attackObj;
}
void CanScanningObj::run() {
	
	if (this->scanning_now_time++ >= this->scanning_time) {
		this->scanning_now_time = 0;
		this->scanning_map();
		if (this->attackObj != NULL&&this->attackObj->attackNode == NULL&&self->attackList->attack_head->ID != 0) {
			this->attackObj->attackNode = self->attackList->attack_head;
		}
		//this->OutScanning();
	}
	if(self->ID != ObjController::PlayerID)
	attackEnemy_simple();
}
//1 x 2 y 正[1,2]：大于 负[-1,-2]：小于
int CanScanningObj::getMaxOffset(Obj*obj,int&result) {
	int x_fuhao = 1;
	int y_fuhao = 1;
	int x_offset = self->X > obj->X  ? self->X - obj->X : (self->X - obj->X)*(x_fuhao = -1);
	int y_offset = self->Y > obj->Y  ? self->Y - obj->Y : (self->Y - obj->Y)*(y_fuhao = -1);
	return x_offset > y_offset ? x_offset *(result=1* x_fuhao)*x_fuhao : y_offset*(result=2* x_fuhao)/2*x_fuhao;
}
void CanScanningObj::OutScanning() {
	Obj::AttackNode* p = self->attackList->attack_head;
	while (true) {
		Obj::AttackNode*p_p = NULL;
		
		if (p->ID != 0) {
			
			int result;
			int offset = getMaxOffset(p->obj, result);
			if (offset > this->scannig_range*UNIT_OBJ_MAP) {
				p_p = p->next;
				self->attackList->delete_(p);
			}
		}
		if (p == self->attackList->attack_tail)break;
		if (p_p != NULL)
			p = p_p;
		else
		p = p->next;
	}

}
bool CanScanningObj::canAttack() {
	return true;
}
void CanScanningObj::doAttack(int x, int y) {
}
void CanScanningObj::attackEnemy_simple() {
	if (this->attackObj != NULL&&this->attackObj->attackNode !=NULL&&attackObj->attackNode->ID != 0) {
		int result;
		if (attack_range >= this->getMaxOffset(this->attackObj->attackNode->obj,result)) {
			if (this->canAttack()) {
				this->doAttack(this->attackObj->attackNode->obj->X, this->attackObj->attackNode->obj->Y);
			}
		}
		else {
			int x, y;
			abs(result) == 2 ? (x = this->attackObj->attackNode->obj->X + 10 * result)*(y = this->attackObj->attackNode->obj->Y) :
				(x = this->attackObj->attackNode->obj->X)*(y = this->attackObj->attackNode->obj->Y + 20 * result);
			self->setAim(x,y);
		}
	}
}
//以区域【UNIT_OBJ_MAP*UNIT_OBJ_MAP】为单位
void CanScanningObj::scanning_map() {
	self->attackList->clear();
	static int max_x = MAP_NUM*POSITION_LIST_X / UNIT_OBJ_MAP;
	static int max_y = MAP_NUM*POSITION_LIST_Y / UNIT_OBJ_MAP;
	int now_num = 0;
	int x = self->X / UNIT_OBJ_MAP;
	int y = self->Y / UNIT_OBJ_MAP;
	auto map_unit_func = [&](int index_x, int index_y)->int {//返回0 退出此函数
		MapController::SearchMapNode * node = MapController::objMap[index_x][index_y];
		if (node == NULL)return 1;
		MapController::MapNode*tmp = node->head;
		while (tmp != NULL) {
			Obj*obj = (Obj*)tmp->obj;
			if (!obj->canBeenScanning&&!self->canScanningAll) { tmp = tmp->next; continue; }
			bool bFriend = false;
			for (int i = 0; i < this->friend_len; i++) {
				if (this->friendList[i] == obj->harmType || self->harmType == obj->harmType) {
					bFriend = true;
					break;
				}
			}
			if (!bFriend) {
				self->attackList->add_(obj);

				now_num++;
				if (this->enemy_num != 0 && now_num >= this->enemy_num) {
					return 0;
				}
			}
			tmp = tmp->next;
		}
	};

	for (int n = 1; n <= this->scannig_range; n++) {
		for (int index_x = x - n; index_x <= x+n; index_x++)
		{
			if (index_x < 0 || index_x >= max_x)continue;
			if (index_x == x + n || index_x == x - n) {
				for (int index_y = y - n; index_y <= y + n; index_y++) {
					if (index_y < 0 || index_y >= max_y)continue;
					if (map_unit_func(index_x, index_y) == 0)return;
				}
			}
			else {
				if (y - n >= 0)
					if (map_unit_func(index_x, y - n) == 0)return;
				if (y + n < max_x)
					if (map_unit_func(index_x, y + n) == 0)return;
			}
		}
	}
}
void CanScanningObj::delete_scanning_death_obj(Obj*obj, Obj*param) {
	obj->attackList->delete_by_id(param->ID);
}