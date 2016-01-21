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
    scene->addChild(layer, 0, 0);

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

//��ʼ��UI
bool SceneMain::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	//����
	CCSprite* bg = CCSprite::create("images/SceneMain_bg_1.jpg");
	bg->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height / 2));
	this->addChild(bg);

	//����
	CCSprite* sprite = CCSprite::create("images/SceneMain_date.png");
	sprite->setAnchorPoint(ccp(0.5f, 1.0f));
	sprite->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height));
	this->addChild(sprite, 0 ,0);
	CCSize size_date = sprite->getContentSize();

	//����
	CCLabelAtlas* atlas = CCLabelAtlas::create("9", RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 0);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 6.75f, size_date.height * 0.556f));

	//����
	atlas = CCLabelAtlas::create("1", RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 1);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 3.2f, size_date.height * 0.556f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString(), RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 2);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width / 1.96f, size_date.height * 0.526f));

	//�����
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGold())->getCString(), RES_number_style_1, 20, 20, '0');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width * 0.77f, size_date.height * 0.526f));

	//�������
	sprite = CCSprite::create("images/SenceMain_user_attributes.png");
	sprite->setAnchorPoint(ccp(0, 1.0f));
	sprite->setPosition(ccp(vo.x, vo.y + vs.height));
	this->addChild(sprite, 0 ,1);
	CCSize size_attribute = sprite->getContentSize();

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 1);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.625f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 2);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.5f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.375f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 4);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.248f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 5);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.122f));

	//�øн�����
	CCSprite *progress_favor_bg =CCSprite::create(RES_SceneMain_progress_favor_bg);
	this->addChild(progress_favor_bg, 0, 2);
	CCSize size_progress_favor_bg = progress_favor_bg->getContentSize();
	progress_favor_bg->setPosition(ccp(vs.width * 0.5f, size_progress_favor_bg.height * 0.5f));
	CCSprite *progress_favor = CCSprite::create(RES_SceneMain_progress_favor);
	CCProgressTimer *progress_timer = CCProgressTimer::create(progress_favor);
	progress_favor_bg->addChild(progress_timer, 0 ,0);
	progress_timer->setType(kCCProgressTimerTypeBar);
	progress_timer->setAnchorPoint(ccp(0, 0.5f));
	progress_timer->setPosition(ccp(size_progress_favor_bg.width * 0.125f, size_progress_favor_bg.height * 0.74f));
	progress_timer->setMidpoint(ccp(0, 0.5));
	progress_timer->setBarChangeRate(ccp(1, 0));
	progress_timer->setPercentage(user_info->getCurrentFavor());
	CCLabelAtlas *la_favor = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentFavor())->getCString(), RES_number_style_5, 9, 12, '0');
	progress_favor_bg->addChild(la_favor, 0, 1);
	CCSize size_la_favor = la_favor->getContentSize();
	la_favor->setPosition(ccp(size_progress_favor_bg.width * 0.6f, size_progress_favor_bg.height * 0.04f));

	//������
	CCMenuItemImage *item_back = CCMenuItemImage::create(
		RES_btn_back_1_0,
		RES_btn_back_1_1,
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_back = item_back->getContentSize();
	item_back->setPosition(ccp(vs.width - size_item_back.width * 0.5f, vs.height - size_item_back.height * 0.5f));

	//�����
	CCMenuItemImage *item_gift = CCMenuItemImage::create(
		RES_btn_gift_0,
		RES_btn_gift_1,
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_gift = item_gift->getContentSize();
	item_gift->setPosition(ccp(vs.width - size_attribute.width * 0.5f, (vs.height - size_attribute.height) * 0.5f));

	//�����
	CCMenuItemImage *item_express = CCMenuItemImage::create(
		RES_btn_express_0,
		RES_btn_express_1,
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_express = item_express->getContentSize();
	item_express->setPosition(ccp((vs.width + size_progress_favor_bg.width + size_item_express.width) * 0.5f, progress_favor_bg->getPositionY() + size_progress_favor_bg.height * 0.18f));

	//������
	CCMenuItemImage *item_task = CCMenuItemImage::create(
		RES_btn_mission_0,
		RES_btn_mission_1,
		this,
		menu_selector(SceneMain::menuMissionCallback));
	CCSize size_item_task = item_task->getContentSize();
	item_task->setPosition(ccp(vs.width - size_item_task.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height));

	//����ı���
	CCSprite* sp_four_items_bg = CCSprite::create("images/SceneMain_four_items_bg.png");
	this->addChild(sp_four_items_bg);
	CCSize size_sp_four_items_bg = sp_four_items_bg->getContentSize();
	sp_four_items_bg->setPosition(ccp(vs.width - size_sp_four_items_bg.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height * 2.0f - size_sp_four_items_bg.height * 0.5f));
	CCSize size_padding = ccp(size_sp_four_items_bg.width * 0.5f, size_sp_four_items_bg.height * 0.5f);

	//������
	CCMenuItemImage *item_exercise = CCMenuItemImage::create(
		RES_btn_exercise_0,
		RES_btn_exercise_1,
		this,
		menu_selector(SceneMain::menuExerciseCallback));
	CCSize size_item_exercise = item_exercise->getContentSize();
	item_exercise->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//��Ʒ��
	CCMenuItemImage *item_goods = CCMenuItemImage::create(
		RES_btn_goods_0,
		RES_btn_goods_1,
		this,
		menu_selector(SceneMain::menuGoodsCallback));
	CCSize size_item_goods = item_goods->getContentSize();
	item_goods->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//����
	CCMenuItemImage *item_work = CCMenuItemImage::create(
		RES_btn_work_0,
		RES_btn_work_1,
		this,
		menu_selector(SceneMain::menuWorkCallback));
	CCSize size_item_work = item_work->getContentSize();
	item_work->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));

	//��Ϣ��
	CCMenuItemImage *item_rest = CCMenuItemImage::create(
		RES_btn_rest_0,
		RES_btn_rest_1,
		this,
		menu_selector(SceneMain::menuRestCallback));
	CCSize size_item_rest = item_rest->getContentSize();
	item_rest->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));
	
	//�˵�
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
//�����˵���
void SceneMain::menuExerciseCallback(CCObject* pSender)
{
	this->addChild(LayerExercise::create(), 10);
}
//��Ʒ�˵���
void SceneMain::menuGoodsCallback(CCObject* pSender)
{
	this->addChild(LayerGoods::create(), 10);
}
//�򹤲˵���
void SceneMain::menuWorkCallback(CCObject* pSender)
{
	this->addChild(LayerWork::create(), 10);
}
//��Ϣ�˵���
void SceneMain::menuRestCallback(CCObject* pSender)
{
	this->addChild(LayerRest::create(), 10);
}
//�����Լ�
void SceneMain::updateMe()
{
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	int plaid_days = user_info->getPlaidDays();
	int month = 9;
	int day = 1;
	if (plaid_days > 30 && plaid_days <= 61)
	{//10
		month = 10;
		day = plaid_days - 30;
	}
	else if (plaid_days > 61 && plaid_days <= 91)
	{//11
		month = 11;
		day = plaid_days - 61;
	}
	else if (plaid_days > 91 && plaid_days <= 122)
	{//12
		month = 12;
		day = plaid_days - 91;
	}
	else if (plaid_days > 122 && plaid_days <= 153)
	{//1
		month = 1;
		day = plaid_days - 122;
	}
	else if (plaid_days > 153 && plaid_days <= 181)
	{//2
		month = 2;
		day = plaid_days - 153;
	}
	else if (plaid_days > 181 && plaid_days <= 212)
	{//3
		month = 3;
		day = plaid_days - 181;
	}
	else if (plaid_days > 212 && plaid_days <= 242)
	{//4
		month = 4;
		day = plaid_days - 212;
	}
	else if (plaid_days > 242 && plaid_days <= 273)
	{//5
		month = 5;
		day = plaid_days - 242;
	}
	else if (plaid_days > 273 && plaid_days <= 303)
	{//6
		month = 6;
		day = plaid_days - 273;
	}
	else if (plaid_days > 303 && plaid_days <= 334)
	{//7
		month = 7;
		day = plaid_days - 303;
	}
	else if (plaid_days > 334 && plaid_days <= 365)
	{//8
		month = 8;
		day = plaid_days - 334;
	}
	CCNode *node = this->getChildByTag(0);
	//��
	CCLabelAtlas *atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("%d", month)->getCString());
	//��
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", day)->getCString());
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(2));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString());
	//���
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(3));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentGold())->getCString());

	node = this->getChildByTag(1);
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString());
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(2));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString());
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(3));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString());
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(4));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString());
	//����
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(5));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString());

	node = this->getChildByTag(2);
	//�øжȽ�����
	CCProgressTimer *progress_timer = static_cast<CCProgressTimer *>(node->getChildByTag(0));
	progress_timer->setPercentage(user_info->getCurrentFavor());
	//�øж���ֵ
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentFavor())->getCString());
}