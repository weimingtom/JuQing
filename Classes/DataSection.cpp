#include "DataSection.h"

DataSection::DataSection()
:__id(0)
, __begin_id(0)
, __end_id(0)
{
}


DataSection::~DataSection()
{
}

//负责初始到原始0状态
bool DataSection::init()
{
	return true;
}
