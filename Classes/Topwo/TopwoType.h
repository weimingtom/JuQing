#ifndef __TOPWO_TYPE_H__
#define __TOPWO_TYPE_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;

//������
class TopwoType : public CCNode
{
public:
	enum TypeLabelStyle{
		LABEL_TTF,
		LABEL_BMFONT
	};
	TopwoType();
	virtual ~TopwoType();
	virtual bool init() override;
	CREATE_FUNC(TopwoType);

	CCNode* createTypedLabel(TypeLabelStyle style, const char* fntfile, float fontSize);

	//������ʾ�����С
	void setTypeSize(CCSize size);
	//���ô��ּ��ʱ��
	void setTypeInterval(twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//���ô��ֵ��ַ���
	virtual void setTypeString(CCString *str);

	//ֱ��ȫ����ʾ����
	virtual void typeAll();
protected:
	//��һ֡����Ҫ��ӡ���ַ�������
	virtual void updateOnce(float f);

	//���ֻص�
	virtual void typing(float f);

	TypeLabelStyle __label_style;//����
	CCLabelProtocol* __label;//��ǩ
	CCSize __type_size;//���������С
	float __type_interval;//���ʱ��
	CCString* __type_str;//��ǩ����
	twuint __type_char_sum;//��ӡ���ַ���
	twuint __type_char_num;//��ӡ���ַ���
	bool __is_type_all;//�Ƿ���ʾ������

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
#endif  //__TOPWO_TYPE_H__