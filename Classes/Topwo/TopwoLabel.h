#ifndef __TOPWO_LABEL_H__
#define __TOPWO_LABEL_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//打字类
class TopwoType
{
public:
	TopwoType();
	virtual ~TopwoType();
	//设置显示区域大小
	void setTypeSize(CCSize size);
	//设置打字间隔时间
	void setTypeInterval(twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);
protected:

	CCSize __type_size;//内容区域大小
	float __type_interval;//间隔时间
	CCString* __type_str;
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	bool __is_type_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
class TopwoLabelBMFont : public CCLabelBMFont, public TopwoType
{
public:
	TopwoLabelBMFont();
	virtual ~TopwoLabelBMFont();

	//创造函数
	static TopwoLabelBMFont* create(const char* fntfile);

	//初始函数
	virtual bool init(const char* fntfile);

	//设置打字的字符串
	virtual void setTypeString(CCString *str);

	//直接全部显示出来
	virtual void typeAll();
	//打字回调
	virtual void typing(float f);
protected:
};

class TopwoLabelTTF :public CCLabelTTF, public TopwoType
{
public:
	TopwoLabelTTF();
	virtual ~TopwoLabelTTF();

	//创造函数
	static TopwoLabelTTF* create(const char* fntfile, float fontSize);

	//初始函数
	virtual bool init(const char* fntfile, float fontSize);

	//设置打字的字符串,t打字间隔时间
	virtual void setTypeString(CCString *str);

	//直接全部显示出来
	virtual void typeAll();

	//打字回调
	virtual void typing(float f);
protected:
};
#endif  //__TOPWO_LABEL_H__