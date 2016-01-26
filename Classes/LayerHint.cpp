#include "LayerHint.h"
#include "LayerMission.h"
#include "LayerExercise.h"
#include "SceneMain.h"
#include "LayerProgress.h"

LayerHint::LayerHint()
:__callbackListener(NULL)
, __callbackfun(NULL)
{

}
LayerHint::~LayerHint()
{
}
bool LayerHint::initWith(CCLabelTTF *content, int style, CCObject* target, SEL_CallFuncN callfun)
{
	__callbackListener = target;
	__callbackfun = callfun;

	initUIWith(content, style);

	setTouchEnabled(true);  //开启触摸响应

    return true;
}
void LayerHint::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
LayerHint* LayerHint::createWith(CCLabelTTF *content, int style, CCObject* target, SEL_CallFuncN callfun)
{
	LayerHint *me = LayerHint::create();
	if (!me)
	{
		return NULL;
	}
	me->initWith(content, style, target, callfun);

	return me;
}
//初始化UI
bool LayerHint::initUIWith(CCLabelTTF *content, int style)
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//背景
	CCSprite* sp_bg = CCSprite::create(RES_LayerHint_bg);
	this->addChild(sp_bg);
	CCSize size_sp_bg = sp_bg->getContentSize();
	sp_bg->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	//内容
	sp_bg->addChild(content);
	content->setAnchorPoint(ccp(0.5f, 0.5f));
	content->setHorizontalAlignment(kCCTextAlignmentCenter);
	content->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	content->setPosition(ccp(size_sp_bg.width * 0.5f, size_sp_bg.height * 0.65f));
	content->setColor(ccRED);
	if (content->getContentSize().width > size_sp_bg.width * 0.9f)
	{
		content->setHorizontalAlignment(kCCTextAlignmentLeft);
		content->setDimensions(CCSizeMake(size_sp_bg.width * 0.85f, 0));
	}

	//菜单
	CCMenu *pMenu = CCMenu::create();
	this->addChild(pMenu);
	pMenu->setPosition(CCPointZero);

	CCMenuItemSprite *item = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_confirm_0),
		CCSprite::create(RES_btn_confirm_1),
		this,
		menu_selector(LayerHint::buttonCallBack)
		);
	pMenu->addChild(item, 0, 1);
	CCSize size_item = item->getContentSize();

	if (style == 1)
	{
		item->setPosition(ccp(vs.width * 0.5f, (vs.height - size_sp_bg.height) * 0.5f + size_item.height * 1.2f));
	}
	else
	{
		item->setPosition(ccp(vs.width * 0.5f + size_item.width, (vs.height - size_sp_bg.height) * 0.5f + size_item.height * 1.2f));

		item = CCMenuItemSprite::create(
			CCSprite::create(RES_btn_cancel_0),
			CCSprite::create(RES_btn_cancel_1),
			this,
			menu_selector(LayerHint::buttonCallBack)
			);
		pMenu->addChild(item, 0, 2);

		item->setPosition(ccp(vs.width * 0.5f - size_item.width, (vs.height - size_sp_bg.height) * 0.5f + size_item.height * 1.2f));
	}
	
	return true;
}
bool LayerHint::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerHint::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerHint::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerHint::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LayerHint::buttonCallBack(CCObject *pSender)
{
	CCNode* node = dynamic_cast<CCNode*>(pSender);
	if (__callbackListener && __callbackfun)
	{
		(__callbackListener->*__callbackfun)(node);
	}
	this->removeFromParent();
}