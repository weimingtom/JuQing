#include "NpcData.h"

NpcData::NpcData()
:__id(0)
, __name("name")
, __des("des")
, __favor_max(0)
, __favor_cur(0)
{
}


NpcData::~NpcData()
{
}

//负责初始到原始0状态
bool NpcData::init()
{
	return true;
}
