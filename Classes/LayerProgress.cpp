#include "LayerProgress.h"

LayerProgress::LayerProgress()
{

}
LayerProgress::~LayerProgress()
{
}
bool LayerProgress::init()
{
    // 1. super init first
    if (!CCLayer::init() )
    {
        return false;
	}

	initUI();

	setTouchEnabled(true);  //开启触摸响应

    return true;
}
void LayerProgress::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
//初始化UI
bool LayerProgress::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* sp_bg = CCSprite::create("images/LayerProgress_bg.png");
	this->addChild(sp_bg);
	sp_bg->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	CCSprite* sp_bar_0 = CCSprite::create("images/LayerProgress_bar_0.png");
	this->addChild(sp_bar_0);
	CCSize size_sp_bar_0 = sp_bar_0->getContentSize();
	sp_bar_0->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	CCSprite* sp_bar_1 = CCSprite::create("images/LayerProgress_bar_1.png");
	CCProgressTimer* progress_timer = CCProgressTimer::create(sp_bar_1);
	this->addChild(progress_timer, 0, 1);
	progress_timer->setType(kCCProgressTimerTypeBar);
	progress_timer->setAnchorPoint(ccp(0, 0.5f));
	progress_timer->setPosition(ccp(vs.width * 0.5f - size_sp_bar_0.width * sp_bar_0->getAnchorPoint().x, vs.height * 0.5f));
	progress_timer->setMidpoint(ccp(0, 0.5));
	progress_timer->setBarChangeRate(ccp(1, 0));
	
	return true;
}
bool LayerProgress::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerProgress::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerProgress::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerProgress::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LayerProgress::setCallFunc(CCCallFunc* callfunc)
{
	CCProgressTo* progress1 = CCProgressTo::create(2, 100);
	static_cast<CCProgressTimer*>(this->getChildByTag(1))->runAction(CCSequence::create(progress1, callfunc, NULL));
}