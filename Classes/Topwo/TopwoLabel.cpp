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
	//�洢Ҫ��ӡ���Ƕλ�
	*__str = *str;
	//�п�
	__line_width = line_width;
	//��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	//һ���ַ�����С����
	twint min_char_count = (twint)(__line_width / this->getConfiguration()->m_nInfoSize);

	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//�����п�
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

	//���
	this->setString("");

	//���»�ȡ��λ����ַ���
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

//���ô���һ�仰��Ļص�����
void TopwoLabelBMFont::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//ֱ��ȫ����ʾ����
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
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelBMFont::typing));
		//�ص�
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//�ų���ʽ��
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

	//�����ַ�ȫ������
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
	//�洢Ҫ��ӡ���Ƕλ�
	*__str = *str;
	//�п�
	__line_width = line_width;
	//��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__str->getCString()));

	//һ���ַ�����С����
	twint min_char_count = (twint)(__line_width / this->getFontSize());

	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __line_width)
		{//�����п�
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

	//���
	this->setString("");

	//���»�ȡ��λ����ַ���
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

//���ô���һ�仰��Ļص�����
void TopwoLabelTTF::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//ֱ��ȫ����ʾ����
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
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_show_all)
	{
		this->unschedule(schedule_selector(TopwoLabelTTF::typing));
		//�ص�
		if (__callbackListener&&__callbackfunc)
			(__callbackListener->*__callbackfunc)();
		return;
	}

	CCString *sub = NULL;

	//�ų���ʽ��
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

	//�����ַ�ȫ������
	if (__type_char_num >= __type_char_sum)
	{
		__is_show_all = true;
	}
}