#include "LayerMission.h"
#include "Topwo.h"
#include "UserInfo.h"
#include "LayerDialog.h"

LayerMission::LayerMission()
:__atlas_total_physical(NULL)
, __ttf_name(NULL)
, __ttf_title(NULL)
, __ttf_content(NULL)
, __ttf_mission(NULL)
, __ttf_reward(NULL)
{

}
LayerMission::~LayerMission()
{
}
bool LayerMission::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
	}

	initUI();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);

    return true;
}
//��ʼ��UI
bool LayerMission::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//����
	CCSprite* mission_bg = CCSprite::create("images/LayerMission_bg.png");
	this->addChild(mission_bg);
	CCSize size_mission_bg = mission_bg->getContentSize();
	mission_bg->setPosition(ccp(vo.x + vs.width * 0.5f, vo.y + vs.height * 0.5f));

	//����ֵ
	CCSprite* sp_physical = CCSprite::create("images/LayerMission_physical.png");
	mission_bg->addChild(sp_physical);
	CCSize size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_mission_bg.width * 0.52f, size_mission_bg.height * 0.78f));

	//���ĵ�����ֵ
	CCLabelAtlas* atlas_need_physical = CCLabelAtlas::create("10", "fonts/atlas/number_style_1.png", 20, 20, '0');
	sp_physical->addChild(atlas_need_physical);
	atlas_need_physical->setAnchorPoint(ccp(0.5f, 0.5f));
	CCSize size_atlas_need_physical = atlas_need_physical->getContentSize();
	atlas_need_physical->setPosition(ccp(size_sp_physical.width * 0.28f, size_sp_physical.height * 0.45f));

	//��ǰӵ�е�����ֵ
	__atlas_total_physical = CCLabelAtlas::create("", "fonts/atlas/number_style_1.png", 20, 20, '0');
	sp_physical->addChild(__atlas_total_physical);
	__atlas_total_physical->setAnchorPoint(ccp(0, 0.5f));
	CCSize size_atlas_total_physical = __atlas_total_physical->getContentSize();
	__atlas_total_physical->setPosition(ccp(size_sp_physical.width * 0.95f, size_sp_physical.height * 0.45f));

	//����
	__ttf_name = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 40.0f);
	mission_bg->addChild(__ttf_name);
	__ttf_name->setColor(ccc3(218, 69, 231));
	CCSize size_ttf_name = __ttf_name->getContentSize();
	__ttf_name->setPosition(ccp(size_mission_bg.width * 0.205f, size_mission_bg.height * 0.77f));

	//����
	__ttf_title = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 36.0f);
	mission_bg->addChild(__ttf_title);
	__ttf_title->enableStroke(ccc3(0, 117, 146), 1.0f);
	CCSize size_ttf_title = __ttf_title->getContentSize();
	__ttf_title->setPosition(ccp(size_mission_bg.width * 0.5f, size_mission_bg.height - 32.0f));

	//����
	__ttf_content = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeMake(460.0f, 110.0f), kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_content);
	__ttf_content->setAnchorPoint(ccp(0.5f, 1.0f));
	CCSize size_ttf_content = __ttf_content->getContentSize();
	__ttf_content->setPosition(ccp(size_mission_bg.width * 0.53f, size_mission_bg.height * 0.68f));

	//Ŀ��
	__ttf_mission = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeZero, kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_mission);
	__ttf_mission->setAnchorPoint(ccp(0, 0.5f));
	__ttf_mission->enableStroke(ccc3(165, 51, 191), 1.0f);
	CCSize size_ttf_target = __ttf_mission->getContentSize();
	__ttf_mission->setPosition(ccp(size_mission_bg.width * 0.13f, size_mission_bg.height * 0.32f));

	//����
	__ttf_reward = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeZero, kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_reward);
	__ttf_reward->setAnchorPoint(ccp(0, 0.5f));
	__ttf_reward->enableStroke(ccc3(214, 221, 179), 1.0f);
	CCSize size_ttf_reward = __ttf_reward->getContentSize();
	__ttf_reward->setPosition(ccp(size_mission_bg.width * 0.13f, size_mission_bg.height * 0.24f));

	//����ָ��ѡ��
	__item_mission_guide = CCMenuItemImage::create(
		"images/btn_mission_guide_0.png",
		"images/btn_mission_guide_1.png",
		this,
		menu_selector(LayerMission::menuCallbackMissionGuide));
	CCSize size_item_mission_guide = __item_mission_guide->getContentSize();
	__item_mission_guide->setPosition(ccp(size_mission_bg.width * 0.5f, size_item_mission_guide.height * 0.5f));

	//��ȡ����ѡ��
	__item_get_reward = CCMenuItemImage::create(
		"images/btn_get_reward_0.png",
		"images/btn_get_reward_1.png",
		this,
		menu_selector(LayerMission::menuCallbackGetReward));
	CCSize size_item_get_reward = __item_get_reward->getContentSize();
	__item_get_reward->setPosition(ccp(size_mission_bg.width * 0.5f, size_item_mission_guide.height * 0.5f));

	//�ر�ѡ��
	CCMenuItemImage *item_close = CCMenuItemImage::create(
		"images/btn_close_1_0.png",
		"images/btn_close_1_0.png",
		this,
		menu_selector(LayerMission::menuCallbackClose));
	CCSize size_item_close = item_close->getContentSize();
	item_close->setPosition(ccp(size_mission_bg.width - size_item_close.width * 0.5f, size_mission_bg.height - size_item_close.height * 0.5f));

	CCMenu* pMenu = CCMenu::create(item_close, __item_mission_guide, __item_get_reward, NULL);
	pMenu->setPosition(CCPointZero);
	mission_bg->addChild(pMenu, 1);

	updataMissionContent();

	checkMissionIsFinish();

	return true;
}
void LayerMission::updataMissionContent()
{
	TopwoTools *tl = Topwo::getInstance()->getTopwoTools();
	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();
	DataNpc * npc_data = user_info->getDataNpcFromArray(user_info->getCurrentWooer());
	int cur_mission_id = user_info->getCurrentMissionId();
	DataMission* mission_data = user_info->getDataMissionFromArray(cur_mission_id);
	//ʣ������ֵ
	__atlas_total_physical->setString(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString());
	//׷����
	__ttf_name->setString(npc_data->getName()->getCString());
	//����
	__ttf_title->setString(mission_data->getTitle()->getCString());
	//����
	__ttf_content->setString(mission_data->getContent()->getCString());
	//����
	__ttf_mission->setString(CCString::createWithFormat("%s%s", tl->getXmlString("Require")->getCString(), mission_data->getMission()->getCString())->getCString());
	//����
	__ttf_reward->setString(CCString::createWithFormat("%s%d%s", tl->getXmlString("Reward")->getCString(), mission_data->getReward(), tl->getXmlString("Gold")->getCString())->getCString());

	//Ŀ��ֵ
	float mission_value = (float)mission_data->getTarget();
	int mission_type = mission_data->getType();
	bool is_finish = false;
	if (mission_type == 1)
	{//�Ի�����
		if (cur_mission_id >= (int)mission_value)
		{
			is_finish = true;
		}
	}
	else if (mission_type == 2)
	{//��������
		int value_int = (int)mission_value;
		float value_double = mission_value - (float)value_int;
		if (value_double == 0.1)
		is_finish = true;
	}
	else if (mission_type == 3)
	{//��������
		is_finish = true;
	}
	if (is_finish)
	{
		__item_mission_guide->setVisible(false);
		__item_mission_guide->setEnabled(false);
		__item_get_reward->setVisible(true);
		__item_get_reward->setEnabled(true);
	}
	else
	{
		__item_mission_guide->setVisible(true);
		__item_mission_guide->setEnabled(true);
		__item_get_reward->setVisible(false);
		__item_get_reward->setEnabled(false);
	}
}

