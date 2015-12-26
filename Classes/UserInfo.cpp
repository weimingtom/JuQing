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

//�����ʼ��ԭʼ0״̬
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