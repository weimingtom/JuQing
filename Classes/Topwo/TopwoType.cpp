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

	this->scheduleOnce(schedule_selector(TopwoType::updateOnce), 0);
}
void TopwoType::updateOnce(float f)
{
	TopwoTools* topwo_tools = Topwo::getInstance()->getTopwoTools();

	//һ���ַ�����С����
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
	CCString *sub = NULL;//�洢�ü���һ�λ�
	twint sub_start = 0;//�ü��Ŀ�ʼλ��
	twint line_break_count = 0;//�ü��Ĵ���
	twuint i = min_char_count;//�ü��Ľ���λ��
	while ((i <= __type_char_sum) && (sub = topwo_tools->subUtfString(const_cast<char*>(str->getCString()), sub_start, i + 1)))
	{
		__label->setString(sub->getCString());
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
	__label->setString("");

	//���»�ȡ��λ����ַ���
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

//���ֻص�
void TopwoType::typing(float f)
{
	//�Ѿ�ȫ����ʾ��ȡ���ƻ�
	if (__is_type_all || __type_char_num >= __type_char_sum - 1)
	{
		this->unschedule(schedule_selector(TopwoType::typing));
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
			__label->setString(sub->getCString());
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
	__label->setString(__type_str->getCString());
	//�ص�
	if (__callbackListener&&__callbackfunc)
		(__callbackListener->*__callbackfunc)();
}
