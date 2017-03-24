#include"TData.h"
#include"malloc.h"
//暂时用不到，就不写了
template<class T>
TData<T>::TData( Type type) {
	
	this->type = type;
	switch (this->type)
	{
	case Type::DICHOTOMY:
		this->DICHOTOMY_head = NULL;
		break;
	default:
		break;
	}
}
// 0 成功 1 存在并覆盖
template<class T>
int TData<T>::DICHOTOMY_add(int ID, T data) {
	if (this->DICHOTOMY_head == NULL) {
		this->DICHOTOMY_head = (Node*)malloc(sizeof(Node));
		this->DICHOTOMY_head->next = NULL;
		this->DICHOTOMY_head->data = data;
		this->DICHOTOMY_head->ID = ID;
		return 0;
	}
	Node* p = this->DICHOTOMY_head;
	while (p != NULL) {
		if (p->ID == ID) {
			p->data == data;
			return 1;
		}
		if (p->next == NULL) {
			break;
		}
		p = p->next;
	}
	p->next = (Node*)malloc(sizeof(Node));
	p->next->next = NULL;
	p->next->data = data;
	p->next->ID = ID;
}
template<class T>
T TData<T>::DICHOTOMY_get(int ID) {

}
template<class T>
int TData<T>::Add(int ID, T data) {
	switch (this->type)
	{
	case Type::DICHOTOMY:
		return this->DICHOTOMY_add();
		break;
	default:
		break;
	}
}
template<class T>
T TData<T>::get(int ID) {
	switch (this->type)
	{
	case Type::DICHOTOMY:
		return this->DICHOTOMY_get();
		break;
	default:
		break;
	}
}