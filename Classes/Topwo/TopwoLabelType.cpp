#include "TopwoLabelType.h"

//utf8�ַ�����1-6�����Ը���ÿ���ַ���һ���ֽ��ж������ַ�����
//0xxxxxxx
//110xxxxx 10xxxxxx
//1110xxxx 10xxxxxx 10xxxxxx
//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//
//������ұ�����256�����е���ֵ��ʾ�Դ�Ϊ��ʼ�ֽڵ�utf8�ַ�����
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
// ����str�ַ���Ŀ
int TopwoLabelType::getUtf8Length(char *str)
{
	int clen = strlen(str);
	int len = 0;

	for (char *ptr = str; *ptr != 0 && len<clen; len++, ptr += UTFLEN((unsigned char)*ptr));

	return len;
}
//get�Ӵ�
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
	//�洢Ҫ��ӡ���Ƕλ�
	*__str = *str;
	//�п�
	__line_width = dlg_width;
	//��λ����ַ���
	__type_char_sum = getUtf8Length(const_cast<char*>(__str->getCString()));

	//һ���ַ�����С����
	twint min_char_count = (twint)(__line_width / this->getConfiguration()->m_nInfoSize);

	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//�����п�
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

	//���
	this->setString("");

	//���»�ȡ��λ����ַ���
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

//���ô���һ�仰��Ļص�����
void TopwoLabelType::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//ֱ��ȫ����ʾ����
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
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelType::typing));
		//�ص�
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//�ų���ʽ��
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

	//�����ַ�ȫ������
	if (__type_char_num >= __type_char_sum)
	{
		__is_show_all = true;
	}
}
