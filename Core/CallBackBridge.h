#pragma once
#include"Model\data.h"
typedef void(*FUN_NO_P)();
class CallBackBridge : public CCLayer {

private:
	static CallBackBridge * m_Instance;
public:
	static CallBackBridge* GetInstance();
	void callback(CCNode* sender, void* data);
	void obj_resetmap(CCNode* sender, void* data);
};