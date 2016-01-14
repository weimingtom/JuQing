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

	setTouchEnabled(true);  //开启触摸响应

	return true;
}
void LayerMission::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
//初始化UI
bool LayerMission::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//背景
	CCSprite* mission_bg = CCSprite::create("images/LayerMission_bg.png");
	this->addChild(mission_bg);
	CCSize size_mission_bg = mission_bg->getContentSize();
	mission_bg->setPosition(ccp(vo.x + vs.width * 0.5f, vo.y + vs.height * 0.5f));

	//体力值
	CCSprite* sp_physical = CCSprite::create("images/LayerMission_physical.png");
	mission_bg->addChild(sp_physical);
	CCSize size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_mission_bg.width * 0.52f, size_mission_bg.height * 0.78f));

	//消耗的体力值
	CCLabelAtlas* atlas_need_physical = CCLabelAtlas::create("10", "fonts/atlas/number_style_1.png", 20, 20, '0');
	sp_physical->addChild(atlas_need_physical);
	atlas_need_physical->setAnchorPoint(ccp(0.5f, 0.5f));
	CCSize size_atlas_need_physical = atlas_need_physical->getContentSize();
	atlas_need_physical->setPosition(ccp(size_sp_physical.width * 0.28f, size_sp_physical.height * 0.45f));

	//当前拥有的体力值
	__atlas_total_physical = CCLabelAtlas::create("", "fonts/atlas/number_style_1.png", 20, 20, '0');
	sp_physical->addChild(__atlas_total_physical);
	__atlas_total_physical->setAnchorPoint(ccp(0, 0.5f));
	CCSize size_atlas_total_physical = __atlas_total_physical->getContentSize();
	__atlas_total_physical->setPosition(ccp(size_sp_physical.width * 0.95f, size_sp_physical.height * 0.45f));

	//名字
	__ttf_name = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 40.0f);
	mission_bg->addChild(__ttf_name);
	__ttf_name->setColor(ccc3(218, 69, 231));
	CCSize size_ttf_name = __ttf_name->getContentSize();
	__ttf_name->setPosition(ccp(size_mission_bg.width * 0.205f, size_mission_bg.height * 0.77f));

	//标题
	__ttf_title = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 36.0f);
	mission_bg->addChild(__ttf_title);
	__ttf_title->enableStroke(ccc3(0, 117, 146), 1.0f);
	CCSize size_ttf_title = __ttf_title->getContentSize();
	__ttf_title->setPosition(ccp(size_mission_bg.width * 0.5f, size_mission_bg.height - 32.0f));

	//内容
	__ttf_content = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeMake(460.0f, 110.0f), kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_content);
	__ttf_content->setAnchorPoint(ccp(0.5f, 1.0f));
	CCSize size_ttf_content = __ttf_content->getContentSize();
	__ttf_content->setPosition(ccp(size_mission_bg.width * 0.53f, size_mission_bg.height * 0.68f));

	//目标
	__ttf_mission = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeZero, kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_mission);
	__ttf_mission->setAnchorPoint(ccp(0, 0.5f));
	__ttf_mission->enableStroke(ccc3(165, 51, 191), 1.0f);
	CCSize size_ttf_target = __ttf_mission->getContentSize();
	__ttf_mission->setPosition(ccp(size_mission_bg.width * 0.13f, size_mission_bg.height * 0.32f));

	//奖励
	__ttf_reward = CCLabelTTF::create("", "fonts/ttfs/arial.ttf", 24.0f, CCSizeZero, kCCTextAlignmentLeft);
	mission_bg->addChild(__ttf_reward);
	__ttf_reward->setAnchorPoint(ccp(0, 0.5f));
	__ttf_reward->enableStroke(ccc3(214, 221, 179), 1.0f);
	CCSize size_ttf_reward = __ttf_reward->getContentSize();
	__ttf_reward->setPosition(ccp(size_mission_bg.width * 0.13f, size_mission_bg.height * 0.24f));

	//任务指引选项
	__item_mission_guide = CCMenuItemImage::create(
		"images/btn_mission_guide_0.png",
		"images/btn_mission_guide_1.png",
		this,
		menu_selector(LayerMission::menuCallbackMissionGuide));
	CCSize size_item_mission_guide = __item_mission_guide->getContentSize();
	__item_mission_guide->setPosition(ccp(size_mission_bg.width * 0.5f, size_item_mission_guide.height * 0.5f));

	//获取奖励选项
	__item_get_reward = CCMenuItemImage::create(
		"images/btn_get_reward_0.png",
		"images/btn_get_reward_1.png",
		this,
		menu_selector(LayerMission::menuCallbackGetReward));
	CCSize size_item_get_reward = __item_get_reward->getContentSize();
	__item_get_reward->setPosition(ccp(size_mission_bg.width * 0.5f, size_item_mission_guide.height * 0.5f));

	//关闭选项
	CCMenuItemImage *item_close = CCMenuItemImage::create(
		"images/btn_close_1_0.png",
		"images/btn_close_1_0.png",
		this,
		menu_selector(LayerMission::menuCallbackClose));
	CCSize size_item_close = item_close->getContentSize();
	item_close->setPosition(ccp(size_mission_bg.width - size_item_close.width * 0.5f, size_mission_bg.height - size_item_close.height * 0.5f));

	CCMenu* pMenu = CCMenu::create(item_close, __item_mission_guide, __item_get_reward, NULL);
	mission_bg->addChild(pMenu, 1);
	pMenu->setPosition(CCPointZero);

	updataMissionContent();

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
	//剩余体力值
	__atlas_total_physical->setString(CCString::createWithFormat("%d", user_info->getCurrentPhysical())->getCString());
	//追求者
	__ttf_name->setString(npc_data->getName()->getCString());
	//标题
	__ttf_title->setString(mission_data->getTitle()->getCString());
	//内容
	__ttf_content->setString(mission_data->getContent()->getCString());
	//任务
	__ttf_mission->setString(CCString::createWithFormat("%s%s", tl->getXmlString("Require")->getCString(), mission_data->getMission()->getCString())->getCString());
	//奖励
	__ttf_reward->setString(CCString::createWithFormat("%s%d%s", tl->getXmlString("Reward")->getCString(), mission_data->getReward(), tl->getXmlString("Gold")->getCString())->getCString());

	//目标值
	bool is_finish = false;
	float mission_value = (float)mission_data->getTarget();
	int mission_type = mission_data->getType();
	if (mission_type == 1)
	{//对话任务
		if (user_info->getCurrentSectionId() == (int)mission_value)
		{
			is_finish = true;
		}
	}
	else if (mission_type == 2)
	{//锻炼任务
		int value_int = (int)mission_value;
		float value_float = mission_value - (float)value_int;
		if (tl->floatIsEquals(value_float, 0.1f))
		{//体魄
			if (user_info->getCurrentTiPo() >= value_int)
			{
				is_finish = true;
			}
		}
		else if (tl->floatIsEquals(value_float, 0.2f))
		{//魅力
			if (user_info->getCurrentMeiLi() >= value_int)
			{
				is_finish = true;
			}
		}
		else if (tl->floatIsEquals(value_float, 0.3f))
		{//智力
			if (user_info->getCurrentZhiLi() >= value_int)
			{
				is_finish = true;
			}
		}
		else if (tl->floatIsEquals(value_float, 0.4f))
		{//情商
			if (user_info->getCurrentEQ() >= value_int)
			{
				is_finish = true;
			}
		}
		else if (tl->floatIsEquals(value_float, 0.5f))
		{//感性
			if (user_info->getCurrentGanXing() >= value_int)
			{
				is_finish = true;
			}
		}
	}
	else if (mission_type == 3)
	{//购买任务
		int value_int = (int)mission_value;
		float value_float = mission_value - (float)value_int;
		if (tl->floatIsEquals(value_float, 0.1f))
		{//物品1
		}
		else if (tl->floatIsEquals(value_float, 0.2f))
		{//物品2
		}
		else if (tl->floatIsEquals(value_float, 0.3f))
		{//物品3
		}
		else if (tl->floatIsEquals(value_float, 0.4f))
		{//物品4
		}
		else if (tl->floatIsEquals(value_float, 0.5f))
		{//物品5
		}
		is_finish = true;
	}

	setMissionFinishState(is_finish);
}

