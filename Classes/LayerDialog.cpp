#include "LayerDialog.h"

LayerDialog::LayerDialog()
:__fork_arr(NULL)
{

}
LayerDialog::~LayerDialog()
{
	if (__fork_arr)
	{
		__fork_arr->release();
		__fork_arr = NULL;
	}
}
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
	__offset = 1;

	__is_typed_all = false;

	__fork_arr = CCArray::create();
	__fork_arr->retain();

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

	__fork_menu = CCMenu::create();
	this->addChild(__fork_menu,10);
	__fork_menu->setPosition(CCPointZero);
	__fork_menu->setVisible(false);

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
	__dialog = TopwoType::create();
	CCLabelTTF* ttf = static_cast<CCLabelTTF*>(__dialog->createTypedLabel(TopwoType::TypeLabelStyle::LABEL_TTF, "fonts/arial.ttf", 32));
	ttf->setHorizontalAlignment(kCCTextAlignmentLeft);
	//lbl_dialog->setAlignment(kCCTextAlignmentLeft);
	ttf->setAnchorPoint(ccp(0, 1.0f));

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
		if (__fork_menu->getChildrenCount() > 0 && __fork_menu->isVisible())
		{
			return true;
		}
		if (__current_id < __end_id)
		{
			__current_id += __offset;
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

void LayerDialog::menuForkCallback(CCObject* pSender)
{
	__fork_menu->setVisible(false);
	__fork_menu->removeAllChildren();
	int fork_pos = static_cast<CCMenuItemImage*>(pSender)->getZOrder();
	__current_id += fork_pos;
	analyzeDialog(__current_id);
}
void LayerDialog::typedCallBack()
{
	__is_typed_all = true;
	if (__fork_menu->getChildrenCount() > 0)
	{
		__fork_menu->setVisible(true);
	}
}
//解析一句对话
void LayerDialog::analyzeDialog(int index)
{
	__is_typed_all = false;
	__vertical_drawing->setVisible(false);

	CCTexture2D* texture2d_bg = NULL;

	rapidjson::Value& v = Topwo::getInstance()->getTopwoData()->getJsonValue(index);
	if (v.HasMember("CG") && v["CG"].IsNumber())
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("CG_%d.jpg", (int)v["CG"].GetDouble())->getCString());
	}
	else
	{
		if (v.HasMember("VE") && v["VE"].IsNumber())
		{
			__vertical_drawing->setVisible(true);
			CCTexture2D* texture2d_ve = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("VE_1_%d.png", (int)v["VE"].GetDouble())->getCString());
			__vertical_drawing->initWithTexture(texture2d_ve);
			__vertical_drawing->setAnchorPoint(ccp(0.5f, 1.0f));
		}
		if (v.HasMember("BG") && v["BG"].IsNumber())
		{
			texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("BG_%d.jpg", (int)v["BG"].GetDouble())->getCString());
		}
	}
	if (!texture2d_bg)
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage("bg_black.png");
	}
	__bg->setTexture(texture2d_bg);

	if (v.HasMember("FO") && v["FO"].IsString())
	{
		__fork_menu->removeAllChildren();
		do {
			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(v["FO"].GetString());
			CCLOG("doc HasParseError : %d", doc.HasParseError());
			CC_BREAK_IF(doc.HasParseError());
			if (doc.IsArray())
			{
				int doc_size = doc.Size();
				int need = doc_size - __fork_arr->count();
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("btn_fork_0.png");
				CCSize fork_size = texture->getContentSize();
				while (need > 0)
				{
					CCMenuItemImage* fork = CCMenuItemImage::create("btn_fork_0.png", "btn_fork_1.png", this, menu_selector(LayerDialog::menuForkCallback));
					CCLabelTTF* fork_content = CCLabelTTF::create("Fork Content", "fonts/arial.ttf", 28);
					fork->addChild(fork_content);
					fork_content->setTag(0);
					fork_content->setPosition(ccp(fork_size.width / 2.0f, fork_size.height / 2.0f));
					__fork_arr->addObject(fork);
					need--;
				}
				float top_fork_pos = 350.0f + doc_size / 2.0f * fork_size.height;
				for (int i = 0; i < doc_size; i++)
				{
					if (doc[i].IsObject())
					{
						if (doc[i]["fork_item"].IsString())
						{
							CCMenuItemImage* fork = static_cast<CCMenuItemImage*>(__fork_arr->objectAtIndex(i));
							fork->setTag(i);
							if (doc[i]["fork_pos"].IsNumber())
							{
								fork->setZOrder((int)doc[i]["fork_pos"].GetDouble());
							}
							static_cast<CCLabelTTF*>(fork->getChildByTag(0))->setString(doc[i]["fork_item"].GetString());
							__fork_menu->addChild(fork);
							fork->setPosition(ccp(fork_size.width, top_fork_pos - i * fork_size.height * 1.1f));
						}
					}
				}
			}
			break;
		} while (0);
	}


	//对话
	if (v.HasMember("DG") && v["DG"].IsString())
	{
		if (v.HasMember("NA") && v["NA"].IsString())
		{
			__name->setString(v["NA"].GetString());
			if (!__name->getParent()->isVisible())
			{
				__name->getParent()->setVisible(true);
			}
		}
		else
		{
			__name->getParent()->setVisible(false);
		}
		__dialog->setTypeString(CCString::createWithFormat("%s", v["DG"].GetString()));
		if (!__dialog->getParent()->isVisible())
		{
			__dialog->getParent()->setVisible(true);
		}
	}
	else
	{
		__dialog->setTypeString(CCString::create(""));
		__dialog->getParent()->setVisible(false);
		__name->getParent()->setVisible(false);
	}

	__offset = 1;
	if (v.HasMember("NE") && v["NE"].IsNumber())
	{
		__offset = (int)v["NE"].GetDouble();
	}
}