void LayerMission::menuCallbackMissionGuide(CCObject* pSender)
{
	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	DataMission *data_mission = user_info->getDataMissionFromArray(user_info->getCurrentMissionId());

	if (user_info->getCurrentPhysical() < 10)
	{//��������
		return;
	}

	user_info->setCurrentPhysical(user_info->getCurrentPhysical() - 10);

	if (data_mission->getType() == 1)
	{
		int section_id = user_info->getCurrentSectionId();
		int begin_id = user_info->getDataSectionFromArray(section_id)->getBeginId();
		int end_id = user_info->getDataSectionFromArray(section_id)->getEndId();
		this->addChild(LayerDialog::createWith(begin_id, end_id, this, callfunc_selector(LayerMission::callbackDialogOver)), 10);
		user_info->setCurrentSectionId(++section_id);
	}
}

void LayerMission::menuCallbackGetReward(CCObject* pSender)
{
	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();
	user_info->setCurrentMissionId(user_info->getCurrentMissionId() + 1);

	updataMissionContent();
}
void LayerMission::menuCallbackClose(CCObject* pSender)
{
	this->removeFromParent();
}
void LayerMission::callbackDialogOver()
{
}
void LayerMission::removeFromParent()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::removeFromParent();
}

void LayerMission::checkMissionIsFinish()
{
	bool is_finish = false;

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	DataMission *data_mission = user_info->getDataMissionFromArray(user_info->getCurrentMissionId());
	if (data_mission->getType() == 1)
	{//�Ի�����
		is_finish = true;
	}
	else if (data_mission->getType() == 2)
	{//��������
		is_finish = true;
	}
	else if (data_mission->getType() == 3)
	{//��������
		is_finish = true;
	}

	if (is_finish)
	{
		__item_mission_guide->setVisible(false);
		__item_mission_guide->setEnabled(false);
		__item_get_reward->setVisible(true);
		__item_get_reward->setEnabled(true);
	}
	else
	{
		__item_mission_guide->setVisible(true);
		__item_mission_guide->setEnabled(true);
		__item_get_reward->setVisible(false);
		__item_get_reward->setEnabled(false);
	}
	updataMissionContent();
}
bool LayerMission::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerMission::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerMission::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerMission::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}