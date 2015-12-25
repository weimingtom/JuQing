#ifndef __LAYER_DIALOG_H__
#define __LAYER_DIALOG_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

class LayerDialog : public cocos2d::CCLayer
{
public:
	LayerDialog();
	~LayerDialog();
	virtual bool init();
	CREATE_FUNC(LayerDialog);
	static LayerDialog* createWith(int start_id, int end_id);

	//初始化UI
	bool initUI();

	virtual void onExit() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
    //回调
	void menuCloseCallback(CCObject* pSender);
	void menuForkCallback(CCObject* pSender);

	//解析一句对话
	void analyzeDialog(int index);
	//打字结束回调
	void typedCallBack();
private:
	CCSprite* __bg;
	CCSprite* __vertical_drawing;
	CCLabelTTF* __name;
	TopwoType* __dialog;
	CCArray* __fork_arr;
	CCMenu* __fork_menu;
	bool __is_typed_all;
	int __start_id;
	int __end_id;
	int __current_id;
	int __offset;
};

#endif // __SCENE_DIALOG_H__
