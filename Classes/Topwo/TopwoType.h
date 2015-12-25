#ifndef __TOPWO_TYPE_H__
#define __TOPWO_TYPE_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
USING_NS_CC;

//打字类
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

	//设置显示区域大小
	void setTypeSize(CCSize size);
	//设置打字间隔时间
	void setTypeInterval(twfloat interval);
	//设置打完一句话后的回调函数
	void setTypeFinishCallback(CCObject* target, SEL_CallFunc callfun);

	//设置打字的字符串
	virtual void setTypeString(CCString *str);

	//直接全部显示出来
	virtual void typeAll();
protected:
	//第一帧对需要打印的字符串分析
	virtual void updateOnce(float f);

	//打字回调
	virtual void typing(float f);

	TypeLabelStyle __label_style;//类型
	CCLabelProtocol* __label;//标签
	CCSize __type_size;//内容区域大小
	float __type_interval;//间隔时间
	CCString* __type_str;//标签内容
	twuint __type_char_sum;//打印的字符数
	twuint __type_char_num;//打印的字符数
	bool __is_type_all;//是否显示所有了

	CCObject* __callbackListener;
	SEL_CallFunc __callbackfunc;
};
#endif  //__TOPWO_TYPE_H__