#include"SpriteController.h"
#include"GameController.h"
#include"Model\Obj\Obj.h"
#include"View\MainScene.h"
#include"Core\CallBackBridge.h"
#include"Core\UI\Progress.h"
#include"Controller\ObjController.h"
SpriteController* SpriteController::m_Instance = new SpriteController();
 bool SpriteController::bNewSprite = false;
Vec2 SpriteController::spriteScale[MAX_TYPE][4][4];
 MyLock*  SpriteController::spirte_lc = new MyLock();//精灵锁
 MyLock* SpriteController::frame_lc = new MyLock();//frame锁
 map<long, void*> SpriteController::spriteUsedList;//存储在用精灵
 vector<SpriteController::SpritesNode*>  SpriteController::spriteList;//存储可用精灵
 map<std::string, std::map<std::string, CCSpriteFrame*>*>SpriteController::spriteFrameRoute;
//具体存储spriteframe信息，解决多线程无法获取frame问题
//std::map<char*, CCSpriteFrame*>spriteFrame;
//按照关键字存储spriteframe信息，解决多线程无法获取frame问题 
//>>>>>>>>>>>>>>>>>>>>>>>弃用
static map<std::string, std::map<std::string, CCSpriteFrame*>*>spriteFrameRoute;
SpriteController* SpriteController::GetInstance() {
	return m_Instance;
}
SpriteController::~SpriteController() {
	delete spirte_lc;
}
SpriteController::SpriteController() {
	spirte_lc = new MyLock();
}
void SpriteController::freeSprites(void *obj_) {
	Obj*obj = (Obj*)obj_;
	for (int i = 0; i < obj->spritesNode->len; i++) {
		if (i != 2) {
			((CCSprite*)obj->spritesNode->list[i])->setVisible(false);
		}
	}
	obj->spritesNode->used = false;
	((CCSprite*)obj->spritesNode->list[0])->setPosition(-300, -300);
	obj->spritesNode = NULL;
	obj->bShow = false;
	//spirte_lc->Lock();
	map<long, void*>::iterator it = spriteUsedList.find(obj->ID);
	if (it != spriteUsedList.end()) {
		spriteUsedList.erase(it);
	}
}