void LayerMission::menuCallbackMissionGuide(CCObject* pSender)
{
	TopwoTools *tl = Topwo::getInstance()->getTopwoTools();
	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	DataMission *data_mission = user_info->getDataMissionFromArray(user_info->getCurrentMissionId());

	if (user_info->getCurrentPhysical() < 10)
	{//体力不足
		return;
	}

	user_info->setCurrentPhysical(user_info->getCurrentPhysical() - 10);

	float mission_value = (float)data_mission->getTarget();
	int mission_type = data_mission->getType();
	if (mission_type == 1)
	{//对话任务
		DataSection *data_section = user_info->getDataSectionFromArray((int)mission_value);
		this->addChild(LayerDialog::createWith(data_section->getBeginId(), data_section->getEndId(), this, callfunc_selector(LayerMission::callbackDialogOver)), 10);
	}
	else if (mission_type == 2)
	{//锻炼任务
		int value_int = (int)mission_value;
		float value_float = mission_value - (float)value_int;
		if (tl->floatIsEquals(value_float, 0.1f))
		{//体魄
		}
		else if (tl->floatIsEquals(value_float, 0.2f))
		{//魅力
		}
		else if (tl->floatIsEquals(value_float, 0.3f))
		{//智力
		}
		else if (tl->floatIsEquals(value_float, 0.4f))
		{//情商
		}
		else if (tl->floatIsEquals(value_float, 0.5f))
		{//感性
		}
	}
	else if (mission_type == 3)
	{//购买任务
		int value_int = (int)mission_value;
		float value_float = mission_value - (float)value_int;
		if (tl->floatIsEquals(value_float, 0.1f))
		{//物品1
		}
		else if (tl->floatIsEquals(value_float, 0.2f))
		{//物品2
		}
		else if (tl->floatIsEquals(value_float, 0.3f))
		{//物品3
		}
		else if (tl->floatIsEquals(value_float, 0.4f))
		{//物品4
		}
		else if (tl->floatIsEquals(value_float, 0.5f))
		{//物品5
		}
	}
}

void LayerMission::menuCallbackGetReward(CCObject* pSender)
{
	TopwoData *td = Topwo::getInstance()->getTopwoData();
	UserInfo *user_info = td->getUserInfo();

	//领取奖励
	int cur_mission_id = user_info->getCurrentMissionId();
	DataMission* mission_data = user_info->getDataMissionFromArray(cur_mission_id);
	user_info->setCurrentGold(user_info->getCurrentGold() + mission_data->getReward());

	//跳到下一个任务
	user_info->setCurrentMissionId(user_info->getCurrentMissionId() + 1);

	updataMissionContent();
}
void LayerMission::menuCallbackClose(CCObject* pSender)
{
	this->removeFromParent();
}
void LayerMission::callbackDialogOver()
{
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	int cur_mission_id = user_info->getCurrentMissionId();
	DataMission* mission_data = user_info->getDataMissionFromArray(cur_mission_id);
	float mission_value = (float)mission_data->getTarget();
	user_info->setCurrentSectionId((int)mission_value);

	updataMissionContent();
}
void LayerMission::setMissionFinishState(bool is_finish)
{
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