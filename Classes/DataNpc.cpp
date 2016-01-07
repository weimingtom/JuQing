#include "DataNpc.h"

DataNpc::DataNpc()
:__id(0)
, __name(CCString::create("name"))
, __des(CCString::create("des"))
, __favor_max(0)
, __favor_cur(0)
{
}


DataNpc::~DataNpc()
{
}

//负责初始到原始0状态
bool DataNpc::init()
{
	return true;
}
