#pragma once
#include"Core\Controller.h"
#include"Model\Obj\Building\Brike\Brike.h"


class MapBuildController : public Controller {
private:
	static MapBuildController * m_Instance;
public:
	static MapBuildController* GetInstance();
	
	//参数
	//要放置的类型
	//x_start 开始横坐标 x_range 范围
	// y_start 开始横坐标 y_range 范围
	//count 数量
	//<T> 要放置的类型
	//返回值 放置成功的数量
	template<class T, class Type>
	static int MakeMapRange(Type type,int x_start, int x_range, int y_start, int y_range,int count);
	
	static void test();
	enum class CODE {
		THREAD_OVER,
	};
};