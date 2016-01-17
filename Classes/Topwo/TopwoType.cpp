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

	//开启解析
	openAnalyze(0);
}

//第一帧计算打字内容
void TopwoType::analyzeTypeString(float f)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();

	//一行字符串最小个数
	twuint min_char_count = (twuint)(__type_size.width / this->getTypedFontSize());

	CCString* str = CCString::create(__type_str->getCString());
	CCString *sub = NULL;//存储裁剪的一段话
	twint sub_start = 0;//裁剪的开始位置
	twint line_break_count = 0;//裁剪的次数
	twuint i = min_char_count;//裁剪的结束位置
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setTypedString(sub->getCString());
		if (this->getTypedStringContentSize().width > __type_size.width)
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
	this->setTypedString("");

	//重新获取这段话总字符数
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	if ((__type_interval > -0.00001f && __type_interval < 0.00001f) || (!__type_char_sum))
	{
		typeAll();
	}
	else
	{
		this->openTypeLoop( __type_interval, __type_char_sum, 0);
	}
}
//打字回调
void TopwoType::typing(float f)
{
	//已经全部显示，取消计划
	if (__is_type_all || __type_char_num >= __type_char_sum - 1)
	{
		this->closeTypeLoop();
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
			this->setTypedString(sub->getCString());
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
	this->setTypedString(__type_str->getCString());
	//回调
	if (__callbackListener&&__callbackfunc)
		(__callbackListener->*__callbackfunc)();
}
//TopwoTypeBMFont
TopwoTypeBMFont::TopwoTypeBMFont()
{
}

TopwoTypeBMFont::~TopwoTypeBMFont()
{
}

bool TopwoTypeBMFont::init(const char* fntfile)
{
	if (!initWithString("", fntfile))
	{
		return false;
	}
	return true;
}
TopwoTypeBMFont* TopwoTypeBMFont::create(const char* fntfile)
{
	TopwoTypeBMFont *pRet = new TopwoTypeBMFont();
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
//解析要进行打字的字符串
void TopwoTypeBMFont::analyzeTypeStringSelf(float f)
{
	TopwoType::analyzeTypeString(f);
}
//打字回调
void TopwoTypeBMFont::typingSelf(float f)
{
	TopwoType::typing(f);
}
//开启解析
void TopwoTypeBMFont::openAnalyze(float delay)
{
	this->scheduleOnce(schedule_selector(TopwoTypeBMFont::analyzeTypeStringSelf), delay);
}
//开启打字循环
void TopwoTypeBMFont::openTypeLoop(float interval, unsigned int repeat, float delay)
{
	this->schedule(schedule_selector(TopwoTypeBMFont::typingSelf), interval, repeat, delay);
}
//关闭打字循环
void TopwoTypeBMFont::closeTypeLoop()
{
	this->unschedule(schedule_selector(TopwoTypeBMFont::typingSelf));
}
//设置打出来的字符串
void TopwoTypeBMFont::setTypedString(const char* typed_string)
{
	this->setString(typed_string);
}
//获取打出来的字符串内容的大小
CCSize TopwoTypeBMFont::getTypedStringContentSize()
{
	return this->getContentSize();
}
//获取字体的大小
float TopwoTypeBMFont::getTypedFontSize()
{
	return this->getConfiguration()->m_nInfoSize;
}

//LabelTTF
TopwoTypeTTF::TopwoTypeTTF()
{
}

TopwoTypeTTF::~TopwoTypeTTF()
{
}

bool TopwoTypeTTF::init(const char* fntfile, float fontSize)
{
	if (!initWithString("", fntfile, fontSize))
	{
		return false;
	}
	return true;
}
TopwoTypeTTF* TopwoTypeTTF::create(const char* fntfile, float fontSize)
{
	TopwoTypeTTF *pRet = new TopwoTypeTTF();
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
//解析要进行打字的字符串
void TopwoTypeTTF::analyzeTypeStringSelf(float f)
{
	TopwoType::analyzeTypeString(f);
}
//打字回调
void TopwoTypeTTF::typingSelf(float f)
{
	TopwoType::typing(f);
}
//开启解析
void TopwoTypeTTF::openAnalyze(float delay)
{
	this->scheduleOnce(schedule_selector(TopwoTypeTTF::analyzeTypeStringSelf), delay);
}
//开启打字循环
void TopwoTypeTTF::openTypeLoop(float interval, unsigned int repeat, float delay)
{
	this->schedule(schedule_selector(TopwoTypeTTF::typingSelf), interval, repeat, delay);
}
//关闭打字循环
void TopwoTypeTTF::closeTypeLoop()
{
	this->unschedule(schedule_selector(TopwoTypeTTF::typingSelf));
}
//设置打出来的字符串
void TopwoTypeTTF::setTypedString(const char* typed_string)
{
	this->setString(typed_string);
}
//获取当前内容的大小
CCSize TopwoTypeTTF::getTypedStringContentSize()
{
	return this->getContentSize();
}
//获取字体的大小
float TopwoTypeTTF::getTypedFontSize()
{
	return this->getFontSize();
}