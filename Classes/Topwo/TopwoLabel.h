#ifndef __TOPWO_LABEL_H__
#define __TOPWO_LABEL_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//������
class TopwoType
{
public:
	TopwoType();
	virtual ~TopwoType();
	//������ʾ�����С
	void setTypeSize(CCSize size);
	//���ô��ּ��ʱ��
	void setTypeInterval(twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);
protected:

	CCSize __type_size;//���������С
	float __type_interval;//���ʱ��
	CCString* __type_str;
	twuint __type_char_sum;//��ӡ���ַ���
	twuint __type_char_num;//��ӡ���ַ���
	bool __is_type_all;//�Ƿ���ʾ������

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
class TopwoLabelBMFont : public CCLabelBMFont, public TopwoType
{
public:
	TopwoLabelBMFont();
	virtual ~TopwoLabelBMFont();

	//���캯��
	static TopwoLabelBMFont* create(const char* fntfile);

	//��ʼ����
	virtual bool init(const char* fntfile);

	//���ô��ֵ��ַ���
	virtual void setTypeString(CCString *str);

	//ֱ��ȫ����ʾ����
	virtual void typeAll();
	//���ֻص�
	virtual void typing(float f);
protected:
};

class TopwoLabelTTF :public CCLabelTTF, public TopwoType
{
public:
	TopwoLabelTTF();
	virtual ~TopwoLabelTTF();

	//���캯��
	static TopwoLabelTTF* create(const char* fntfile, float fontSize);

	//��ʼ����
	virtual bool init(const char* fntfile, float fontSize);

	//���ô��ֵ��ַ���,t���ּ��ʱ��
	virtual void setTypeString(CCString *str);

	//ֱ��ȫ����ʾ����
	virtual void typeAll();

	//���ֻص�
	virtual void typing(float f);
protected:
};
#endif  //__TOPWO_LABEL_H__