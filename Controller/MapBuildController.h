#pragma once
#include"Core\Controller.h"
#include"Model\Obj\Building\Brike\Brike.h"


class MapBuildController : public Controller {
private:
	static MapBuildController * m_Instance;
public:
	static MapBuildController* GetInstance();
	
	//����
	//Ҫ���õ�����
	//x_start ��ʼ������ x_range ��Χ
	// y_start ��ʼ������ y_range ��Χ
	//count ����
	//<T> Ҫ���õ�����
	//����ֵ ���óɹ�������
	template<class T, class Type>
	static int MakeMapRange(Type type,int x_start, int x_range, int y_start, int y_range,int count);
	
	static void test();
	enum class CODE {
		THREAD_OVER,
	};
};