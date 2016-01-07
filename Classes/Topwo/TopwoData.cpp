#include "TopwoData.h"
#include "Topwo.h"

TopwoData::TopwoData()
: __user_info(nullptr)
, __cur_plot_id(0)
, __cur_chapter_id(0)
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
	analyzeDataNpc(doc_npc);

	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&doc_npc, "fonts/chapter.json");
	analyzeDataChapter(doc_npc);

	__cur_chapter_id = 1;

	return true;
}

void TopwoData::analyzeDataNpc(rapidjson::Document& doc)
{
	DataNpc* npc_data = nullptr;
	for (int i = 0; i < doc.Size(); i++)
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
		npc_data->setFavorCur(0);
		__user_info->addDataNpcToArray(npc_data);
	}
}
void TopwoData::analyzeDataChapter(rapidjson::Document& doc)
{
	DataChapter* chapter_data = nullptr;
	for (int i = 0; i < doc.Size(); i++)
	{
		chapter_data = DataChapter::create();
		if (doc[i].HasMember("ID") && doc[i]["ID"].IsDouble())
			chapter_data->setId((int)doc[i]["ID"].GetDouble());
		if (doc[i].HasMember("BE") && doc[i]["BE"].IsDouble())
			chapter_data->setBeginId((int)doc[i]["BE"].GetDouble());
		if (doc[i].HasMember("EN") && doc[i]["EN"].IsDouble())
			chapter_data->setEndId((int)doc[i]["EN"].GetDouble());
		__user_info->addDataChapterToArray(chapter_data);
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