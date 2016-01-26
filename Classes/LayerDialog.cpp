#include "LayerDialog.h"
#include "Topwo.h"

LayerDialog::LayerDialog()
:__fork_arr(NULL)
, __pListener(NULL)
, __pSelector(NULL)
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

	setTouchEnabled(true);  //开启触摸响应

	return true;
}
void LayerDialog::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
LayerDialog* LayerDialog::createWith(int start_id, int end_id, CCObject* target, SEL_CallFunc selector)
{
	LayerDialog* me = create();
	if (!me)
	{
		return NULL;
	}
	me->__start_id = start_id;
	me->__end_id = end_id;

	me->__pListener = target;
	me->__pSelector = selector;

	me->analyzeDialog(start_id);

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
	__bg = CCSprite::create("images/bg_black.png");
	__bg->setPosition(ccp(vo.x + vs.width / 2.0f, vo.y + vs.height / 2.0f));
	this->addChild(__bg, 0);

	//立绘
	__vertical_drawing = CCSprite::create();
	__vertical_drawing->setPosition(ccp(vo.x + vs.width / 2.0f, vo.y + vs.height - 50.0f));
	this->addChild(__vertical_drawing, 2);

	//对话框背景
	CCSprite* bg_dialog = CCSprite::create("images/LayerDialog_bg_dialog.png");
	CCSize bg_dialog_size = bg_dialog->getContentSize();
	bg_dialog->setPosition(ccp(vo.x + vs.width / 2.0f, vo.y + bg_dialog_size.height / 2.0f));
	this->addChild(bg_dialog, 5);

	//人物名字背景
	CCSprite* bg_name = CCSprite::create("images/LayerDialog_bg_name.png");
	CCSize bg_name_size = bg_name->getContentSize();
	bg_name->setPosition(ccp(vo.x + bg_dialog->getPositionX() - bg_dialog_size.width / 2.0f + bg_name_size.width / 2.0f, vo.y + bg_dialog_size.height + bg_name_size.height / 2.0f + 5.0f));
	this->addChild(bg_name, 5);

	//名字
	__name = CCLabelTTF::create("Name", "fonts/ttfs/MicrosoftYaHei.ttf", 32);
	__name->setPosition(ccp(bg_name_size.width / 2.0f, bg_name_size.height / 2.0f));
	bg_name->addChild(__name, 0, 0);

	//对话
	CCSize type_size = bg_dialog_size - CCSizeMake(80.0f, 40.0f);
	__dialog = TopwoTypeTTF::create("fonts/ttfs/MicrosoftYaHei.ttf", 28);
	__dialog->setTypeSize(type_size);
	__dialog->setTypeInterval(0.1f);
	__dialog->setTypeFinishCallback(this, callfunc_selector(LayerDialog::typedCallBack));

	__dialog->setAnchorPoint(ccp(0, 1.0f));
	__dialog->setPosition(ccp(bg_dialog_size.width / 2.0f - type_size.width / 2.0f, bg_dialog_size.height / 2.0f + type_size.height / 2.0f));
	bg_dialog->addChild(__dialog, 0, 0);

	return true;
}
void LayerDialog::removeFromParent()
{
	if (__pListener && __pSelector)
	{
		(__pListener->*__pSelector)();
	}
	CCLayer::removeFromParent();
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
		int next_id = __current_id + __offset;
		if (next_id > __end_id)
		{
			CCFadeOut* action_fade_out = CCFadeOut::create(0.5f);
			this->runAction(CCSequence::createWithTwoActions(action_fade_out, CCCallFunc::create(this, callfunc_selector(LayerDialog::removeFromParent))));
		}
		else
		{
			analyzeDialog(next_id);
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


void LayerDialog::menuCallbackFork(CCObject* pSender)
{
	__fork_menu->setVisible(false);
	__fork_menu->removeAllChildren();
	int fork_pos = static_cast<CCMenuItemImage*>(pSender)->getZOrder();
	int next_id = __current_id + fork_pos;
	if (next_id > __end_id)
	{
		CCFadeOut* action_fade_out = CCFadeOut::create(0.5f);
		this->runAction(CCSequence::createWithTwoActions(action_fade_out, CCCallFunc::create(this, callfunc_selector(LayerDialog::removeFromParent))));
	}
	else
	{
		analyzeDialog(next_id);
	}
}
void LayerDialog::typedCallBack()
{
	__is_typed_all = true;

	if (__fork_menu->getChildrenCount() > 0)
	{
		__fork_menu->setVisible(true);
	}
	rapidjson::Value& json_value = Topwo::getInstance()->getTopwoData()->getPlotDataFromJson(__current_id);
	if (json_value.HasMember("FA") && json_value["FA"].IsString())
	{
		do
		{
			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(json_value["FA"].GetString());
			CCLOG("doc HasParseError : %d", doc.HasParseError());
			CC_BREAK_IF(doc.HasParseError()); 
			for (int i = 0; i < (int)doc.Size(); i++)
			{
				if (doc[i].IsObject())
				{
					if (doc[i].HasMember("npc") && doc[i]["npc"].IsNumber() && doc[i].HasMember("favor") && doc[i]["favor"].IsNumber())
					{
						TopwoData* td = Topwo::getInstance()->getTopwoData();
						UserInfo* user_info = td->getUserInfo();
						int npc_id = (int)doc[i]["npc"].GetDouble();
						int npc_favor = (int)doc[i]["favor"].GetDouble();
						if (npc_id == user_info->getCurrentWooer())
						{
							user_info->setCurrentFavor(user_info->getCurrentFavor() + npc_favor);
						}
						DataNpc* npc_data = td->getDataNpcFromArray(npc_id);
						CCLOG("getFavorMax:%d", npc_data->getFavorMax());
					}
				}
			}
		} while (0);
	}
}
//解析一句对话
void LayerDialog::analyzeDialog(int index)
{
	__current_id = index;

	__is_typed_all = false;
	__vertical_drawing->setVisible(false);

	CCTexture2D* texture2d_bg = NULL;

	rapidjson::Value& json_value = Topwo::getInstance()->getTopwoData()->getPlotDataFromJson(index);

	if (json_value.HasMember("CG") && json_value["CG"].IsNumber())
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("images/CG_%d.jpg", (int)json_value["CG"].GetDouble())->getCString());
	}
	else
	{
		if (json_value.HasMember("BG") && json_value["BG"].IsNumber())
		{
			texture2d_bg = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("images/BG_%d.jpg", (int)json_value["BG"].GetDouble())->getCString());
		}
		if (json_value.HasMember("VE") && json_value["VE"].IsNumber() && json_value.HasMember("NA") && json_value["NA"].IsNumber())
		{
			int people_id = (int)json_value["NA"].GetDouble();
			int vertical_id = (int)json_value["VE"].GetDouble();
			if (people_id == 1 || people_id == 2)
			{
				people_id = vertical_id;
				vertical_id = 1;
			}
			CCTexture2D* texture2d_ve = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("images/VE_%d_%d.png", people_id, vertical_id)->getCString());
			if (texture2d_ve)
			{
				__vertical_drawing->setVisible(true);
				__vertical_drawing->initWithTexture(texture2d_ve);
				__vertical_drawing->setAnchorPoint(ccp(0.5f, 1.0f));
			}
		}
	}
	if (!texture2d_bg)
	{
		texture2d_bg = CCTextureCache::sharedTextureCache()->addImage("images/bg_black.png");
	}
	__bg->setTexture(texture2d_bg);

	if (json_value.HasMember("FO") && json_value["FO"].IsString())
	{
		__fork_menu->removeAllChildren();
		do
		{
			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(json_value["FO"].GetString());
			CCLOG("doc HasParseError : %d", doc.HasParseError());
			CC_BREAK_IF(doc.HasParseError());
			if (doc.IsArray())
			{
				int doc_size = doc.Size();
				int need = doc_size - __fork_arr->count();
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("images/btn_fork_0.png");
				CCSize fork_size = texture->getContentSize();
				while (need > 0)
				{
					CCMenuItemImage* fork = CCMenuItemImage::create("images/btn_fork_0.png", "images/btn_fork_1.png", this, menu_selector(LayerDialog::menuCallbackFork));
					CCLabelTTF* fork_content = CCLabelTTF::create("Fork Content", "fonts/atlas/MicrosoftYaHei.ttf", 28);
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
	if (json_value.HasMember("DG") && json_value["DG"].IsString())
	{
		if (json_value.HasMember("NA") && json_value["NA"].IsNumber())
		{
			int name_id = (int)json_value["NA"].GetDouble();
			DataNpc* npc_data = Topwo::getInstance()->getTopwoData()->getDataNpcFromArray(name_id);
			__name->setString(npc_data->getName()->getCString());
			if (!__name->getParent()->isVisible())
			{
				__name->getParent()->setVisible(true);
			}
		}
		else
		{
			__name->getParent()->setVisible(false);
		}
		__dialog->setTypeString(CCString::create(json_value["DG"].GetString()));
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
	if (json_value.HasMember("NE") && json_value["NE"].IsNumber())
	{
		__offset = (int)json_value["NE"].GetDouble();
	}
}