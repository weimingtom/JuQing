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
}


UserInfo::~UserInfo()
{
}

//负责初始到原始0状态
bool UserInfo::init()
{
	return true;
}

void UserInfo::resetData()
{
	__plaid_days = (0);
	__cur_physical = (100);
	__cur_gold = (1000);
	__cur_tipo = (10);
	__cur_meili = (10);
	__cur_zhili = (10);
	__cur_eq = (10);
	__cur_ganxing = (10);
	__cur_tipo_bonus = (0);
	__cur_meili_bonus = (0);
	__cur_zhili_bonus = (0);
	__cur_eq_bonus = (0);
	__cur_ganxing_bonus = (0);
	__cur_mission_id = (1);
	__cur_section_id = (1);
	__cur_plot_id = (0);
	__cur_goods_level_tipo = (0);
	__cur_goods_level_meili = (0);
	__cur_goods_level_zhili = (0);
	__cur_goods_level_eq = (0);
	__cur_goods_level_ganxing = (0);
	__cur_mission_is_consume = (false);
	__cur_chapter_id = (1);
	__cur_wooer = (5);
	__cur_favor = (10);
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