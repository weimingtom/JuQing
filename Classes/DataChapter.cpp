#include "DataChapter.h"

DataChapter::DataChapter()
:__id(0)
, __begin_id(0)
, __end_id(0)
{
}


DataChapter::~DataChapter()
{
}

//负责初始到原始0状态
bool DataChapter::init()
{
	return true;
}
