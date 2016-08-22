#include"MyLock.h"
void MyLock::Init() {
#ifdef WIN_32
	InitializeCriticalSection(&this->lock);
#endif
}
void MyLock::Lock() {
#ifdef WIN_32
	EnterCriticalSection(&this->lock);
#endif
}
MyLock::MyLock() {
	this->Init();
}
void MyLock::UnLock() {
#ifdef WIN_32
	LeaveCriticalSection(&this->lock);
#endif
}
void MyLock::Delete() {
#ifdef WIN_32
	DeleteCriticalSection(&this->lock);
#endif
}
MyLock::~MyLock() {
	this->Delete();
}
