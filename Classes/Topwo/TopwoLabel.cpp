#include "TopwoLabel.h"
#include "Topwo.h"

//TopwoLabel
TopwoType::TopwoType()
:__type_str(NULL)
, __type_size(CCSizeZero)
, __type_interval(0.0f)
, __type_char_sum(0)
, __type_char_num(0)
, __is_type_all(false)
, __callbackListener(NULL)
, __callbackfunc(NULL)
{
}

TopwoType::~TopwoType()
{
	__type_str->release();
}

//������ʾ�����С
void TopwoType::setTypeSize(CCSize size)
{
	__type_size = size;
}
//���ô��ּ��ʱ��
void TopwoType::setTypeInterval(twfloat interval)
{
	__type_interval = interval;
}
//���ô���һ�仰��Ļص�����
void TopwoType::setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
}

//TopwoLabelBMFont
TopwoLabelBMFont::TopwoLabelBMFont()
{
}

TopwoLabelBMFont::~TopwoLabelBMFont()
{
}

bool TopwoLabelBMFont::init(const char* fntfile)
{
	if (!CCLabelBMFont::initWithString("", fntfile))
	{
		return false;
	}
	__type_str = CCString::create("");
	__type_str->retain();
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
void TopwoLabelBMFont::setTypeString(CCString *str)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//�洢Ҫ��ӡ���Ƕλ�
	*__type_str = *str;
	//��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	//һ���ַ�����С����
	twint min_char_count = (twint)(__type_size.width / this->getConfiguration()->m_nInfoSize);

	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __type_size.width)
		{//�����п�
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

	//���
	this->setString("");

	//���»�ȡ��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	if (__type_interval > -0.00001f && __type_interval < 0.00001f)
	{
		typeAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoLabelBMFont::typing), __type_interval, __type_char_sum, 0);
	}
}

//ֱ��ȫ����ʾ����
void TopwoLabelBMFont::typeAll()
{
	if (__is_type_all)
	{
		return;
	}
	__is_type_all = true;
	this->setString(__type_str->getCString());
}

void TopwoLabelBMFont::typing(float f)
{
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_type_all)
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
	for (__type_char_num++; sub = Topwo::getInstance()->getTopwoTools()->subUtfString(const_cast<char*>(__type_str->getCString()), 0, __type_char_num); __type_char_num++)
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
		__is_type_all = true;
	}
}

//LabelTTF
TopwoLabelTTF::TopwoLabelTTF()
{
}

TopwoLabelTTF::~TopwoLabelTTF()
{
	__type_str->release();
}

bool TopwoLabelTTF::init(const char* fntfile, float fontSize)
{
	if (!TopwoLabelTTF::initWithString("", fntfile, fontSize))
	{
		return false;
	}
	__type_str = CCString::create("");
	__type_str->retain();
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
void TopwoLabelTTF::setTypeString(CCString *str)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//�洢Ҫ��ӡ���Ƕλ�
	*__type_str = *str;
	//��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	//һ���ַ�����С����
	twint min_char_count = (twint)(__type_size.width / this->getFontSize());

	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setString(sub->getCString());
		if (this->getContentSize().width > __type_size.width)
		{//�����п�
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

	//���
	this->setString("");

	//���»�ȡ��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	if (__type_interval > -0.00001f && __type_interval < 0.00001f)
	{
		typeAll();
	}
	else
	{
		this->schedule(schedule_selector(TopwoLabelTTF::typing), __type_interval, __type_char_sum, 0);
	}
}

//ֱ��ȫ����ʾ����
void TopwoLabelTTF::typeAll()
{
	if (__is_type_all)
	{
		return;
	}
	__is_type_all = true;
	this->setString(__type_str->getCString());
}

void TopwoLabelTTF::typing(float f)
{
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_type_all)
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
	for (__type_char_num++; sub = Topwo::getInstance()->getTopwoTools()->subUtfString(const_cast<char*>(__type_str->getCString()), 0, __type_char_num); __type_char_num++)
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
		__is_type_all = true;
	}
}