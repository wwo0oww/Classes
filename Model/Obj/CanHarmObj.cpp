#include"CanHarmObj.h"
CanHarmObj::CanHarmObj(Obj*self) {
	this->self = self;
}
//以点为单位
void CanHarmObj::dearHarm(void*obj_, int x, int y) {
	Obj*obj = (Obj*)obj_;
	static int MAX_SPRITE_SIZE_2 = MAX_SPRITE_SIZE / 2, MAP_NUM_POSITION_LIST_X = MAP_NUM*POSITION_LIST_X, MAP_NUM_POSITION_LIST_Y = MAP_NUM*POSITION_LIST_Y;
	int minx = x > this->harm_x_range ? x - this->harm_x_range : 0, miny = y > this->harm_y_range ? y - this->harm_y_range : 0, maxx = x + this->harm_x_range<MAP_NUM_POSITION_LIST_X ? x + this->harm_x_range : MAP_NUM_POSITION_LIST_X - 1, maxy = y + this->harm_y_range < MAP_NUM_POSITION_LIST_Y ? y + this->harm_y_range : MAP_NUM_POSITION_LIST_Y - 1;
	int cminx = minx - MAX_SPRITE_SIZE_2 > 0 ? minx - MAX_SPRITE_SIZE_2 : 0;
	int cminy = miny - MAX_SPRITE_SIZE_2> 0 ? miny - MAX_SPRITE_SIZE_2 : 0;
	int cmaxx = maxx + MAX_SPRITE_SIZE_2 < MAP_NUM_POSITION_LIST_X ? maxx + MAX_SPRITE_SIZE_2 : MAP_NUM_POSITION_LIST_X - 1;
	int cmaxy = maxy + MAX_SPRITE_SIZE_2 < MAP_NUM_POSITION_LIST_Y ? maxy + MAX_SPRITE_SIZE_2 : MAP_NUM_POSITION_LIST_Y - 1;
	for (int i = cminx / UNIT_OBJ_MAP; i <= cmaxx / UNIT_OBJ_MAP; i++) {
		for (int j = cminy / UNIT_OBJ_MAP; j <= cmaxy / UNIT_OBJ_MAP; j++) {
			MapController::SearchMapNode * node = MapController::objMap[i][j];
			if (node == NULL)continue;
			MapController::MapNode*tmp = node->head;
			while (tmp != NULL) {
				if (tmp->ID != 0 && ((Obj*)tmp->obj)->harmType != self->harmType) {

					Obj*obj = (Obj*)tmp->obj;
					if ((obj->X - obj->W / 2 - minx < this->harm_x_range * 2 && obj->X + obj->W / 2.0 > minx) &&
						((obj->Y - obj->H / 2 - miny < this->harm_y_range * 2 && obj->Y + obj->H / 2.0 > miny))) {
						if (obj->SetHP(obj->now_HP - harm, self) <= 0) {

						}
					}

				}
				tmp = tmp->next;
			}
		}
	}
}