#ifndef __TOPWO_TYPE_H__
#define __TOPWO_TYPE_H__
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

	//设置要进行打字的字符串
	virtual void setTypeString(CCString *str);
	//设置显示区域大小
	void setTypeSize(CCSize size);
	//设置打字间隔时间
	void setTypeInterval(twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);
	//直接全部打出来
	virtual void typeAll();

	//设置打出来的字符串
	virtual void setTypedString(const char* typed_string) = 0;
	//获取打出来的字符串内容的大小
	virtual CCSize getTypedStringContentSize() = 0;
	//开启解析
	virtual void openAnalyze(float delay) = 0;
	//开启打字循环
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) = 0;
	//关闭打字循环
	virtual void closeTypeLoop() = 0;
	//获取字体的大小
	virtual float getTypedFontSize() = 0;
protected:
	//解析要进行打字的字符串
	virtual void analyzeTypeString(float f);
	//打字回调
	virtual void typing(float f);

	CCSize __type_size;//内容区域大小
	float __type_interval;//间隔时间
	CCString* __type_str;
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	bool __is_type_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
class TopwoTypeBMFont : public CCLabelBMFont, public TopwoType
{
public:
	TopwoTypeBMFont();
	virtual ~TopwoTypeBMFont();

	//初始函数
	virtual bool init(const char* fntfile);
	//创造函数
	static TopwoTypeBMFont* create(const char* fntfile);

	//设置打出来的字符串
	virtual void setTypedString(const char* typed_string) override;
	//获取打出来的字符串内容的大小
	virtual CCSize getTypedStringContentSize() override;
	//开启解析
	virtual void openAnalyze(float delay) override;
	//开启打字循环
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) override;
	//关闭打字循环
	virtual void closeTypeLoop() override;
	//获取字体的大小
	virtual float getTypedFontSize() override;
protected:
	//解析要进行打字的字符串
	virtual void analyzeTypeStringSelf(float f);
	//打字回调
	virtual void typingSelf(float f);
};

class TopwoTypeTTF :public CCLabelTTF, public TopwoType
{
public:
	TopwoTypeTTF();
	virtual ~TopwoTypeTTF();

	//初始函数
	virtual bool init(const char* fntfile, float fontSize);
	//创造函数
	static TopwoTypeTTF* create(const char* fntfile, float fontSize);

	//设置打出来的字符串
	virtual void setTypedString(const char* typed_string) override;
	//获取打出来的字符串内容的大小
	virtual CCSize getTypedStringContentSize() override;
	//开启解析
	virtual void openAnalyze(float delay) override;
	//开启打字循环
	virtual void openTypeLoop(float interval, unsigned int repeat, float delay) override;
	//关闭打字循环
	virtual void closeTypeLoop() override;
	//获取字体的大小
	virtual float getTypedFontSize() override;
protected:
	//解析要进行打字的字符串
	virtual void analyzeTypeStringSelf(float f);
	//打字回调
	virtual void typingSelf(float f);
};
#endif  //__TOPWO_TYPE_H__