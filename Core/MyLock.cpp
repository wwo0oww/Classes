#include"MyLock.h"
void MyLock::Init() {
#ifdef WIN_32
	InitializeCriticalSection(&this->lock);
#else
#ifdef ANDROID
	this->lock = new mutex();
#endif
#endif
}
void MyLock::Lock() {
#ifdef WIN_32
	EnterCriticalSection(&this->lock);
#else
#ifdef ANDROID
	this->lock->lock();
#endif
#endif
}
MyLock::MyLock() {
	this->Init();
}
void MyLock::UnLock() {
#ifdef WIN_32
	LeaveCriticalSection(&this->lock);
#else
#ifdef ANDROID
	this->lock->unlock();
#endif
#endif
}
void MyLock::Delete() {
#ifdef WIN_32
	DeleteCriticalSection(&this->lock);
#else
#ifdef ANDROID
	delete this->lock;
#endif
#endif
}
MyLock::~MyLock() {
	this->Delete();
}
