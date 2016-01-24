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
, __cur_tipo_bonus(0)
, __cur_meili_bonus(0)
, __cur_zhili_bonus(0)
, __cur_eq_bonus(0)
, __cur_ganxing_bonus(0)
, __cur_mission_id(1)
, __cur_section_id(1)
, __cur_plot_id(0)
, __cur_goods_level_tipo(0)
, __cur_goods_level_meili(0)
, __cur_goods_level_zhili(0)
, __cur_goods_level_eq(0)
, __cur_goods_level_ganxing(0)
, __cur_mission_is_consume(false)
, __cur_chapter_id(1)
, __cur_wooer(5)
, __cur_favor(10)
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

int UserInfo::getBonusById(int id)
{
	float fRet = 0;
	if (id == 1)
	{
		fRet = __cur_tipo * __cur_tipo_bonus;
	}
	else if (id == 2)
	{
		fRet = __cur_meili * __cur_meili_bonus;
	}
	else if (id == 3)
	{
		fRet = __cur_zhili * __cur_zhili_bonus;
	}
	else if (id == 4)
	{
		fRet = __cur_eq *  __cur_eq_bonus;
	}
	else if (id == 5)
	{
		fRet = __cur_ganxing * __cur_ganxing_bonus;
	}
	int iRet = (int)fRet;
	float temp_f = fRet - (float)iRet;
	temp_f = temp_f - 1.0f;
	if (temp_f> -1e-6 && temp_f < 1e-6)
	{
		iRet += 1;
	}
	return iRet;
}