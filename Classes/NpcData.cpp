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

//�����ʼ��ԭʼ0״̬
bool NpcData::init()
{
	return true;
}
