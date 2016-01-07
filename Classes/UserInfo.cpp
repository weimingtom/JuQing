#include "UserInfo.h"

UserInfo::UserInfo()
{
	__arr_data_npc = CCArray::create();
	__arr_data_npc->retain();
	__arr_data_chapter = CCArray::create();
	__arr_data_chapter->retain();
}


UserInfo::~UserInfo()
{
	__arr_data_npc->release();
}

//负责初始到原始0状态
bool UserInfo::init()
{
	return true;
}

void UserInfo::addDataNpcToArray(DataNpc* npc_data)
{
	__arr_data_npc->addObject(npc_data);
}
DataNpc* UserInfo::getDataNpcFromArray(int id)
{
	return static_cast<DataNpc*>(__arr_data_npc->objectAtIndex(id));
}
void UserInfo::addDataChapterToArray(DataChapter* npc_data)
{
	__arr_data_chapter->addObject(npc_data);
}
DataChapter* UserInfo::getDataChapterFromArray(int id)
{
	return static_cast<DataChapter*>(__arr_data_chapter->objectAtIndex(id));
}