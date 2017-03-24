#include"CallBackBridge.h"
#include"Model\Obj\Obj.h"
CallBackBridge* CallBackBridge::m_Instance = new CallBackBridge();
CallBackBridge* CallBackBridge::GetInstance() {
	return m_Instance;
}
void CallBackBridge::callback(CCNode* sender, void* data) {
	FUN_NO_P p = (FUN_NO_P)data;	
}
void CallBackBridge::obj_resetmap(CCNode* sender, void* data) {
	((Obj*)data)->resetMove();
}