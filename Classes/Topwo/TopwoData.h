#ifndef __TOPWO_DATA_H__
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

	void analyzeDataNpc(rapidjson::Document& doc);
	void analyzeDataSection(rapidjson::Document& doc);
	void analyzeDataMission(rapidjson::Document& doc);

	rapidjson::Value& getPlotDataFromJson(int index);

	void addDataNpcToArray(DataNpc* npc_data);
	DataNpc* getDataNpcFromArray(int id);
	void addDataSectionToArray(DataSection* section_data);
	DataSection* getDataSectionFromArray(int id);
	void addDataMissionToArray(DataMission* mission_data);
	DataMission* getDataMissionFromArray(int id);
private:
	rapidjson::Document __doc_plot;
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_section, ArrOfDataSection);//段落的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_mission, ArrOfDataMission);//任务的数据
	//用户数据
	CC_SYNTHESIZE_READONLY(UserInfo*, __user_info, UserInfo);
};

#endif  //__TOPWO_DATA_H__