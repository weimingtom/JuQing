#ifndef __LAYER_PROGRESS_H__
#define __LAYER_PROGRESS_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

class LayerProgress : public cocos2d::CCLayer
{
public:
	LayerProgress();
	~LayerProgress();
	virtual bool init();
	CREATE_FUNC(LayerProgress);

	//≥ı ºªØUI
	bool initUI();
	virtual void registerWithTouchDispatcher() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void setCallFunc(CCCallFunc* callfunc);
private:
};

#endif // __LAYER_PROGRESS_H__
