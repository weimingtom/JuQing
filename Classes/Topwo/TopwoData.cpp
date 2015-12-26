#include "TopwoData.h"
#include "Topwo.h"

TopwoData::TopwoData()
{
	__user_info = UserInfo::create();
	__user_info->retain();
}


TopwoData::~TopwoData()
{
	__user_info->release();
}

//负责初始到原始0状态
twbool TopwoData::init()
{
	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&__doc_plot, "fonts/plot.json");
	rapidjson::Document doc_npc;
	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&doc_npc, "fonts/npc.json");
	analyzeNpcData(doc_npc);
	return true;
}

void TopwoData::analyzeNpcData(rapidjson::Document& doc)
{
	NpcData* npc_data = NpcData::create();
	__user_info->addNpcDataToArray(npc_data);
	for (int i = 0; i < doc.Size(); i++)
	{
		npc_data = NpcData::create();
		npc_data->setId((int)doc[i]["ID"].GetDouble());
		npc_data->setName(doc[i]["NA"].GetString());
		npc_data->setFavorMax((int)doc[i]["MF"].GetDouble());
		npc_data->setName(doc[i]["IN"].GetString());
		npc_data->setFavorCur(0);
		__user_info->addNpcDataToArray(npc_data);
	}
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
	if (!isExistData())
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("existData", true);
	}
	return true;
}
twbool TopwoData::readData()
{
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