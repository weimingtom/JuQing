#ifndef __LAYER_MISSION_H__
#define __LAYER_MISSION_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

class LayerMission : public cocos2d::CCLayer
{
public:
	LayerMission();
	~LayerMission();
	virtual bool init();
	CREATE_FUNC(LayerMission);

	//初始化UI
	bool initUI();
	virtual void removeFromParent() override;

	void updataMissionContent();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void menuCallbackMissionGuide(CCObject* pSender);
	void menuCallbackGetReward(CCObject* pSender);
	void menuCallbackClose(CCObject* pSender);

	//对话结束回调
	void callbackDialogOver();

	void setMissionFinishState(bool is_finish);
private:
	CCLabelAtlas* __atlas_total_physical;
	CCLabelTTF*  __ttf_name;
	CCLabelTTF* __ttf_title;
	CCLabelTTF* __ttf_content;
	CCLabelTTF* __ttf_mission;
	CCLabelTTF* __ttf_reward;
	CCMenuItemImage *__item_mission_guide;
	CCMenuItemImage *__item_get_reward;
};

#endif // __LAYER_MISSION_H__
