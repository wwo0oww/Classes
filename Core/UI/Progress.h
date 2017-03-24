#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Progress 
{
public:
	bool init(const char* background, const char* fillname);
	/*
	the inputs are SpriteFrame Names.
	they should be loaded into SpriteFrameCache before calling this.
	*/
	static Progress* create(const char* background, const char* fill);
	//progress bg ID
	
	void setFill(ProgressTimer* fill) { fill = fill; }
	CCSprite*progress;
	Progress();
	bool initbg(CCSprite*);
	bool initfill(CCSprite*);
	void setProgress(float percentage) {
		if(this->fill != NULL)
		this->fill->setPercentage(percentage);
	}
	static char cbg[50];
	static char cfill[50];
private:
	ProgressTimer* fill;
};