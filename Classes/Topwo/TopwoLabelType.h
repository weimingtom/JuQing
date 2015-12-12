#ifndef __YIEYOTYPING_H__
#define __YIEYOTYPING_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//������
class TopwoLabelType:public CCLabelBMFont
{
public:
	TopwoLabelType();
	virtual ~TopwoLabelType();

	//���캯��
	CREATE_FUNC(TopwoLabelType);

	//��ʼ����
	virtual bool init();

	//���ô��ֵ��ַ���,t���ּ��ʱ��
	void setTypeString(CCString *str, twfloat dlg_width, twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//ֱ��ȫ����ʾ����
	void showAll();

	//���ֻص�
	void typing(float f);

	// ����str�ַ���Ŀ
	int getUtf8Length(char *str);
	//get�Ӵ�
	CCString* subUtfString(char *str, unsigned int start, unsigned int end);

private:
	CCString* __str;
	twfloat __line_width;//һ���ַ������
	twuint __type_char_sum;//��ӡ���ַ���
	twuint __type_char_num;//��ӡ���ַ���
	twbool __is_show_all;//�Ƿ���ʾ������

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};

#endif  //__YIEYOTYPING_H__