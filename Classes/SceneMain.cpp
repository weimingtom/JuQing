#include "SceneMain.h"
#include "SceneAction.h"
#include "LayerMission.h"
#include "LayerExercise.h"
#include "LayerGoods.h"
#include "LayerWork.h"
#include "LayerRest.h"
#include "LayerDialog.h"
#include "LayerHint.h"

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

	Topwo::getInstance()->getTopwoAudio()->playMusic(1);
    
    return true;
}

//初始化UI
bool SceneMain::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	//背景
	CCSprite* bg = CCSprite::create("images/BG_1.jpg");
	bg->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height / 2));
	this->addChild(bg);

	//日期
	CCSprite* sprite = CCSprite::create("images/SceneMain_date.png");
	sprite->setAnchorPoint(ccp(0.5f, 1.0f));
	sprite->setPosition(ccp(vo.x + vs.width / 2, vo.y + vs.height));
	this->addChild(sprite, 0 ,0);
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
	this->addChild(sprite, 0 ,1);
	CCSize size_attribute = sprite->getContentSize();

	//体魄数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 1);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.625f));
	//加成
	CCSize size_atlas = atlas->getContentSize();
	CCLabelAtlas *atlas_bonus = CCLabelAtlas::create(CCString::createWithFormat("(+%d)", user_info->getBonusById(1))->getCString(), RES_number_style_3, 10, 15, '(');
	atlas->addChild(atlas_bonus, 0, 0);
	atlas_bonus->setPosition(ccp(size_atlas.width, 0));

	//魅力数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 2);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.5f));
	//加成
	size_atlas = atlas->getContentSize();
	atlas_bonus = CCLabelAtlas::create(CCString::createWithFormat("(+%d)", user_info->getBonusById(2))->getCString(), RES_number_style_3, 10, 15, '(');
	atlas->addChild(atlas_bonus, 0, 0);
	atlas_bonus->setPosition(ccp(size_atlas.width, 0));

	//智力数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.375f));
	//加成
	size_atlas = atlas->getContentSize();
	atlas_bonus = CCLabelAtlas::create(CCString::createWithFormat("(+%d)", user_info->getBonusById(3))->getCString(), RES_number_style_3, 10, 15, '(');
	atlas->addChild(atlas_bonus, 0, 0);
	atlas_bonus->setPosition(ccp(size_atlas.width, 0));

	//情商数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 4);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.248f));
	//加成
	size_atlas = atlas->getContentSize();
	atlas_bonus = CCLabelAtlas::create(CCString::createWithFormat("(+%d)", user_info->getBonusById(4))->getCString(), RES_number_style_3, 10, 15, '(');
	atlas->addChild(atlas_bonus, 0, 0);
	atlas_bonus->setPosition(ccp(size_atlas.width, 0));

	//感性数
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString(), RES_number_style_2, 9, 15, '+');
	sprite->addChild(atlas, 0, 5);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.122f));
	//加成
	size_atlas = atlas->getContentSize();
	atlas_bonus = CCLabelAtlas::create(CCString::createWithFormat("(+%d)", user_info->getBonusById(5))->getCString(), RES_number_style_3, 10, 15, '(');
	atlas->addChild(atlas_bonus, 0, 0);
	atlas_bonus->setPosition(ccp(size_atlas.width, 0));

	//好感进度条
	CCSprite *progress_favor_bg =CCSprite::create(RES_SceneMain_progress_favor_bg);
	this->addChild(progress_favor_bg, 0, 2);
	CCSize size_progress_favor_bg = progress_favor_bg->getContentSize();
	progress_favor_bg->setPosition(ccp(vs.width * 0.5f, size_progress_favor_bg.height * 0.5f));
	CCSprite *progress_favor = CCSprite::create(RES_SceneMain_progress_favor);
	CCProgressTimer *progress_timer = CCProgressTimer::create(progress_favor);
	progress_favor_bg->addChild(progress_timer, 0 ,0);
	progress_timer->setType(kCCProgressTimerTypeBar);
	progress_timer->setAnchorPoint(ccp(0, 0.5f));
	progress_timer->setPosition(ccp(size_progress_favor_bg.width * 0.125f, size_progress_favor_bg.height * 0.73f));
	progress_timer->setMidpoint(ccp(0, 0.5));
	progress_timer->setBarChangeRate(ccp(1, 0));
	progress_timer->setPercentage(user_info->getCurrentFavor());
	CCLabelAtlas *la_favor = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentFavor())->getCString(), RES_number_style_5, 9, 12, '0');
	progress_favor_bg->addChild(la_favor, 0, 1);
	CCSize size_la_favor = la_favor->getContentSize();
	la_favor->setPosition(ccp(size_progress_favor_bg.width * 0.6f, size_progress_favor_bg.height * 0.04f));

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
		RES_btn_gift_0,
		RES_btn_gift_1,
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_gift = item_gift->getContentSize();
	item_gift->setPosition(ccp(vs.width - size_attribute.width * 0.5f, (vs.height - size_attribute.height) * 0.5f));

	//表白项
	CCMenuItemImage *item_express = CCMenuItemImage::create(
		RES_btn_express_0,
		RES_btn_express_1,
		this,
		menu_selector(SceneMain::menuExpressCallback));
	CCSize size_item_express = item_express->getContentSize();
	item_express->setPosition(ccp((vs.width + size_progress_favor_bg.width + size_item_express.width) * 0.5f, progress_favor_bg->getPositionY() + size_progress_favor_bg.height * 0.18f));

	//任务项
	CCMenuItemImage *item_task = CCMenuItemImage::create(
		RES_btn_mission_0,
		RES_btn_mission_1,
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
		RES_btn_exercise_0,
		RES_btn_exercise_1,
		this,
		menu_selector(SceneMain::menuExerciseCallback));
	CCSize size_item_exercise = item_exercise->getContentSize();
	item_exercise->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//物品项
	CCMenuItemImage *item_goods = CCMenuItemImage::create(
		RES_btn_goods_0,
		RES_btn_goods_1,
		this,
		menu_selector(SceneMain::menuGoodsCallback));
	CCSize size_item_goods = item_goods->getContentSize();
	item_goods->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() + size_padding.height * 0.5f));

	//打工项
	CCMenuItemImage *item_work = CCMenuItemImage::create(
		RES_btn_work_0,
		RES_btn_work_1,
		this,
		menu_selector(SceneMain::menuWorkCallback));
	CCSize size_item_work = item_work->getContentSize();
	item_work->setPosition(ccp(sp_four_items_bg->getPositionX() - size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));

	//休息项
	CCMenuItemImage *item_rest = CCMenuItemImage::create(
		RES_btn_rest_0,
		RES_btn_rest_1,
		this,
		menu_selector(SceneMain::menuRestCallback));
	CCSize size_item_rest = item_rest->getContentSize();
	item_rest->setPosition(ccp(sp_four_items_bg->getPositionX() + size_padding.width * 0.5f, sp_four_items_bg->getPositionY() - size_padding.height * 0.5f));
	
	//菜单
	CCMenu* menu = CCMenu::create(item_back, item_rest, item_goods, item_express, /*item_gift,*/ item_exercise, item_work, item_task, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);

	updateMe();

	return true;
}

