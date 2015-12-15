#include "TopwoLabel.h"
#include "Topwo.h"

TopwoLabelBMFont::TopwoLabelBMFont()
:__str(NULL)
, __line_width(0.0f)
, __type_char_sum(0)
, __type_char_num(0)
, __is_show_all(false)
, __callbackListener(NULL)
, __callbackfunc(NULL)
{
}

TopwoLabelBMFont::~TopwoLabelBMFont()
{
	__str->release();
}

bool TopwoLabelBMFont::init(const char* fntfile)
{
	if (!CCLabelBMFont::initWithString("", fntfile))
	{
		return false;
	}
	__str = CCString::create("");
	__str->retain();
	return true;
}
TopwoLabelBMFont* TopwoLabelBMFont::create(const char* fntfile)
{
	TopwoLabelBMFont *pRet = new TopwoLabelBMFont();
	if (pRet && pRet->init(fntfile))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
void TopwoLabelBMFont::setTypeString(CCString *str, twfloat line_width, twfloat interval)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//存储要打印的那段话
	*__str = *str;
	//行宽
	__line_width = line_width;
	//这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	//一行字符串最小个数
	twint min_char_count = (twint)(__line_width / this->getConfiguration()->m_nInfoSize);

	CCString *sub = NULL;//存储裁剪的一段话
	twint sub_start = 0;//裁剪的开始位置
	twint line_break_count = 0;//裁剪的次数
	twint i = min_char_count;//裁剪的结束位置
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//超过行宽
			sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), 0, i);
			__str->m_sString.insert(strlen(sub->getCString()) + line_break_count, 1, '\n');
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
	this->setString("");

	//重新获取这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	if (interval > -0.00001f&&interval < 0.00001f)
	{
		showAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoLabelBMFont::typing), interval, __type_char_sum, 0);
	}
}

//设置打完一句话后的回调函数
void TopwoLabelBMFont::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//直接全部显示出来
void TopwoLabelBMFont::showAll()
{
	if (__is_show_all)
	{
		return;
	}
	__is_show_all = true;
	this->setString(__str->getCString());
}

void TopwoLabelBMFont::typing(float f)
{
	//已经全部显示，取消计划
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelBMFont::typing));
		//回调
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//排除格式符
	char ch = 0;
	for (__type_char_num++; sub = Topwo::getInstance()->getTopwoTools()->subUtfString(const_cast<char*>(__str->getCString()), 0, __type_char_num); __type_char_num++)
	{
		ch = sub->m_sString.at(sub->m_sString.length() - 1);
		if (/*ch != '\n' &&*/
			ch != '\t' &&
			ch != ' ')
		{
			this->setString(sub->getCString());
			break;
		}
	}

	//所有字符全部打完
	if (__type_char_num >= __type_char_sum)
	{
		__is_show_all = true;
	}
}

//LabelTTF
TopwoLabelTTF::TopwoLabelTTF()
:__str(NULL)
, __line_width(0.0f)
, __type_char_sum(0)
, __type_char_num(0)
, __is_show_all(false)
, __callbackListener(NULL)
, __callbackfunc(NULL)
{
}

TopwoLabelTTF::~TopwoLabelTTF()
{
	__str->release();
}

bool TopwoLabelTTF::init(const char* fntfile, float fontSize)
{
	if (!TopwoLabelTTF::initWithString("", fntfile, fontSize))
	{
		return false;
	}
	__str = CCString::create("");
	__str->retain();
	return true;
}
TopwoLabelTTF* TopwoLabelTTF::create(const char* fntfile, float fontSize)
{
	TopwoLabelTTF *pRet = new TopwoLabelTTF();
	if (pRet && pRet->init(fntfile, fontSize))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
void TopwoLabelTTF::setTypeString(CCString *str, twfloat line_width, twfloat interval)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//存储要打印的那段话
	*__str = *str;
	//行宽
	__line_width = line_width;
	//这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	//一行字符串最小个数
	twint min_char_count = (twint)(__line_width / this->getFontSize());

	CCString *sub = NULL;//存储裁剪的一段话
	twint sub_start = 0;//裁剪的开始位置
	twint line_break_count = 0;//裁剪的次数
	twint i = min_char_count;//裁剪的结束位置
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//超过行宽
			sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), 0, i);
			__str->m_sString.insert(strlen(sub->getCString()) + line_break_count, 1, '\n');
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
	this->setString("");

	//重新获取这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	if (interval > -0.00001f&&interval < 0.00001f)
	{
		showAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoLabelTTF::typing), interval, __type_char_sum, 0);
	}
}

//设置打完一句话后的回调函数
void TopwoLabelTTF::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//直接全部显示出来
void TopwoLabelTTF::showAll()
{
	if (__is_show_all)
	{
		return;
	}
	__is_show_all = true;
	this->setString(__str->getCString());
}

void TopwoLabelTTF::typing(float f)
{
	//已经全部显示，取消计划
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelTTF::typing));
		//回调
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//排除格式符
	char ch = 0;
	for (__type_char_num++; sub = Topwo::getInstance()->getTopwoTools()->subUtfString(const_cast<char*>(__str->getCString()), 0, __type_char_num); __type_char_num++)
	{
		ch = sub->m_sString.at(sub->m_sString.length() - 1);
		if (/*ch != '\n' &&*/
			ch != '\t' &&
			ch != ' ')
		{
			this->setString(sub->getCString());
			break;
		}
	}

	//所有字符全部打完
	if (__type_char_num >= __type_char_sum)
	{
		__is_show_all = true;
	}
}