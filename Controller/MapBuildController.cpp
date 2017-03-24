#include"MapBuildController.h"
#include"MapController.h"
#include"Model\Obj\Weapon\Missile.h"
#include"Model\Obj\Plant\Flower\Flower.h"
#include"Model\Obj\Biological\Tank\Tank.h"

MapBuildController* MapBuildController::m_Instance = new MapBuildController();
MapBuildController* MapBuildController::GetInstance() {
	return m_Instance;
}
//参数
//要放置的类型
//x_start 开始横坐标 x_range 范围
// y_start 开始横坐标 y_range 范围
//count 数量
//<T> 要放置的类型
//返回值 放置成功的数量
template<class T,class Type>
int MapBuildController::MakeMapRange(Type type, int x_start, int x_range, int y_start, int y_range, int count) {
	int MAX_TEST = 200, now_test = 0;
	int now_x = x_start,now_y = y_start;
	Vec2 cover = CoverInfo::coverData->coverData[int(type)];
	if (int(cover.x) % 2 == 1)cover.x++;
	if (int(cover.y) % 2 == 1)cover.y++;

	int xy = sqrt(count);
	int xoffset = (x_range - cover.x * xy)/ xy ;
	int yoffset = (y_range - cover.y * xy) / xy ;
	xoffset = xoffset <= 0 ? 3 : xoffset;
	yoffset = yoffset <= 0 ? 3 : yoffset;
	for (int i = 0; i < xy; i++) {
		for (int j = 0; j < xy; j++) {
			now_test = 0;
			
			
			now_x = now_x + cover.x / 2 + rand() % xoffset;
			if (now_x >= x_start + x_range) {
				now_x = x_start;
				now_y = now_y + cover.y / 2 + rand() % yoffset;
			}
			while (!MapController::canBuild(now_x, now_y, cover.x / 2, cover.y / 2)) {
				now_x = now_x + cover.x / 2 + rand() % xoffset;
				if (now_x >= x_start + x_range) {
					now_x = x_start;
					now_y = now_y + cover.y / 2 + rand() % yoffset;
				}
				if (now_test++ > MAX_TEST) {
					now_test = 0;
					while (!MapController::canBuild(now_x, now_y, cover.x / 2, cover.y / 2)) {
						now_y = now_y + cover.y / 2 + rand() % yoffset;
						if (now_y >= y_start + y_range) {
							now_y = y_start;
							return i*xy + j;
						}
						if (now_test++ > MAX_TEST) {
							return i*xy + j;
						}
					}
					break;
				}
			}
			T* obj = new T((Type)type, now_x, now_y, true);

		}
		now_y = now_y + cover.y / 2 + rand() % yoffset;
		if (now_y >= y_start + y_range) {
			now_y = y_start;
			return i*xy;
		}
	}
	for (int i = xy*xy; i < count - xy*xy; i++) {
		now_test = 0;
		now_x = x_start + rand() % x_range;
		now_y = y_start + rand() % y_range;
		while (!MapController::canBuild(now_x, now_y, cover.x / 2, cover.y / 2)) {
			if (now_test++ > MAX_TEST) {
				return xy*xy + i;
			}
		}
		T* obj = new T((Type)type, now_x, now_y, true);
	}
	return count;
}

void MapBuildController::test() {
	MapBuildController::MakeMapRange<Brike, Brike::Type>(Brike::Type::STEEL, 2, 200, 2, 200, 200);
	MapBuildController::MakeMapRange<Flower, Flower::Type>(Flower::Type::FRANGIPANI, 2, 200, 2, 200, 200);
	MapBuildController::MakeMapRange<Tank, Tank::Type>(Tank::Type::STRONG, 2, 200, 2, 200, 2);
}