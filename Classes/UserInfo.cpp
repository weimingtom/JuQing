#include "UserInfo.h"

UserInfo::UserInfo()
:__plaid_days(0)
, __cur_physical(100)
, __cur_gold(1000)
, __cur_tipo(10)
, __cur_meili(10)
, __cur_zhili(10)
, __cur_eq(10)
, __cur_ganxing(10)
, __cur_mission_id(1)
, __cur_plot_id(0)
, __cur_section_id(0)
, __cur_wooer(3)
{
	__arr_data_npc = CCArray::create();
	__arr_data_npc->retain();
	__arr_data_chapter = CCArray::create();
	__arr_data_chapter->retain();
	__arr_data_mission = CCArray::create();
	__arr_data_mission->retain();
}


UserInfo::~UserInfo()
{
	__arr_data_npc->release();
	__arr_data_chapter->release();
	__arr_data_mission->release();
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
void UserInfo::addDataSectionToArray(DataSection* chapter_data)
{
	__arr_data_chapter->addObject(chapter_data);
}
DataSection* UserInfo::getDataSectionFromArray(int id)
{
	return static_cast<DataSection*>(__arr_data_chapter->objectAtIndex(id));
}
void UserInfo::addDataMissionToArray(DataMission* mission_data)
{
	__arr_data_mission->addObject(mission_data);
}
DataMission* UserInfo::getDataMissionFromArray(int id)
{
	return static_cast<DataMission*>(__arr_data_mission->objectAtIndex(id));
}