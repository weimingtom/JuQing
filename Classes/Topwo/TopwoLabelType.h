#ifndef __YIEYOTYPING_H__
#define __YIEYOTYPING_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;
//打字类
class TopwoLabelType:public CCLabelBMFont
{
public:
	TopwoLabelType();
	virtual ~TopwoLabelType();

	//创造函数
	CREATE_FUNC(TopwoLabelType);

	//初始函数
	virtual bool init();

	//设置打字的字符串,t打字间隔时间
	void setTypeString(CCString *str, twfloat dlg_width, twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//直接全部显示出来
	void showAll();

	//打字回调
	void typing(float f);

	// 计算str字符数目
	int getUtf8Length(char *str);
	//get子串
	CCString* subUtfString(char *str, unsigned int start, unsigned int end);

private:
	CCString* __str;
	twfloat __line_width;//一行字符串宽度
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	twbool __is_show_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};

#endif  //__YIEYOTYPING_H__