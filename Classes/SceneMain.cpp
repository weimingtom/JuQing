#include "SceneMain.h"
#include "SceneAction.h"
#include "LayerMission.h"
#include "LayerExercise.h"
#include "LayerGoods.h"
#include "LayerWork.h"
#include "LayerRest.h"

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

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	//背景
	CCSprite* bg = CCSprite::create("images/SceneMain_bg_1.jpg");
	bg->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height / 2));
	this->addChild(bg);

	//日期
	CCSprite* sprite = CCSprite::create("images/SceneMain_date.png");
	sprite->setAnchorPoint(ccp(0.5f, 1.0f));
	sprite->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height));
	this->addChild(sprite);
	CCSize size_date = sprite->getContentSize();

	//月数
	CCLabelAtlas* atlas = CCLabelAtlas::create("9", RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 0);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 6.75f, size_date.height * 0.556f));

	//日数
	atlas = CCLabelAtlas::create("1", RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 1);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 3.2f, size_date.height * 0.556f));

	//体力数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString(), RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 2);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width / 1.96f, size_date.height * 0.526f));

	//金币数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGold())->getCString(), RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width * 0.77f, size_date.height * 0.526f));

	//玩家属性
	sprite = CCSprite::create("images/SenceMain_user_attributes.png");
	sprite->setAnchorPoint(ccp(0, 1.0f));
	sprite->setPosition(ccp(vo.x, vo.y + vs.height));
	this->addChild(sprite);
	CCSize size_attribute = sprite->getContentSize();

	//体魄数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.625f));

	//魅力数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.5f));

	//智力数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.375f));

	//情商数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.248f));

	//感性数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.122f));

	//返回项
	CCMenuItemImage *item_back = CCMenuItemImage::create(
		RES_btn_back_1_0,
		RES_btn_back_1_1,
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_back = item_back->getContentSize();
	item_back->setPosition(ccp(vs.width - size_item_back.width * 0.5f, vs.height - size_item_back.height * 0.5f));

	//礼包项
	CCMenuItemImage *item_gift = CCMenuItemImage::create(
		"images/btn_gift_0.png",
		"images/btn_gift_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_gift = item_gift->getContentSize();
	item_gift->setPosition(ccp(size_attribute.width * 0.5f, (vs.height - size_attribute.height) * 0.5f));

	//表白项
	CCMenuItemImage *item_express = CCMenuItemImage::create(
		"images/btn_express_0.png",
		"images/btn_express_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_express = item_express->getContentSize();
	item_express->setPosition(ccp(vs.width * 0.5f, size_item_express.height * 0.5f));

	//任务项
	CCMenuItemImage *item_task = CCMenuItemImage::create(
		"images/btn_mission_0.png",
		"images/btn_mission_1.png",
		this,
		menu_selector(SceneMain::menuMissionCallback));
	CCSize size_item_task = item_task->getContentSize();
	item_task->setPosition(ccp(vs.width - size_item_task.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height));

	//四项的背景
	CCSprite* sp_four_items_bg = CCSprite::create("images/SceneMain_four_items_bg.png");
	this->addChild(sp_four_items_bg);
	CCSize size_sp_four_items_bg = sp_four_items_bg->getContentSize();
	sp_four_items_bg->setPosition(ccp(vs.width - size_sp_four_items_bg.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height * 2.0f - size_sp_four_items_bg.height * 0.5f));
	CCSize size_padding = ccp(size_sp_four_items_bg.width * 0.5f, size_sp_four_items_bg.height * 0.5f);

	//锻炼项
	CCMenuItemImage *item_exercise = CCMenuItemImage::create(
		"images/btn_exercise_0.png",
		"images/btn_exercise_1.png",
		this,
		menu_selector(SceneMain::menuExerciseCallback));
	CCSize size_item_exercise = item_exercise->getContentSize();
	item_exercise->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//物品项
	CCMenuItemImage *item_goods = CCMenuItemImage::create(
		"images/btn_goods_0.png",
		"images/btn_goods_1.png",
		this,
		menu_selector(SceneMain::menuGoodsCallback));
	CCSize size_item_goods = item_goods->getContentSize();
	item_goods->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//打工项
	CCMenuItemImage *item_work = CCMenuItemImage::create(
		"images/btn_work_0.png",
		"images/btn_work_1.png",
		this,
		menu_selector(SceneMain::menuWorkCallback));
	CCSize size_item_work = item_work->getContentSize();
	item_work->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));

	//休息项
	CCMenuItemImage *item_rest = CCMenuItemImage::create(
		"images/btn_rest_0.png",
		"images/btn_rest_1.png",
		this,
		menu_selector(SceneMain::menuRestCallback));
	CCSize size_item_rest = item_rest->getContentSize();
	item_rest->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));
	
	//菜单
	CCMenu* menu = CCMenu::create(item_back, item_rest, item_goods, item_express, item_gift, item_exercise, item_work, item_task, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);

	return true;
}

void SceneMain::menuBackCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, SceneAction::creatScene()));
}

void SceneMain::menuMissionCallback(CCObject* pSender)
{
	this->addChild(LayerMission::create(), 10);
}
//锻炼菜单项
void SceneMain::menuExerciseCallback(CCObject* pSender)
{
	this->addChild(LayerExercise::create(), 10);
}
//物品菜单项
void SceneMain::menuGoodsCallback(CCObject* pSender)
{
	this->addChild(LayerGoods::create(), 10);
}
//打工菜单项
void SceneMain::menuWorkCallback(CCObject* pSender)
{
	this->addChild(LayerWork::create(), 10);
}
//休息菜单项
void SceneMain::menuRestCallback(CCObject* pSender)
{
	this->addChild(LayerRest::create(), 10);
}