#ifndef __TOPWO_PLATFORM_H__
#define __TOPWO_PLATFORM_H__

#include "cocos2d.h"

USING_NS_CC;


typedef void (CCObject::*SEL_CallFuncI)(int);
#define callfuncI_selector(_SELECTOR) (SEL_CallFuncI)(&_SELECTOR)

class TopwoPlatform : public CCObject
{
public:
	TopwoPlatform();
	virtual ~TopwoPlatform();
	virtual bool init();
	CREATE_FUNC(TopwoPlatform);
	

	// -------------------------------------------------------------
	//显示退出框
	void callShowExitDialog();
	//打开网址
	void callOpenURL(const char* pszUrl);
	//调用支付
	void callPay(int id, CCObject* target, SEL_CallFuncI callfun);
	//支付回调
	void payCallback(int status);
	//退出回调
	void exitCallback();

	//设置当前玩家的等级
	void setLevel(int level);
	//游戏关卡开始
	void levelBegin(const char* levelId);
	//游戏关卡通过
	void levelComplete(const char* levelId);
	//游戏关卡通关失败
	void levelIdFail(const char* levelId);
	//记录玩家虚拟币留存总量
	void setCoinNum(int coinNum, const char* coinType);
	//自定义事件
	void onEvent(const char* eventId);


	//展示对话框积分墙
	void showOffersWallDialog();

	//展示对话框分享
	void showShareWallDialog();

	//奖励
	void awardPoints(float f);
	//消费
	void spendPoints(float f);
	//查询积分
	float queryPoints();

private:

	CCObject* __callbackListener;
	SEL_CallFuncI __callbackfunc;
};

#endif  //__TOPWO_PLATFORM_H__