void SceneMain::menuBackCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, SceneAction::creatScene()));
}

void SceneMain::menuMissionCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->addChild(LayerMission::create(), 10);
}
//锻炼菜单项
void SceneMain::menuExerciseCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->addChild(LayerExercise::create(), 10);
}
//物品菜单项
void SceneMain::menuGoodsCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->addChild(LayerGoods::create(), 10);
}
//打工菜单项
void SceneMain::menuWorkCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->addChild(LayerWork::create(), 10);
}
//休息菜单项
void SceneMain::menuRestCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->addChild(LayerRest::create(), 10);
}
//更新自己
void SceneMain::updateMe()
{
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	int day = 1 + user_info->getPlaidDays();
	int month = 9;
	if (day > 30 && day <= 61)
	{//10
		month = 10;
		day = day - 30;
	}
	else if (day > 61 && day <= 91)
	{//11
		month = 11;
		day = day - 61;
	}
	else if (day > 91 && day <= 122)
	{//12
		month = 12;
		day = day - 91;
	}
	else if (day > 122 && day <= 153)
	{//1
		month = 1;
		day = day - 122;
	}
	else if (day > 153 && day <= 181)
	{//2
		month = 2;
		day = day - 153;
	}
	else if (day > 181 && day <= 212)
	{//3
		month = 3;
		day = day - 181;
	}
	else if (day > 212 && day <= 242)
	{//4
		month = 4;
		day = day - 212;
	}
	else if (day > 242 && day <= 273)
	{//5
		month = 5;
		day = day - 242;
	}
	else if (day > 273 && day <= 303)
	{//6
		month = 6;
		day = day - 273;
	}
	else if (day > 303 && day <= 334)
	{//7
		month = 7;
		day = day - 303;
	}
	else if (day > 334 && day <= 365)
	{//8
		month = 8;
		day = day - 334;
	}
	CCNode *node = this->getChildByTag(0);
	//月
	CCLabelAtlas *atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("%d", month)->getCString());
	//日
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", day)->getCString());
	//体力
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(2));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString());
	//金币
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(3));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentGold())->getCString());

	node = this->getChildByTag(1);
	//体魄
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString());
	//加成
	CCSize size_atlas = atlas->getContentSize();
	atlas = static_cast<CCLabelAtlas *>(atlas->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("(+%d)", user_info->getBonusById(1))->getCString());
	atlas->setPosition(ccp(size_atlas.width, 0));

	//魅力
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(2));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString());
	//加成
	size_atlas = atlas->getContentSize();
	atlas = static_cast<CCLabelAtlas *>(atlas->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("(+%d)", user_info->getBonusById(2))->getCString());
	atlas->setPosition(ccp(size_atlas.width, 0));

	//智力
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(3));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString());
	//加成
	size_atlas = atlas->getContentSize();
	atlas = static_cast<CCLabelAtlas *>(atlas->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("(+%d)", user_info->getBonusById(3))->getCString());
	atlas->setPosition(ccp(size_atlas.width, 0));

	//情商
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(4));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString());
	//加成
	size_atlas = atlas->getContentSize();
	atlas = static_cast<CCLabelAtlas *>(atlas->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("(+%d)", user_info->getBonusById(4))->getCString());
	atlas->setPosition(ccp(size_atlas.width, 0));

	//感性
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(5));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString());
	//加成
	size_atlas = atlas->getContentSize();
	atlas = static_cast<CCLabelAtlas *>(atlas->getChildByTag(0));
	atlas->setString(CCString::createWithFormat("(+%d)", user_info->getBonusById(5))->getCString());
	atlas->setPosition(ccp(size_atlas.width, 0));

	node = this->getChildByTag(2);
	//好感度进度条
	CCProgressTimer *progress_timer = static_cast<CCProgressTimer *>(node->getChildByTag(0));
	progress_timer->setPercentage(user_info->getCurrentFavor());
	//好感度数值
	atlas = static_cast<CCLabelAtlas *>(node->getChildByTag(1));
	atlas->setString(CCString::createWithFormat("%d", user_info->getCurrentFavor())->getCString());
}

