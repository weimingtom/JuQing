#include "SceneAction.h"
#include "SceneMain.h"
#include "LayerDialog.h"
#include "UserInfo.h"
#include "LayerHint.h"

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

	setKeypadEnabled(true);
    
    return true;
}

//初始化UI
bool SceneAction::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	//背景
	CCSprite* bg = CCSprite::create("images/SceneAction_bg.jpg");
	bg->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height / 2));
	this->addChild(bg, 0);

	//新的开始项
	CCMenuItemImage *item_new = CCMenuItemImage::create(
		"images/SceneAction_new_0.png",
		"images/SceneAction_new_1.png",
		this,
		menu_selector(SceneAction::menuNewCallback));
	CCSize size = item_new->getContentSize();
	item_new->setPosition(ccp(vs.width * 0.5f - size.width * 1.6f, vs.height * 0.3f));

	//旧的回忆项
	CCMenuItemImage *item_old = CCMenuItemImage::create(
		"images/SceneAction_old_0.png",
		"images/SceneAction_old_1.png",
		this,
		menu_selector(SceneAction::menuOldCallback));
	item_old->setPosition(ccp(vs.width * 0.5f, vs.height * 0.3f));

	//退出项
	CCMenuItemImage *item_close = CCMenuItemImage::create(
		"images/SceneAction_end_0.png",
		"images/SceneAction_end_1.png",
		this,
		menu_selector(SceneAction::menuCloseCallback));
	item_close->setPosition(ccp(vs.width * 0.5f + size.width * 1.6f, vs.height * 0.3f));


	CCLabelTTF* lbl = CCLabelTTF::create("new", "fonts/ttfs/MicrosoftYaHei.ttf", 36);
	//设置项
	CCMenuItemImage *item_set = CCMenuItemImage::create(
		"images/btn_common_1_0.png",
		"images/btn_common_1_1.png",
		this,
		menu_selector(SceneAction::menuSetCallback));
	item_set->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f + size.height / 2.0f + 5));

	lbl = CCLabelTTF::create("set", "fonts/ttfs/MicrosoftYaHei.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_set->addChild(lbl, 1);

	//帮助项
	CCMenuItemImage *item_help = CCMenuItemImage::create(
		"images/btn_common_1_0.png",
		"images/btn_common_1_1.png",
		this,
		menu_selector(SceneAction::menuHelpCallback));
	item_help->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f - size.height / 2.0f - 5.0f));

	lbl = CCLabelTTF::create("help", "fonts/ttfs/MicrosoftYaHei.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_help->addChild(lbl, 1);

	//关于项
	CCMenuItemImage *item_about = CCMenuItemImage::create(
		"images/btn_common_1_0.png",
		"images/btn_common_1_1.png",
		this,
		menu_selector(SceneAction::menuAboutCallback));
	item_about->setPosition(ccp(vs.width / 2.0f, vs.height / 2.0f - size.height * 3.0f / 2.0f - 15.0f));

	lbl = CCLabelTTF::create("about", "fonts/ttfs/MicrosoftYaHei.ttf", 36);
	lbl->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	item_about->addChild(lbl, 1);

	CCMenu* pMenu = CCMenu::create(item_new, item_old, item_close, /*item_set, item_help, item_about,*/ NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/*if (user_info->getCurrentSectionId() <= 1)
	{
		item_old->setEnabled(false);
		item_old->setColor(ccc3(128,128,128));
	}*/

	return true;
}


//新的开始
void SceneAction::menuNewCallback(CCObject* pSender)
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile();
	TopwoData* td = Topwo::getInstance()->getTopwoData();
	UserInfo* user_info = td->getUserInfo();
	DataSection *data_section = td->getDataSectionFromArray(1);
	this->addChild(LayerDialog::createWith(data_section->getBeginId(), data_section->getEndId(), this, callfunc_selector(SceneAction::callbackDialogOver)), 10);
	
	user_info->resetData();
}
//旧的回忆
void SceneAction::menuOldCallback(CCObject* pSender)
{
	Topwo::getInstance()->getTopwoData()->readData();
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
	Topwo::getInstance()->getTopwoPlatform()->callShowExitDialog();
}

void SceneAction::keyBackClicked()
{
	Topwo::getInstance()->getTopwoPlatform()->callShowExitDialog();
}

//对话回调
void SceneAction::callbackDialogOver()
{
	CCDirector::sharedDirector()->replaceScene(SceneMain::creatScene());
}