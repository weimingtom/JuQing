#include "SceneMain.h"
#include "SceneAction.h"

CCScene* SceneMain::creatScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SceneMain *layer = SceneMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	initUI();
    
    return true;
}

//初始化UI
bool SceneMain::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	//背景
	CCSprite* bg = CCSprite::create("SceneMain_bg_1.jpg");
	bg->setPosition(ccp(vs.width / 2 + vo.x, vs.height / 2 + vo.y));
	this->addChild(bg, 0);

	//返回项
	CCMenuItemImage *item_back = CCMenuItemImage::create(
		"btn_back_0.png",
		"btn_back_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_back = item_back->getContentSize();
	item_back->setPosition(ccp(vs.width - size_item_back.width / 2.0f, vs.height - size_item_back.height / 2.0f));

	CCMenu* menu = CCMenu::create(item_back, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);

	return true;
}

void SceneMain::menuBackCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, SceneAction::creatScene()));
}

void SceneMain::menuBeginCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}