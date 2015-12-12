#include "TopwoLabelType.h"

//utf8字符长度1-6，可以根据每个字符第一个字节判断整个字符长度
//0xxxxxxx
//110xxxxx 10xxxxxx
//1110xxxx 10xxxxxx 10xxxxxx
//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//
//定义查找表，长度256，表中的数值表示以此为起始字节的utf8字符长度
unsigned char utf8_look_for_table[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};
#define UTFLEN(x)  utf8_look_for_table[(x)]
// 计算str字符数目
int TopwoLabelType::getUtf8Length(char *str)
{
	int clen = strlen(str);
	int len = 0;

	for (char *ptr = str; *ptr != 0 && len<clen; len++, ptr += UTFLEN((unsigned char)*ptr));

	return len;
}
//get子串
CCString* TopwoLabelType::subUtfString(char *str, unsigned int start, unsigned int end)
{
	int len = getUtf8Length(str);

	if (start >= len) return NULL;
	if (end > len) end = len;

	char *sptr = str;
	for (int i = 0; i < start; ++i, sptr += UTFLEN((unsigned char)*sptr));

	char *eptr = sptr;
	for (int i = start; i < end; ++i, eptr += UTFLEN((unsigned char)*eptr));

	int retLen = eptr - sptr;
	char *retStr = (char*)malloc(retLen + 1);
	memcpy(retStr, sptr, retLen);
	retStr[retLen] = 0;

	CCString* retccstr = NULL;
	if (retStr)
	{
		retccstr = CCString::create(retStr);
		free(retStr);
	}

	return retccstr;
}

TopwoLabelType::TopwoLabelType()
:__str(NULL)
, __line_width(0.0f)
, __type_char_sum(0)
, __type_char_num(0)
, __is_show_all(false)
, __callbackListener(NULL)
, __callbackfunc(NULL)
{
}

TopwoLabelType::~TopwoLabelType()
{
	__str->release();
}

bool TopwoLabelType::init()
{
	if (!CCLabelBMFont::init())
	{
		return false;
	}
	__str = CCString::create("");
	__str->retain();
	return true;
}

void TopwoLabelType::setTypeString(CCString *str, twfloat dlg_width, twfloat interval)
{
	//存储要打印的那段话
	*__str = *str;
	//行宽
	__line_width = dlg_width;
	//这段话总字符数
	__type_char_sum = getUtf8Length(const_cast<char*>(__str->getCString()));

	//一行字符串最小个数
	twint min_char_count = (twint)(__line_width / this->getConfiguration()->m_nInfoSize);

	CCString *sub = NULL;//存储裁剪的一段话
	twint sub_start = 0;//裁剪的开始位置
	twint line_break_count = 0;//裁剪的次数
	twint i = min_char_count;//裁剪的结束位置
	while ((i <= __type_char_sum) && (sub = subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//超过行宽
			sub = subUtfString(const_cast<char*>(str->getCString()), 0, i);
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
	__type_char_sum = getUtf8Length(const_cast<char*>(__str->getCString()));

	if (interval > -0.00001f&&interval < 0.00001f)
	{
		showAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoLabelType::typing), interval, __type_char_sum, 0);
	}
}

//设置打完一句话后的回调函数
void TopwoLabelType::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//直接全部显示出来
void TopwoLabelType::showAll()
{
	if (__is_show_all)
	{
		return;
	}
	__is_show_all = true;
	this->setString(__str->getCString());
}

void TopwoLabelType::typing(float f)
{
	//已经全部显示，取消计划
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelType::typing));
		//回调
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//排除格式符
	char ch = 0;
	for (__type_char_num++; sub = subUtfString(const_cast<char*>(__str->getCString()), 0, __type_char_num); __type_char_num++)
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
