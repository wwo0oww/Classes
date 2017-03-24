#pragma once
#include"Model\data.h"

class MainScene : public cocos2d::Layer {
private:
	
public:
	Label* label;
	std::string lab_str;
	std::mutex lab_str_cs;
	virtual bool init() override;
	static cocos2d::Scene* scene();
	virtual void update(float delta) override;
	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

};