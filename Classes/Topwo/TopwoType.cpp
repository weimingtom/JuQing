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
void TopwoType::setTypeString(CCString *str)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();
	//�洢Ҫ��ӡ���Ƕλ�
	*__type_str = *str;
	//��λ����ַ���
	__type_char_sum = topwo_tools->getUtf8Length(const_cast<char*>(__type_str->getCString()));

	__type_char_num = 0;

	__is_type_all = false;

	//��������
	openAnalyze(0);
}

//��һ֡�����������
void TopwoType::analyzeTypeString(float f)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();

	//һ���ַ�����С����
	twuint min_char_count = (twuint)(__type_size.width / this->getTypedFontSize());

	CCString* str = CCString::create(__type_str->getCString());
	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twuint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		this->setTypedString(sub->getCString());
		if (this->getTypedStringContentSize().width > __type_size.width)
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
	this->setTypedString("");

	//���»�ȡ��λ����ַ���
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
//���ֻص�
void TopwoType::typing(float f)
{
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_type_all || __type_char_num >= __type_char_sum - 1)
	{
		this->closeTypeLoop();
		typeAll();
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
			this->setTypedString(sub->getCString());
			break;
		}
	}
}
//ֱ��ȫ����ʾ����
void TopwoType::typeAll()
{
	if (__is_type_all)
	{
		return;
	}
	__is_type_all = true;
	this->setTypedString(__type_str->getCString());
	//�ص�
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
//����Ҫ���д��ֵ��ַ���
void TopwoTypeBMFont::analyzeTypeStringSelf(float f)
{
	TopwoType::analyzeTypeString(f);
}
//���ֻص�
void TopwoTypeBMFont::typingSelf(float f)
{
	TopwoType::typing(f);
}
//��������
void TopwoTypeBMFont::openAnalyze(float delay)
{
	this->scheduleOnce(schedule_selector(TopwoTypeBMFont::analyzeTypeStringSelf), delay);
}
//��������ѭ��
void TopwoTypeBMFont::openTypeLoop(float interval, unsigned int repeat, float delay)
{
	this->schedule(schedule_selector(TopwoTypeBMFont::typingSelf), interval, repeat, delay);
}
//�رմ���ѭ��
void TopwoTypeBMFont::closeTypeLoop()
{
	this->unschedule(schedule_selector(TopwoTypeBMFont::typingSelf));
}
//���ô�������ַ���
void TopwoTypeBMFont::setTypedString(const char* typed_string)
{
	this->setString(typed_string);
}
//��ȡ��������ַ������ݵĴ�С
CCSize TopwoTypeBMFont::getTypedStringContentSize()
{
	return this->getContentSize();
}
//��ȡ����Ĵ�С
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
//����Ҫ���д��ֵ��ַ���
void TopwoTypeTTF::analyzeTypeStringSelf(float f)
{
	TopwoType::analyzeTypeString(f);
}
//���ֻص�
void TopwoTypeTTF::typingSelf(float f)
{
	TopwoType::typing(f);
}
//��������
void TopwoTypeTTF::openAnalyze(float delay)
{
	this->scheduleOnce(schedule_selector(TopwoTypeTTF::analyzeTypeStringSelf), delay);
}
//��������ѭ��
void TopwoTypeTTF::openTypeLoop(float interval, unsigned int repeat, float delay)
{
	this->schedule(schedule_selector(TopwoTypeTTF::typingSelf), interval, repeat, delay);
}
//�رմ���ѭ��
void TopwoTypeTTF::closeTypeLoop()
{
	this->unschedule(schedule_selector(TopwoTypeTTF::typingSelf));
}
//���ô�������ַ���
void TopwoTypeTTF::setTypedString(const char* typed_string)
{
	this->setString(typed_string);
}
//��ȡ��ǰ���ݵĴ�С
CCSize TopwoTypeTTF::getTypedStringContentSize()
{
	return this->getContentSize();
}
//��ȡ����Ĵ�С
float TopwoTypeTTF::getTypedFontSize()
{
	return this->getFontSize();
}