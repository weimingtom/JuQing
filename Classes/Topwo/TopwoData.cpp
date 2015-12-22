#include "TopwoData.h"
#include "Topwo.h"

TopwoData::TopwoData()
{
}


TopwoData::~TopwoData()
{
}

//负责初始到原始0状态
twbool TopwoData::init()
{
	Topwo::getInstance()->getTopwoTools()->readRapidJSON(&__doc_plot, "fonts/plot.json");
	return true;
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

rapidjson::Value& TopwoData::getJsonValue(int index)
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