#include "UserInfo.h"

UserInfo::UserInfo()
{
	__arr_npc_data = CCArray::create();
	__arr_npc_data->retain();
}


UserInfo::~UserInfo()
{
	__arr_npc_data->release();
}

//负责初始到原始0状态
bool UserInfo::init()
{
	return true;
}

void UserInfo::addNpcDataToArray(NpcData* npc_data)
{
	__arr_npc_data->addObject(npc_data);
}
NpcData* UserInfo::getNpcDataFromArray(int id)
{
	return static_cast<NpcData*>(__arr_npc_data->objectAtIndex(id));
}