void SpriteController::resetSprite(void*obj_,bool bscale) {
	
	if (bscale) {
		Obj* obj = (Obj*)obj_;
		auto spritesNode = obj->spritesNode;
		if (obj->anchorPoint.x == -1)
			((CCSprite*)spritesNode->list[0])->setAnchorPoint(GameController::anchorPoint);
		else
			((CCSprite*)spritesNode->list[0])->setAnchorPoint(obj->anchorPoint);
		
		Vec2 pscale, scale;
		
		scale = obj->getSizeScale();
		Vec2 vec = CoverInfo::coverData->getPicList(obj->type, obj->status, obj->fx);
		((CCSprite*)spritesNode->list[1])->setPosition(Vec2(GameController::getScreenUnitSize().width   * (0.5 * vec.x) / scale.y, GameController::getScreenUnitSize().height   * (1.2 * vec.y) / scale.y));
		((CCSprite*)spritesNode->list[3])->setPosition(Vec2(GameController::getScreenUnitSize().height   * (0.5 * vec.x) / scale.x / 2, GameController::getScreenUnitSize().height   * (1.4 * vec.y) / scale.y));
		Vec2 scale_over = PrefixInfo::prefixData->prefixList[obj->type]->scale_over[obj->fx];
		
		pscale = obj->getProgressSizeScale();
		((CCSprite*)spritesNode->list[1])->setScaleY(pscale.y / scale.y);
		((CCSprite*)spritesNode->list[1])->setScaleX(pscale.x / scale.x);
		((CCSprite*)spritesNode->list[0])->setScaleY(scale.y*scale_over.y);
		((CCSprite*)spritesNode->list[0])->setScaleX(scale.x*scale_over.x);
		((Label*)spritesNode->list[3])->setAnchorPoint(Vec2(0.5,0.5));
		
	}
}
void SpriteController::dearBaseSprites(void*obj_) {
	Obj* obj = (Obj*)obj_;
	SpritesNode*spritesNode = obj->spritesNode;
	
	
	Vec2 position = obj->getScreenPosition();

	CCSprite*sprite = (CCSprite*)spritesNode->list[0];
	// 0
	//CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(obj->picName);
	CCSpriteFrame* frame = getSpriteFrame("", obj->picName);
	if(frame != NULL)
	 sprite->setDisplayFrame(frame) ;
	//if (obj->fx != -1 &&(obj->last_fx != obj->fx||obj->last_status != obj->status)) {2017年2月9日21:40:44
	if (obj->last_fx != obj->fx || obj->last_status != obj->status) {
		int rotation;
		obj->last_fx = obj->fx;
		obj->last_status = obj->status;
		if (obj->status&Status::ATTACK) {

			rotation = PrefixInfo::prefixData->prefixList[obj->type]->arotation[obj->fx];
		}
		else if (obj->status&Status::MOVE) {
			rotation = PrefixInfo::prefixData->prefixList[obj->type]->mrotation[obj->fx];
		}
		else if (obj->status&Status::STAND) {
			rotation = PrefixInfo::prefixData->prefixList[obj->type]->srotation[obj->fx];
		}
		else {
			rotation = 0;
		}
		sprite->setRotation(rotation);
	}
	sprite->setPosition(position);

	
	// 1
	//sprite = spritesNode->list[1];
	/*obj->progress->progress = (CCSprite*)spritesNode->list[1];*/
	
	
	// 2
	if(obj->InitBShowName())
	obj->buildName();
	resetSprite(obj,true);
	obj->InitBShowProgress();
}
void SpriteController::changeBaseSprites(void*obj_) {
	Obj* obj = (Obj*)obj_;
	if (obj->spritesNode == NULL)return;
	CCSprite*sprite = (CCSprite*)obj->spritesNode->list[0];
	if (obj->bPicChanage) {
		obj->bPicChanage = false;
		CCSpriteFrame* frame = getSpriteFrame("", obj->picName);
		if (frame != NULL)
			sprite->setDisplayFrame(frame);
		else
			int i = 0;
		//2017年2月9日21:40 : 44 != -1
		if (obj->last_fx != obj->fx || obj->last_status != obj->status) {
			obj->last_fx = obj->fx;
			obj->last_status = obj->status;
			int rotation;
			if (obj->status&Status::ATTACK) {

				rotation = PrefixInfo::prefixData->prefixList[obj->type]->arotation[obj->fx];
			}
			else if (obj->status&Status::MOVE) {
				rotation = PrefixInfo::prefixData->prefixList[obj->type]->mrotation[obj->fx];
			}
			else if (obj->status&Status::STAND) {
				rotation = PrefixInfo::prefixData->prefixList[obj->type]->srotation[obj->fx];
			}
			else {
				rotation = 0;
			}
			
			sprite->setRotation(rotation);
		}
	}
	

	if (GameController::bSreeenChange||obj->bsclae_change) {
		Vec2 vec2 = obj->getScreenPosition();
		resetSprite(obj,  obj->bsclae_change || GameController::bSreeenScale);
		//其他处理放到了obj类里了
		if (!obj->bMove||!(obj->status & Status::MOVE)) {
			if (obj != ObjController::PlayerObj) {
				sprite->setPosition(vec2);
				sprite->setZOrder(-(obj->GetZOrderY() - GameController::zero_y));
			}
		}

		obj->bsclae_change = false;
		
}
#ifdef ACTION
	Vec2 vec2 = obj->getScreenPosition();
	if (GameController::bSreeenChange || obj->lastX != vec2.x || obj->lastY != vec2.y) {
		if (GameController::last_screenSizeW!= GameController::screenSizeW||
			GameController::last_screenSizeH != GameController::screenSizeH) {
			resetSprite(obj);
		}
		if (GameController::bSreeenChange&&!obj->bMove) {
			sprite->setPosition(vec2);
		}
		else {
			//sprite->setPosition(vec2);
			CCFiniteTimeAction *actionMove = CCMoveTo::create(GameController::timeInterval * obj->moveNum, vec2);
			sprite->runAction(CCSequence::create(actionMove, NULL, NULL));
		}
		obj->lastX = vec2.x;
		obj->lastY = vec2.y;
		sprite->setZOrder(-(obj->GetZOrderY() - GameController::zero_y));
	}
#endif
}

void SpriteController::changeSpritesPic(void * obj_) {
	changeBaseSprites(obj_);
}

