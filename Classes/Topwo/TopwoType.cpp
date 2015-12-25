#include "TopwoType.h"
#include "Topwo.h"

//TopwoLabel
TopwoType::TopwoType()
:__type_str(NULL)
, __type_size(CCSizeZero)
, __type_interval(0.0f)
, __callbackListener(NULL)
, __callbackfunc(NULL)
, __type_char_sum(0)
, __type_char_num(0)
, __is_type_all(false)
{
	__type_str = CCString::create("");
	__type_str->retain();
}

TopwoType::~TopwoType()
{
	__type_str->release();
}

bool TopwoType::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	return true;
}
CCNode* TopwoType::createTypedLabel(TypeLabelStyle style, const char* fntfile, float fontSize)
{
	__label_style = style;
	this->removeAllChildren();
	CCNode* node = NULL;
	if (__label_style == TypeLabelStyle::LABEL_TTF)
	{
		node = CCLabelTTF::create("", fntfile, fontSize);
		__label = static_cast<CCLabelTTF*>(node);
	}
	else if (__label_style == TypeLabelStyle::LABEL_BMFONT)
	{
		node = CCLabelBMFont::create("", fntfile);
		__label = static_cast<CCLabelBMFont*>(node);
	}
	this->addChild(node);
	return node;
}
//设置显示区域大小
void TopwoType::setTypeSize(CCSize size)
{
	__type_size = size;
}
//设置打字间隔时间
void TopwoType::setTypeInterval(twfloat interval)
{
	__type_interval = interval;
}
//设置打完一句话后的回调函数
void TopwoType::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}
void TopwoType::setTypeString(CCString *str)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//存储要打印的那段话
	*__type_str = *str;
	//这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	__type_char_num = 0;

	__is_type_all = false;

	this->scheduleOnce(schedule_selector(TopwoType::updateOnce), 0);
}
void TopwoType::updateOnce(float f)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();

	//一行字符串最小个数
	float font_size = 0;
	if (__label_style == TypeLabelStyle::LABEL_TTF)
	{
		font_size = static_cast<CCLabelTTF*>(__label)->getFontSize();
	}
	else if (__label_style == TypeLabelStyle::LABEL_BMFONT)
	{
		font_size = static_cast<CCLabelBMFont*>(__label)->getConfiguration()->m_nInfoSize;
	}
	twuint min_char_count = (twuint)(__type_size.width / font_size);

	CCString* str = CCString::create(__type_str->getCString());
	CCString *sub = NULL;//存储裁剪的一段话
	twint sub_start = 0;//裁剪的开始位置
	twint line_break_count = 0;//裁剪的次数
	twuint i = min_char_count;//裁剪的结束位置
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		__label->setString(sub->getCString());
		if (this->getContentSize().width > __type_size.width)
		{//超过行宽
			sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), 0, i);
			__type_str->m_sString.insert(strlen(sub->getCString()) + line_break_count, 1, '\n');
			sub_start = i;
			line_break_count++;
			i += min_char_count;
		}
		else
		{
			i++;
		}
	}

	//清空
	__label->setString("");

	//重新获取这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	if (__type_interval > -0.00001f && __type_interval < 0.00001f)
	{
		typeAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoType::typing), __type_interval, __type_char_sum, 0);
	}
}

//打字回调
void TopwoType::typing(float f)
{
	//已经全部显示，取消计划
	if (__is_type_all || __type_char_num >= __type_char_sum - 1)
	{
		this->unschedule(schedule_selector(TopwoType::typing));
		typeAll();
		return;
	}

	CCString *sub = NULL;

	//排除格式符
	char ch = 0;
	for (__type_char_num++; sub = Topwo::getInstance()->getTopwoTools()->subUtfString(const_cast<char*>(__type_str->getCString()), 0, __type_char_num); __type_char_num++)
	{
		ch = sub->m_sString.at(sub->m_sString.length() - 1);
		if (/*ch != '\n' &&*/
			ch != '\t' &&
			ch != ' ')
		{
			__label->setString(sub->getCString());
			break;
		}
	}
}

//直接全部显示出来
void TopwoType::typeAll()
{
	if (__is_type_all)
	{
		return;
	}
	__is_type_all = true;
	__label->setString(__type_str->getCString());
	//回调
	if (__callbackListener&&__callbackfunc)
		(__callbackListener->*__callbackfunc)();
}
