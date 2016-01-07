#include "SceneAction.h"
#include "SceneMain.h"
#include "LayerDialog.h"

CCScene* SceneAction::creatScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SceneAction *layer = SceneAction::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneAction::init()
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
bool SceneAction::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	//背景
	CCSprite* bg = CCSprite::create("images/SceneAction_bg.jpg");
	bg->setPosition(ccp(vs.width / 2 + vo.x, vs.height / 2 + vo.y));
	this->addChild(bg, 0);

	//新的开始项
	CCMenuItemImage *item_new = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuNewCallback));
	CCSize size = item_new->getContentSize();
	item_new->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f + size.height * 5.0f / 2.0f + 25.0f));

	CCLabelTTF* lbl = CCLabelTTF::create("begin", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_new->addChild(lbl, 1);

	//旧的回忆项
	CCMenuItemImage *item_old = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuOldCallback));
	item_old->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f + size.height * 3.0f / 2.0f + 15.0f));

	lbl = CCLabelTTF::create("old", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_old->addChild(lbl, 1);

	//设置项
	CCMenuItemImage *item_set = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuSetCallback));
	item_set->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f + size.height / 2.0f + 5));

	lbl = CCLabelTTF::create("set", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_set->addChild(lbl, 1);

	//帮助项
	CCMenuItemImage *item_help = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuHelpCallback));
	item_help->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f - size.height / 2.0f - 5.0f));

	lbl = CCLabelTTF::create("help", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_help->addChild(lbl, 1);

	//关于项
	CCMenuItemImage *item_about = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuAboutCallback));
	item_about->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f - size.height * 3.0f / 2.0f - 15.0f));

	lbl = CCLabelTTF::create("about", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_about->addChild(lbl, 1);

	//退出项
	CCMenuItemImage *item_close = CCMenuItemImage::create(
		"images/btn_up.png",
		"images/btn_down.png",
		this,
		menu_selector(SceneAction::menuCloseCallback));

	item_close->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f - size.height * 5.0f / 2.0f - 25.0f));

	lbl = CCLabelTTF::create("close", "fonts/ttfs/arial.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_close->addChild(lbl, 1);

	CCMenu* pMenu = CCMenu::create(item_new, item_old, item_set, item_help, item_about, item_close, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}


//新的开始
void SceneAction::menuNewCallback(CCObject* pSender)
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile();
	TopwoData* td = Topwo::getInstance()->getTopwoData();
	int chapter_id = td->getCurrentChapterId();
	int begin_id = td->getUserInfo()->getDataChapterFromArray(chapter_id)->getBeginId();
	int end_id = td->getUserInfo()->getDataChapterFromArray(chapter_id)->getEndId();
	this->addChild(LayerDialog::createWith(begin_id, end_id), 10);
	td->setCurrentChapterId(chapter_id + 1);
}
//旧的回忆
void SceneAction::menuOldCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, SceneMain::creatScene()));
}
//设置
void SceneAction::menuSetCallback(CCObject* pSender)
{
}
//帮助
void SceneAction::menuHelpCallback(CCObject* pSender)
{
}
//关于
void SceneAction::menuAboutCallback(CCObject* pSender)
{
}
//退出
void SceneAction::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}