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

	//����Ҫ���д��ֵ��ַ���
	virtual void setTypeString(CCString *str);
	//������ʾ�����С
	void setTypeSize(CCSize size);
	//���ô��ּ��ʱ��
	void setTypeInterval(twfloat interval);
	//���ô���һ�仰��Ļص�����
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);
	//ֱ��ȫ�������
	virtual void typeAll();

	//���ô�������ַ���
	virtual void setTypedString(const char* typed_string) = 0;
	//��ȡ��������ַ������ݵĴ�С
	virtual CCSize getTypedStringContentSize() = 0;
	//��������
	virtual void openAnalyze(float delay) = 0;
	//��������ѭ��
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) = 0;
	//�رմ���ѭ��
	virtual void closeTypeLoop() = 0;
	//��ȡ����Ĵ�С
	virtual float getTypedFontSize() = 0;
protected:
	//����Ҫ���д��ֵ��ַ���
	virtual void analyzeTypeString(float f);
	//���ֻص�
	virtual void typing(float f);

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

	//��ʼ����
	virtual bool init(const char* fntfile);
	//���캯��
	static TopwoTypeBMFont* create(const char* fntfile);

	//���ô�������ַ���
	virtual void setTypedString(const char* typed_string) override;
	//��ȡ��������ַ������ݵĴ�С
	virtual CCSize getTypedStringContentSize() override;
	//��������
	virtual void openAnalyze(float delay) override;
	//��������ѭ��
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) override;
	//�رմ���ѭ��
	virtual void closeTypeLoop() override;
	//��ȡ����Ĵ�С
	virtual float getTypedFontSize() override;
protected:
	//����Ҫ���д��ֵ��ַ���
	virtual void analyzeTypeStringSelf(float f);
	//���ֻص�
	virtual void typingSelf(float f);
};

class TopwoTypeTTF :public CCLabelTTF, public TopwoType
{
public:
	TopwoTypeTTF();
	virtual ~TopwoTypeTTF();

	//��ʼ����
	virtual bool init(const char* fntfile, float fontSize);
	//���캯��
	static TopwoTypeTTF* create(const char* fntfile, float fontSize);

	//���ô�������ַ���
	virtual void setTypedString(const char* typed_string) override;
	//��ȡ��������ַ������ݵĴ�С
	virtual CCSize getTypedStringContentSize() override;
	//��������
	virtual void openAnalyze(float delay) override;
	//��������ѭ��
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) override;
	//�رմ���ѭ��
	virtual void closeTypeLoop() override;
	//��ȡ����Ĵ�С
	virtual float getTypedFontSize() override;
protected:
	//����Ҫ���д��ֵ��ַ���
	virtual void analyzeTypeStringSelf(float f);
	//���ֻص�
	virtual void typingSelf(float f);
};
#endif  //__TOPWO_TYPE_H__