void SpriteController::createSprites(void *obj_) {
	Obj* obj = (Obj*)obj_;
	//if (obj->progress == NULL)obj->progress = new Progress();
	//<!--从存储列表中拿出一个sprite，如果没有空闲的，新建一个sprite 并拿出-->
	std::vector <SpritesNode*>::iterator it = spriteList.begin();
	while (it != spriteList.end()) {
		if (!(*it)->used&&(*it)->len == obj->sprites_len) {
			break;
		}
		it++;
	}
	SpritesNode*spritesNode;
	if (it == spriteList.end()) {
		spritesNode = (SpritesNode*)malloc(sizeof(SpritesNode));
		spritesNode->len = obj->sprites_len;
		spritesNode->used = true;
		//0 self 1 progress bg 2 progress fill
		for (int i = 0; i < 3; i++) {
			CCSprite*sprite = CCSprite::create() ;
			spritesNode->list[i] = sprite;
		}
		obj->scene->addChild((CCSprite*)spritesNode->list[0], -(obj->GetZOrderY() - GameController::zero_y));
		
		((CCSprite*)spritesNode->list[0])->addChild((CCSprite*)spritesNode->list[1]);
		
		
		spritesNode->list[3] = Label::createWithSystemFont("name", "Arial", GameController::wUnit / 2);
		spritesNode->list[4] = new Progress();
		Progress * progress = (Progress*)spritesNode->list[4];
		progress->initbg((CCSprite*)spritesNode->list[1]);
		progress->initfill((CCSprite*)spritesNode->list[2]);
		obj->progress = progress;
		((CCSprite*)spritesNode->list[0])->addChild((Label*)spritesNode->list[3]);
		spriteList.push_back(spritesNode);
	}
	else {
		spritesNode = *it;
		spritesNode->used = true;
		obj->progress = (Progress*)(*it)->list[4];
		((CCSprite*)(*it)->list[0])->setVisible(true);
		((CCSprite*)(*it)->list[0])->setZOrder(-(obj->GetZOrderY() - GameController::zero_y));
	}
	obj->spritesNode = spritesNode;
	dearBaseSprites(obj);
}

void SpriteController::getOneTag(void*obj_) {

	bNewSprite = true;
	Obj * obj = ((Obj*)obj_);
	obj->bUI = true;
	spriteUsedList.insert(pair<long,void*>(obj->ID,obj));
}



CCSpriteFrame* SpriteController::getSpriteFrame(string type,string picName) {
#ifdef DEBUG
	CCLOG("getSpriteFrame start");
#endif
	frame_lc->Lock();
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picName);
	frame_lc->UnLock();
	return frame;
	map<string,map<string, CCSpriteFrame*>*>::iterator it =  spriteFrameRoute.find(type);
	if(it == spriteFrameRoute.end()){
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picName);
		return frame;
	}
	map<string, CCSpriteFrame*>::iterator it_ = it->second->find(picName);
	if (it_ == it->second->end()) {
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picName);
		return frame;
	} 
#ifdef DEBUG
	CCLOG("getSpriteFrame end");
#endif
	return it_->second;
}

void SpriteController::initSpriteFrame(SpriteFrameInfo*spriteFrameInfo) {
	string key = spriteFrameInfo->type;
	//遍历所有的 node节点 ，存入 map frame信息
	while (spriteFrameInfo->next != NULL) {
		//寻找 obj对应的map 如 tank
		map<string, map<string, CCSpriteFrame*>*>::iterator it = spriteFrameRoute.find(key);

		map<string, CCSpriteFrame*>*map_;
		bool inmap = false;//是否找到
						   //找到 obj 的map
		if (it != spriteFrameRoute.end()) {
			map_ = it->second;//拿出 map信息
			inmap = true;
		}
		else {
			map_ = new map<string, CCSpriteFrame*>;
		}
		//存入新的 frame信息
		for (int i = 0; i < spriteFrameInfo->total; i++) {
			char*tmpc = new char[MAX_PREFIX + 15];
			sprintf(tmpc, "%s (%d).png", spriteFrameInfo->prefix, i+1);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tmpc);
			map_->insert(pair<string, CCSpriteFrame*>(tmpc, frame));
		}
		//没找到 将新信息 插入 route
		if (!inmap) {
			spriteFrameRoute.insert(pair<string, map<string, CCSpriteFrame*>*>(key, map_));
		}
		//位移node
		SpriteFrameInfo * tmp = spriteFrameInfo;
		spriteFrameInfo = spriteFrameInfo->next;
		free(tmp);
	}
}