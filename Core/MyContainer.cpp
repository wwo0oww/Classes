#include"MyContainer.h"
template<class TData>
MyContainer<TData>::MyContainer() {
	this->head = (Node*)malloc(sizeof(Node));
	this->head->last = NULL;
	this->head->next = NULL;
	this->head->useful = false;
}
template<class TData>
void MyContainer<TData>::add_(TData data) {
	
}
template<class TData>
void MyContainer<TData>::delete_() {

}
template<class TData>
void MyContainer<TData>::free_() {

}