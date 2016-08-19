#pragma once
#define WIN_32
#include"Model\Obj\Obj.h"
namespace EnumData {
	enum LogType
	{
		WORD = 0x0001,
		PER
	};
}
namespace ClassData {
	class ObjData {
	public:
		struct RemoveNodeData {
			std::vector<Obj*>* srcList;
			std::vector<int> deleteList;
		};
		struct RemoveNodeData _RemoveNodeData;
		int _int;
		float _float;
		long _long;
		ObjData(int p) {
			this->_int = p;
		}
		ObjData(float p) {
			this->_float = p;
		}
		ObjData(long p) {
			this->_long = p;
		}
		/*ObjData(RemoveNodeData p) {
			this->_RemoveNodeData = p;
		}*/
	};
}