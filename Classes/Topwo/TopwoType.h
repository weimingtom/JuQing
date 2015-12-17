#ifndef __TOPWO_TYPE_H__
#define __TOPWO_TYPE_H__
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

	//���ô��ֵ��ַ���
	virtual void setTypeString(CCString *str);
	//ֱ��ȫ����ʾ����
	virtual void typeAll() = 0;
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
class TopwoTypeBMFont : public CCLabelBMFont, public TopwoType
{
public:
	TopwoTypeBMFont();
	virtual ~TopwoTypeBMFont();

	//���캯��
	static TopwoTypeBMFont* create(const char* fntfile);

	//��ʼ����
	virtual bool init(const char* fntfile);

	//���ô��ֵ��ַ���
	virtual void setTypeString(CCString *str);

	//ֱ��ȫ����ʾ����
	virtual void typeAll();
protected:
	//���ֻص�
	virtual void typing(float f);
};

class TopwoTypeTTF :public CCLabelTTF, public TopwoType
{
public:
	TopwoTypeTTF();
	virtual ~TopwoTypeTTF();

	//���캯��
	static TopwoTypeTTF* create(const char* fntfile, float fontSize);

	//��ʼ����
	virtual bool init(const char* fntfile, float fontSize);

	//���ô��ֵ��ַ���,t���ּ��ʱ��
	virtual void setTypeString(CCString *str);

	//ֱ��ȫ����ʾ����
	virtual void typeAll();
protected:
	//���ֻص�
	virtual void typing(float f);
};
#endif  //__TOPWO_TYPE_H__