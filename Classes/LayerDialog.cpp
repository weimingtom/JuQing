#include "LayerDialog.h"

bool LayerDialog::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
	}

	__start_id = 0;
	__end_id = 0;
	__current_id = 0;

	__is_typed_all = false;

	initUI();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);

    return true;
}
LayerDialog* LayerDialog::createWith(int start_id, int end_id)
{
	LayerDialog* me = create();
	if (!me)
	{
		return NULL;
	}
	me->__start_id = start_id;
	me->__end_id = end_id;
	me->__current_id = me->__start_id;

	me->analyzeDialog(me->__current_id);

	return me;
}

//初始化UI
bool LayerDialog::initUI()
{
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();

	//背景
	__bg = CCSprite::create("bg_black.png");
	__bg->setPosition(ccp(vs.width / 2.0f + vo.x, vs.height / 2.0f + vo.y));
	this->addChild(__bg, 0);

	//立绘
	__vertical_drawing = CCSprite::create();
	__vertical_drawing->setPosition(ccp(vo.x + vs.width / 2.0f, vo.y + vs.height - 50.0f));
	this->addChild(__vertical_drawing, 2);

	//对话框背景
	CCSprite* bg_dialog = CCSprite::create("LayerDialog_bg_dialog.png");
	CCSize bg_dialog_size = bg_dialog->getContentSize();
	bg_dialog->setPosition(ccp(vs.width / 2.0f + vo.x, bg_dialog_size.height / 2.0f + vo.y));
	this->addChild(bg_dialog, 5);

	//人物名字背景
	CCSprite* bg_name = CCSprite::create("LayerDialog_bg_name.png");
	CCSize bg_name_size = bg_name->getContentSize();
	bg_name->setPosition(ccp(vo.x + bg_dialog->getPositionX() - bg_dialog_size.width / 2.0f + bg_name_size.width / 2.0f, vo.y + bg_dialog_size.height + bg_name_size.height / 2.0f + 5.0f));
	this->addChild(bg_name, 5);

	//名字
	__name = CCLabelTTF::create("Name", "fonts/arial.ttf", 36);
	__name->setPosition(ccp(bg_name_size.width / 2.0f, bg_name_size.height / 2.0f));
	bg_name->addChild(__name, 0, 0);

	//对话
	__dialog = TopwoTypeTTF::create("fonts/arial.ttf", 32);
	__dialog->setHorizontalAlignment(kCCTextAlignmentLeft);
	//lbl_dialog->setAlignment(kCCTextAlignmentLeft);
	__dialog->setAnchorPoint(ccp(0, 1.0f));

	__dialog->setTypeSize(bg_dialog_size - CCSizeMake(80.0f, 10.0f));
	__dialog->setTypeInterval(0.2f);
	__dialog->setTypeFinishCallback(this, callfunc_selector(LayerDialog::typedCallBack));
	__dialog->setPosition(ccp(bg_dialog_size.width / 2.0f - (bg_dialog_size.width - 80.0f) / 2.0f, bg_dialog_size.height / 2.0f + (bg_dialog_size.height - 40.0f) / 2.0f));
	bg_dialog->addChild(__dialog, 0, 0);

	return true;
}
void LayerDialog::onExit()
{
}
bool LayerDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!__is_typed_all)
	{
		__dialog->typeAll();
	}
	else
	{
		if (__current_id < __end_id)
		{
			__current_id++;
			analyzeDialog(__current_id);
		}
		else
		{
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			this->removeFromParent();
		}
	}
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
void LayerDialog::typedCallBack()
{
	__is_typed_all = true;
}
//解析一句对话
void LayerDialog::analyzeDialog(int index)
{
	__is_typed_all = false;
	__vertical_drawing->setVisible(false);

	CCTexture2D* texture2d_bg = NULL;

	rapidjson::Value& v = Topwo::getInstance()->getTopwoData()->getJsonValue(index);
	if (v.HasMember("CG") && v["CG"].IsInt())
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("CG_%d.jpg", v["CG"].GetInt())->getCString());
	}
	else
	{
		if (v.HasMember("VE") && v["VE"].IsInt())
		{
			__vertical_drawing->setVisible(true);
			CCTexture2D* texture2d_ve = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("VE_1_%d.png", v["VE"].GetInt())->getCString());
			__vertical_drawing->initWithTexture(texture2d_ve);
			__vertical_drawing->setAnchorPoint(ccp(0.5f, 1.0f));
		}
		if (v.HasMember("BG") && v["BG"].IsInt())
		{
			texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("BG_%d.jpg", v["BG"].GetInt())->getCString());
		}
	}
	if (!texture2d_bg)
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage("bg_black.png");
	}
	__bg->setTexture(texture2d_bg);
	if (v.HasMember("NM") && v["NM"].IsString())
	{
		__name->setString(v["NM"].GetString());
	}

	if (v.HasMember("DG") && v["DG"].IsString())
	{
		__dialog->setTypeString(CCString::createWithFormat("%s", v["DG"].GetString()));
	}
}