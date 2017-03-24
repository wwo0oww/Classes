#pragma once
#include"Model\Obj\Obj.h"
template<class TData>
class MyContainer{
public:
	struct Node {
		bool useful;
		TData data;
		Node*last;
		Node*next;
	};
private:
	Node*head;
	Node*tail;
public:
	MyContainer();
	void add_(TData data);
	void delete_();
	void free_();
};