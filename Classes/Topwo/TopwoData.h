﻿#ifndef __TOPWO_DATA_H__
#define __TOPWO_DATA_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"
#include "UserInfo.h"

USING_NS_CC;

class TopwoData : public CCObject
{
public:
	TopwoData();
	virtual ~TopwoData();
	bool init();
	CREATE_FUNC(TopwoData);

	//是否存在存档
	twbool isExistData();
	//清除数据
	void purgeData();

	//存取
	twbool writeData();
	twbool readData();

	twbool writeData(const char* key, int value);
	int readData(const char* key);

	rapidjson::Value& getPlotDataFromJson(int index);

	void analyzeDataNpc(rapidjson::Document& doc);
	void analyzeDataSection(rapidjson::Document& doc);
	void analyzeDataMission(rapidjson::Document& doc);
private:
	rapidjson::Document __doc_plot;
	//用户数据
	CC_SYNTHESIZE_READONLY(UserInfo*, __user_info, UserInfo);
};

#endif  //__TOPWO_DATA_H__