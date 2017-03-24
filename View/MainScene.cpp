#pragma once
#include"MainScene.h"
#include "../Core/AppMacros.h"
#include "ui\UIButton.h"
#include"Controller\MainSceneController.h"

USING_NS_CC;
using namespace ui;

Scene* MainScene::scene()
{
	// 'scene' is an autorelease object
	MainSceneController::nowScene = Scene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	MainSceneController::nowScene->addChild(layer);

	// return the scene
	return MainSceneController::nowScene;
}
// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	//excute
	MainSceneController::nowScene->schedule(SEL_SCHEDULE(&MainSceneController::afterInit), 0.01f);
	return true;
}
void MainScene::update(float delta) {
	//MainSceneController::GetInstance()->RunGame(1.0);
	int i = 0;
}

