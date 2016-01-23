#include "DataMission.h"

DataMission::DataMission()
:__id(0)
, __type(0)
, __title(NULL)
, __content(NULL)
, __mission(NULL)
, __target(0.0)
, __reward(0)
{
}


DataMission::~DataMission()
{
}

//负责初始到原始0状态
bool DataMission::init()
{
	return true;
}
