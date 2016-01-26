#include "TopwoData.h"
#include "Topwo.h"

TopwoData::TopwoData()
: __user_info(NULL)
{
	__arr_data_npc = CCArray::create();
	__arr_data_npc->retain();
	__arr_data_section = CCArray::create();
	__arr_data_section->retain();
	__arr_data_mission = CCArray::create();
	__arr_data_mission->retain();
	__user_info = UserInfo::create();
	__user_info->retain();
}


TopwoData::~TopwoData()
{
	__user_info->release();
	__arr_data_npc->release();
	__arr_data_section->release();
	__arr_data_mission->release();
}

//负责初始到原始0状态
twbool TopwoData::init()
{
	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&__doc_plot, "fonts/plot.json");

	rapidjson::Document doc_json;

	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&doc_json, "fonts/npc.json");
	analyzeDataNpc(doc_json);

	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&doc_json, "fonts/section.json");
	analyzeDataSection(doc_json);

	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&doc_json, "fonts/mission.json");
	analyzeDataMission(doc_json);

	return true;
}

void TopwoData::analyzeDataNpc(rapidjson::Document& doc)
{
	DataNpc* npc_data = NULL;
	for (int i = 0; i < (int)doc.Size(); i++)
	{
		npc_data = DataNpc::create();
		if (doc[i].HasMember("ID") && doc[i]["ID"].IsDouble())
			npc_data->setId((int)doc[i]["ID"].GetDouble());
		if (doc[i].HasMember("NA") && doc[i]["NA"].IsString())
			npc_data->setName(CCString::create(doc[i]["NA"].GetString()));
		if (doc[i].HasMember("MF") && doc[i]["MF"].IsDouble())
			npc_data->setFavorMax((int)doc[i]["MF"].GetDouble());
		if (doc[i].HasMember("IN") && doc[i]["IN"].IsString())
			npc_data->setDes(CCString::create(doc[i]["IN"].GetString()));
		if (doc[i].HasMember("EM") && doc[i]["EM"].IsDouble())
			npc_data->setExpressMissionId((int)doc[i]["EM"].GetDouble());
		addDataNpcToArray(npc_data);
	}
}
void TopwoData::analyzeDataSection(rapidjson::Document& doc)
{
	DataSection* chapter_data = NULL;
	for (int i = 0; i < (int)doc.Size(); i++)
	{
		chapter_data = DataSection::create();
		if (doc[i].HasMember("ID") && doc[i]["ID"].IsDouble())
			chapter_data->setId((int)doc[i]["ID"].GetDouble());
		if (doc[i].HasMember("BE") && doc[i]["BE"].IsDouble())
			chapter_data->setBeginId((int)doc[i]["BE"].GetDouble());
		if (doc[i].HasMember("EN") && doc[i]["EN"].IsDouble())
			chapter_data->setEndId((int)doc[i]["EN"].GetDouble());
		addDataSectionToArray(chapter_data);
	}
}
void TopwoData::analyzeDataMission(rapidjson::Document& doc)
{
	DataMission* mission_data = NULL;
	for (int i = 0; i < (int)doc.Size(); i++)
	{
		mission_data = DataMission::create();
		if (doc[i].HasMember("ID") && doc[i]["ID"].IsDouble())
			mission_data->setId((int)doc[i]["ID"].GetDouble());
		if (doc[i].HasMember("TY") && doc[i]["TY"].IsDouble())
			mission_data->setType((int)doc[i]["TY"].GetDouble());
		if (doc[i].HasMember("RE") && doc[i]["RE"].IsDouble())
			mission_data->setReward((int)doc[i]["RE"].GetDouble());
		if (doc[i].HasMember("TI") && doc[i]["TI"].IsString())
			mission_data->setTitle(CCString::create(doc[i]["TI"].GetString()));
		if (doc[i].HasMember("CO") && doc[i]["CO"].IsString())
			mission_data->setContent(CCString::create(doc[i]["CO"].GetString()));
		if (doc[i].HasMember("MI") && doc[i]["MI"].IsString())
			mission_data->setMission(CCString::create(doc[i]["MI"].GetString()));
		if (doc[i].HasMember("TA") && doc[i]["TA"].IsDouble())
			mission_data->setTarget(doc[i]["TA"].GetDouble());
		if (doc[i].HasMember("WO") && doc[i]["WO"].IsDouble())
			mission_data->setWooer((int)doc[i]["WO"].GetDouble());
		addDataMissionToArray(mission_data);
	}
}

