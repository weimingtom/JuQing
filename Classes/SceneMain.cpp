#include "SceneMain.h"
#include "SceneAction.h"
#include "LayerMission.h"
#include "LayerExercise.h"

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
	this->addChild(sprite);
	CCSize size_date = sprite->getContentSize();

	//����
	CCLabelAtlas* atlas = CCLabelAtlas::create("9","fonts/atlas/number_style_1.png",20, 20, '0');
	sprite->addChild(atlas, 0, 0);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 6.75f, size_date.height * 0.556f));

	//����
	atlas = CCLabelAtlas::create("1", "fonts/atlas/number_style_1.png", 20, 20, '0');
	sprite->addChild(atlas, 0, 1);
	atlas->setAnchorPoint(ccp(0.5f, 0.5f));
	atlas->setPosition(ccp(size_date.width / 3.2f, size_date.height * 0.556f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString(), "fonts/atlas/number_style_1.png", 20, 20, '0');
	sprite->addChild(atlas, 0, 2);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width / 1.96f, size_date.height * 0.526f));

	//�����
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGold())->getCString(), "fonts/atlas/number_style_1.png", 20, 20, '0');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_date.width * 0.77f, size_date.height * 0.526f));

	//�������
	sprite = CCSprite::create("images/SenceMain_user_attributes.png");
	sprite->setAnchorPoint(ccp(0, 1.0f));
	sprite->setPosition(ccp(vo.x, vo.y + vs.height));
	this->addChild(sprite);
	CCSize size_attribute = sprite->getContentSize();

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentTiPo())->getCString(), "fonts/atlas/number_style_2.png", 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.625f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentMeiLi())->getCString(), "fonts/atlas/number_style_2.png", 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.5f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentZhiLi())->getCString(), "fonts/atlas/number_style_2.png", 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.375f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentEQ())->getCString(), "fonts/atlas/number_style_2.png", 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.248f));

	//������
	atlas = CCLabelAtlas::create(CCString::createWithFormat("%d", user_info->getCurrentGanXing())->getCString(), "fonts/atlas/number_style_2.png", 9, 15, '+');
	sprite->addChild(atlas, 0, 3);
	atlas->setAnchorPoint(ccp(0, 0.5f));
	atlas->setPosition(ccp(size_attribute.width * 0.4f, size_attribute.height * 0.122f));

	//������
	CCMenuItemImage *item_back = CCMenuItemImage::create(
		"images/btn_back_0.png",
		"images/btn_back_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_back = item_back->getContentSize();
	item_back->setPosition(ccp(vs.width - size_item_back.width * 0.5f, vs.height - size_item_back.height * 0.5f));

	//�����
	CCMenuItemImage *item_gift = CCMenuItemImage::create(
		"images/btn_gift_0.png",
		"images/btn_gift_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_gift = item_gift->getContentSize();
	item_gift->setPosition(ccp(size_attribute.width * 0.5f, (vs.height - size_attribute.height) * 0.5f));

	//��Ϣ��
	CCMenuItemImage *item_rest = CCMenuItemImage::create(
		"images/btn_rest_0.png",
		"images/btn_rest_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_rest = item_rest->getContentSize();
	item_rest->setPosition(ccp(vs.width * 0.5f, size_item_rest.height * 0.5f));

	//��Ʒ��
	CCMenuItemImage *item_goods = CCMenuItemImage::create(
		"images/btn_goods_0.png",
		"images/btn_goods_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_goods = item_goods->getContentSize();
	item_goods->setPosition(ccp(vs.width * 0.5f + size_item_rest.width * 1.25f, size_item_rest.height * 0.5f));

	//�����
	CCMenuItemImage *item_express = CCMenuItemImage::create(
		"images/btn_express_0.png",
		"images/btn_express_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_express = item_express->getContentSize();
	item_express->setPosition(ccp(vs.width * 0.5f - size_item_rest.width * 1.25f, size_item_rest.height * 0.5f));

	//������
	CCMenuItemImage *item_task = CCMenuItemImage::create(
		"images/btn_mission_0.png",
		"images/btn_mission_1.png",
		this,
		menu_selector(SceneMain::menuMissionCallback));
	CCSize size_item_task = item_task->getContentSize();
	item_task->setPosition(ccp(vs.width - size_item_task.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height));

	//������
	CCMenuItemImage *item_exercise = CCMenuItemImage::create(
		"images/btn_exercise_0.png",
		"images/btn_exercise_1.png",
		this,
		menu_selector(SceneMain::menuExerciseCallback));
	CCSize size_item_exercise = item_exercise->getContentSize();
	item_exercise->setPosition(ccp(vs.width - size_item_exercise.width * 1.75f, vs.height - size_date.height * 2.0f - size_item_task.height - size_item_exercise.height * 1.25f));

	//����
	CCMenuItemImage *item_work = CCMenuItemImage::create(
		"images/btn_work_0.png",
		"images/btn_work_1.png",
		this,
		menu_selector(SceneMain::menuBackCallback));
	CCSize size_item_work = item_work->getContentSize();
	item_work->setPosition(ccp(vs.width - size_item_exercise.width * 0.5f, vs.height - size_date.height * 2.0f - size_item_task.height - size_item_exercise.height * 1.25f));
	
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