#include "LayerDialog.h"
#include "Topwo.h"

// on "init" you need to initialize your instance
bool LayerDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	initUI();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
    
    return true;
}

//初始化UI
bool LayerDialog::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	//背景
	__bg = CCSprite::create("bg_SceneMain_1.jpg");
	__bg->retain();
	__bg->setPosition(ccp(vs.width / 2.0f + vo.x, vs.height / 2.0f + vo.y));
	this->addChild(__bg, 0);

	//对话框背景
	__bg_dialog = CCSprite::create("bg_dialog.png");
	__bg_dialog->retain();
	CCSize bg_dialog_size = __bg_dialog->getContentSize();
	__bg_dialog->setPosition(ccp(vs.width / 2.0f + vo.x, bg_dialog_size.height / 2.0f + vo.y));
	this->addChild(__bg_dialog, 5);

	//人物名字背景
	__bg_name = CCSprite::create("bg_name.png");
	__bg_name->retain();
	CCSize bg_name_size = __bg_name->getContentSize();
	__bg_name->setPosition(ccp(vo.x + __bg_dialog->getPositionX() - bg_dialog_size.width / 2.0f + bg_name_size.width / 2.0f, vo.y + bg_dialog_size.height + bg_name_size.height / 2.0f + 5.0f));
	this->addChild(__bg_name, 5);

	//立绘
	__vertical_drawing = CCSprite::create("npc1.png");
	__vertical_drawing->retain();
	__vertical_drawing->setAnchorPoint(ccp(0.5f, 1.0f));
	__vertical_drawing->setPosition(ccp(vs.width / 2.0f + vo.x, vs.height + vo.y - 50.0f));
	this->addChild(__vertical_drawing, 2);

	//名字
	CCLabelTTF * ttf_name = CCLabelTTF::create("xiaorou", "fonts/arial.ttf", 36);
	ttf_name->setPosition(ccp(bg_name_size.width / 2.0f, bg_name_size.height / 2.0f));
	__bg_name->addChild(ttf_name, 0, 0);

	//对话
	TopwoLabelTTF* lbl_dialog = TopwoLabelTTF::create("fonts/arial.ttf", 32);
	lbl_dialog->setHorizontalAlignment(kCCTextAlignmentLeft);
	//lbl_dialog->setAlignment(kCCTextAlignmentLeft);
	lbl_dialog->setAnchorPoint(ccp(0, 1.0f));
	lbl_dialog->setTypeString(Topwo::getInstance()->getTopwoTools()->getXmlString("GameName"), bg_dialog_size.width - 80.0f, 0.2f);
	lbl_dialog->setPosition(ccp(bg_dialog_size.width / 2.0f - (bg_dialog_size.width - 80.0f) / 2.0f, bg_dialog_size.height / 2.0f + (bg_dialog_size.height - 40.0f) / 2.0f));
	__bg_dialog->addChild(lbl_dialog, 0, 0);

	return true;
}
void LayerDialog::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool LayerDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	TopwoLabelTTF* lbl_dialog = static_cast<TopwoLabelTTF*>(__bg_dialog->getChildByTag(0));
	lbl_dialog->showAll();
	return true;
}
void LayerDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LayerDialog::menuCloseCallback(CCObject* pSender)
{
}

void LayerDialog::menuBeginCallback(CCObject* pSender)
{
}