void TopwoData::addDataNpcToArray(DataNpc* npc_data)
{
	__arr_data_npc->addObject(npc_data);
}
DataNpc* TopwoData::getDataNpcFromArray(int id)
{
	return static_cast<DataNpc*>(__arr_data_npc->objectAtIndex(id));
}
void TopwoData::addDataSectionToArray(DataSection* chapter_data)
{
	__arr_data_section->addObject(chapter_data);
}
DataSection* TopwoData::getDataSectionFromArray(int id)
{
	return static_cast<DataSection*>(__arr_data_section->objectAtIndex(id));
}
void TopwoData::addDataMissionToArray(DataMission* mission_data)
{
	__arr_data_mission->addObject(mission_data);
}
DataMission* TopwoData::getDataMissionFromArray(int id)
{
	return static_cast<DataMission*>(__arr_data_mission->objectAtIndex(id));
}

twbool TopwoData::isExistData()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("existData");
}
//清除数据
void TopwoData::purgeData()
{
}

//存档相关
twbool TopwoData::writeData()
{
	CCUserDefault* user_default = CCUserDefault::sharedUserDefault();
	if (!isExistData())
	{
		user_default->setBoolForKey("existData", true);
	}
	user_default->setIntegerForKey("PlaidDays", __user_info->getPlaidDays());
	user_default->setIntegerForKey("Physical", __user_info->getCurrentPhysical());
	user_default->setIntegerForKey("Gold", __user_info->getCurrentGold());
	user_default->setIntegerForKey("TiPo", __user_info->getCurrentTiPo());
	user_default->setIntegerForKey("MeiLi", __user_info->getCurrentMeiLi());
	user_default->setIntegerForKey("ZhiLi", __user_info->getCurrentZhiLi());
	user_default->setIntegerForKey("EQ", __user_info->getCurrentEQ());
	user_default->setIntegerForKey("GanXing", __user_info->getCurrentGanXing());
	user_default->setFloatForKey("TiPoBonus", __user_info->getCurrentTiPoBonus());
	user_default->setFloatForKey("MeiLiBonus", __user_info->getCurrentMeiLiBonus());
	user_default->setFloatForKey("ZhiLiBonus", __user_info->getCurrentZhiLiBonus());
	user_default->setFloatForKey("EQBonus", __user_info->getCurrentEQBonus());
	user_default->setFloatForKey("GanXingBonus", __user_info->getCurrentGanXingBonus());
	user_default->setIntegerForKey("GoodsLevelTiPo", __user_info->getCurrentGoodsLevelTiPo());
	user_default->setIntegerForKey("GoodsLevelMeiLi", __user_info->getCurrentGoodsLevelMeiLi());
	user_default->setIntegerForKey("GoodsLevelZhiLi", __user_info->getCurrentGoodsLevelZhiLi());
	user_default->setIntegerForKey("GoodsLevelEQ", __user_info->getCurrentGoodsLevelEQ());
	user_default->setIntegerForKey("GoodsLevelGanXing", __user_info->getCurrentGoodsLevelGanXing());
	user_default->setIntegerForKey("MissionId", __user_info->getCurrentMissionId());
	user_default->setBoolForKey("MissionIsConsume", __user_info->getCurrentMissionIsConsume());
	user_default->setIntegerForKey("SectionId", __user_info->getCurrentSectionId());
	user_default->setIntegerForKey("PlotId", __user_info->getCurrentPlotId());
	user_default->setIntegerForKey("ChapterId", __user_info->getCurrentChapterId());
	user_default->setIntegerForKey("Wooer", __user_info->getCurrentWooer());
	user_default->setIntegerForKey("Favor", __user_info->getCurrentFavor());
	return true;
}
twbool TopwoData::readData()
{
	CCUserDefault* user_default = CCUserDefault::sharedUserDefault();
	user_default->getBoolForKey("existData", false);
	__user_info->setPlaidDays(user_default->getIntegerForKey("PlaidDays", __user_info->getPlaidDays()));
	__user_info->setCurrentPhysical(user_default->getIntegerForKey("Physical", __user_info->getCurrentPhysical()));
	__user_info->setCurrentGold(user_default->getIntegerForKey("Gold", __user_info->getCurrentGold()));
	__user_info->setCurrentTiPo(user_default->getIntegerForKey("TiPo", __user_info->getCurrentTiPo()));
	__user_info->setCurrentMeiLi(user_default->getIntegerForKey("MeiLi", __user_info->getCurrentMeiLi()));
	__user_info->setCurrentZhiLi(user_default->getIntegerForKey("ZhiLi", __user_info->getCurrentZhiLi()));
	__user_info->setCurrentEQ(user_default->getIntegerForKey("EQ", __user_info->getCurrentEQ()));
	__user_info->setCurrentGanXing(user_default->getIntegerForKey("GanXing", __user_info->getCurrentGanXing()));
	__user_info->setCurrentTiPoBonus(user_default->getFloatForKey("TiPoBonus", __user_info->getCurrentTiPoBonus()));
	__user_info->setCurrentMeiLiBonus(user_default->getFloatForKey("MeiLiBonus", __user_info->getCurrentMeiLiBonus()));
	__user_info->setCurrentZhiLiBonus(user_default->getFloatForKey("ZhiLiBonus", __user_info->getCurrentZhiLiBonus()));
	__user_info->setCurrentEQBonus(user_default->getFloatForKey("EQBonus", __user_info->getCurrentEQBonus()));
	__user_info->setCurrentGanXingBonus(user_default->getFloatForKey("GanXingBonus", __user_info->getCurrentGanXingBonus()));
	__user_info->setCurrentGoodsLevelTiPo(user_default->getIntegerForKey("GoodsLevelTiPo", __user_info->getCurrentGoodsLevelTiPo()));
	__user_info->setCurrentGoodsLevelMeiLi(user_default->getIntegerForKey("GoodsLevelMeiLi", __user_info->getCurrentGoodsLevelMeiLi()));
	__user_info->setCurrentGoodsLevelZhiLi(user_default->getIntegerForKey("GoodsLevelZhiLi", __user_info->getCurrentGoodsLevelZhiLi()));
	__user_info->setCurrentGoodsLevelEQ(user_default->getIntegerForKey("GoodsLevelEQ", __user_info->getCurrentGoodsLevelEQ()));
	__user_info->setCurrentGoodsLevelGanXing(user_default->getIntegerForKey("GoodsLevelGanXing", __user_info->getCurrentGoodsLevelGanXing()));
	__user_info->setCurrentMissionId(user_default->getIntegerForKey("MissionId", __user_info->getCurrentMissionId()));
	__user_info->setCurrentMissionIsConsume(user_default->getBoolForKey("MissionIsConsume", __user_info->getCurrentMissionIsConsume()));
	__user_info->setCurrentSectionId(user_default->getIntegerForKey("SectionId", __user_info->getCurrentSectionId()));
	__user_info->setCurrentPlotId(user_default->getIntegerForKey("PlotId", __user_info->getCurrentPlotId()));
	__user_info->setCurrentChapterId(user_default->getIntegerForKey("ChapterId", __user_info->getCurrentChapterId()));
	__user_info->setCurrentWooer(user_default->getIntegerForKey("Wooer", __user_info->getCurrentWooer()));
	__user_info->setCurrentFavor(user_default->getIntegerForKey("Favor", __user_info->getCurrentFavor()));
	return true;
}
twbool TopwoData::writeData(const char* key, int value)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, value);
	return true;
}
int TopwoData::readData(const char* key)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
}

rapidjson::Value& TopwoData::getPlotDataFromJson(int index)
{
	int size = __doc_plot.Size();
	if (index < 0)
	{
		index = 0;
	}
	else if (index > size)
	{
		index = size;
	}
	return __doc_plot[index];
}