//补充好感度
void SceneMain::callbackBuyFavor(CCNode* pSender)
{
	if (pSender->getTag() == 1)
	{
		callbackBuiedFavor();
	}
}
//购买后的回调
void SceneMain::callbackBuiedFavor()
{
	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();
	user_info->setCurrentFavor(100);
	updateMe();
}
//表白
void SceneMain::menuExpressCallback(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	TopwoTools *tl = Topwo::getInstance()->getTopwoTools();
	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();
	DataNpc* data_npc = td->getDataNpcFromArray(user_info->getCurrentWooer());
	if (user_info->getCurrentFavor() < 100)
	{
		this->addChild(LayerHint::createWith(CCLabelTTF::create(CCString::createWithFormat("%s%s", data_npc->getName()->getCString(), tl->getXmlString("HintFavorNotEnough")->getCString())->getCString(), "", 30), 2, this, callfuncN_selector(SceneMain::callbackBuyFavor)));
		return;
	}
	DataMission* mission_data = td->getDataMissionFromArray(data_npc->getExpressMissionId());
	if (mission_data->getType() == 4)
	{
		double mission_value = mission_data->getTarget();
		DataSection* data_section = td->getDataSectionFromArray((int)mission_value);
		this->addChild(LayerDialog::createWith(data_section->getBeginId(), data_section->getEndId(), this, callfunc_selector(SceneMain::callbackExpressOver)), 10);
	}
}
//表白结束回调
void SceneMain::callbackExpressOver()
{
	Topwo::getInstance()->getTopwoAudio()->playMusic(1);

	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();
	DataNpc* data_npc = td->getDataNpcFromArray(user_info->getCurrentWooer());
	int mission_id = data_npc->getExpressMissionId() + 1;
	DataMission* mission_data = td->getDataMissionFromArray(mission_id);
	user_info->setCurrentWooer(mission_data->getWooer());
	user_info->setCurrentFavor(10);
	user_info->setPlaidDays(0);
	user_info->setCurrentMissionId(mission_id);
	user_info->setCurrentMissionIsConsume(false);
	updateMe();
}