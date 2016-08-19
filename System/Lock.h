#pragma once
#include<stdio.h>
#include"Model\data.h"
#include<Windows.h>
class MyLock {
private:
#ifdef WIN_32
	CRITICAL_SECTION lock;
#endif // WIN_32
public:
	MyLock();
	void Init();
	void Lock();
	void UnLock();
	void Delete();
	~MyLock();
};
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
MyLock::MyLock(){
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
