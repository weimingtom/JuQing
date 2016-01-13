#ifndef __LAYER_EXERCISE_H__
#define __LAYER_EXERCISE_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

class LayerExercise : public cocos2d::CCLayer
{
public:
	LayerExercise();
	~LayerExercise();
	virtual bool init();
	CREATE_FUNC(LayerExercise);

	//��ʼ��UI
	bool initUI();
	virtual void removeFromParent() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void menuCallbackToLeft(CCObject* pSender);
	void menuCallbackToRight(CCObject* pSender);
	void menuCallbackClose(CCObject* pSender);
	void menuCallbackTipo(CCObject* pSender);
	void menuCallbackMeili(CCObject* pSender);
	void menuCallbackZhili(CCObject* pSender);
	void menuCallbackEq(CCObject* pSender);
	void menuCallbackGanxing(CCObject* pSender);

	void updateMe();
private:
	CC_SYNTHESIZE(int, __level, Level);
	CCSprite *__sp_title;
	CCMenuItemSprite *__item_to_left;
	CCMenuItemSprite *__item_to_right;
	//������
	CCMenuItemSprite *__item_tipo;
	//������
	CCMenuItemSprite *__item_meili;
	//������
	CCMenuItemSprite *__item_zhili;
	//������
	CCMenuItemSprite *__item_eq;
	//������
	CCMenuItemSprite *__item_ganxing;
};

#endif // __LAYER_EXERCISE_H__
