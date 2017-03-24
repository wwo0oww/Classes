#pragma once
#ifndef NULL
#define NULL 0
#endif // !NULL

template<class T>
class TData {
public:
	struct Node {
		Node*next;
		int ID;
		T data;
	};
private:
	//参数:ID 唯一id
	//	   data 数据
	int DICHOTOMY_add(int ID, T data);
	T DICHOTOMY_get(int ID);
	
	Node*DICHOTOMY_head;
public:
	
	int length;
	enum Type {
		DICHOTOMY,
	};
	TData(Type type);
	Type type;
	
	int Add(int ID, T data);
	T get(int ID);
};
//class Test {
//public:
//	int i;
//};
//static TData<Test*>* test = new TData<Test*>(TData<Test*>::Type::DICHOTOMY);