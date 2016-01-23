#ifndef __LAYER_WORK_H__
#define __LAYER_WORK_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

static const char RES_LayerWork_title[] = "images/LayerWork_title.png";
static const char RES_LayerWork_job_1_0[] = "images/LayerWork_job_1_0.png";
static const char RES_LayerWork_job_1_1[] = "images/LayerWork_job_1_1.png";
static const char RES_LayerWork_job_2_0[] = "images/LayerWork_job_2_0.png";
static const char RES_LayerWork_job_2_1[] = "images/LayerWork_job_2_1.png";
static const char RES_LayerWork_job_3_0[] = "images/LayerWork_job_3_0.png";
static const char RES_LayerWork_job_3_1[] = "images/LayerWork_job_3_1.png";

class LayerWork : public cocos2d::CCLayer
{
public:
	LayerWork();
	~LayerWork();
	virtual bool init();
	CREATE_FUNC(LayerWork);

	//初始化UI
	bool initUI();
	virtual void registerWithTouchDispatcher() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void menuCallbackClose(CCObject* pSender);
	void menuCallbackWork(CCObject* pSender);
	void work(CCObject* pSender);
private:
};

#endif
