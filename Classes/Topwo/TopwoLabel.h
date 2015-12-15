#ifndef __TOPWO_LABEL_H__
#define __TOPWO_LABEL_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//打字类
class TopwoLabelBMFont :public CCLabelBMFont
{
public:
	TopwoLabelBMFont();
	virtual ~TopwoLabelBMFont();

	//创造函数
	static TopwoLabelBMFont* create(const char* fntfile);

	//初始函数
	virtual bool init(const char* fntfile);

	//设置打字的字符串,t打字间隔时间
	void setTypeString(CCString *str, twfloat line_width, twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//直接全部显示出来
	void showAll();

private:
	//打字回调
	void typing(float f);

	CCString* __str;
	twfloat __line_width;//一行字符串宽度
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	twbool __is_show_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};

class TopwoLabelTTF :public CCLabelTTF
{
public:
	TopwoLabelTTF();
	virtual ~TopwoLabelTTF();

	//创造函数
	static TopwoLabelTTF* create(const char* fntfile, float fontSize);

	//初始函数
	virtual bool init(const char* fntfile, float fontSize);

	//设置打字的字符串,t打字间隔时间
	void setTypeString(CCString *str, twfloat line_width, twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//直接全部显示出来
	void showAll();

private:
	//打字回调
	void typing(float f);

	CCString* __str;
	twfloat __line_width;//一行字符串宽度
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	twbool __is_show_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
#endif  //__TOPWO_LABEL_H__