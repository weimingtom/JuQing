#ifndef __TOPWO_LABEL_H__
#define __TOPWO_LABEL_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//������
class TopwoLabelBMFont :public CCLabelBMFont
{
public:
	TopwoLabelBMFont();
	virtual ~TopwoLabelBMFont();

	//���캯��
	static TopwoLabelBMFont* create(const char* fntfile);

	//��ʼ����
	virtual bool init(const char* fntfile);

	//���ô��ֵ��ַ���,t���ּ��ʱ��
	void setTypeString(CCString *str, twfloat line_width, twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//ֱ��ȫ����ʾ����
	void showAll();

private:
	//���ֻص�
	void typing(float f);

	CCString* __str;
	twfloat __line_width;//һ���ַ������
	twuint __type_char_sum;//��ӡ���ַ���
	twuint __type_char_num;//��ӡ���ַ���
	twbool __is_show_all;//�Ƿ���ʾ������

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};

class TopwoLabelTTF :public CCLabelTTF
{
public:
	TopwoLabelTTF();
	virtual ~TopwoLabelTTF();

	//���캯��
	static TopwoLabelTTF* create(const char* fntfile, float fontSize);

	//��ʼ����
	virtual bool init(const char* fntfile, float fontSize);

	//���ô��ֵ��ַ���,t���ּ��ʱ��
	void setTypeString(CCString *str, twfloat line_width, twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//ֱ��ȫ����ʾ����
	void showAll();

private:
	//���ֻص�
	void typing(float f);

	CCString* __str;
	twfloat __line_width;//һ���ַ������
	twuint __type_char_sum;//��ӡ���ַ���
	twuint __type_char_num;//��ӡ���ַ���
	twbool __is_show_all;//�Ƿ���ʾ������

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
#endif  //__TOPWO_LABEL_H__