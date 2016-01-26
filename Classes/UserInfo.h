#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "DataNpc.h"
#include "DataSection.h"
#include "DataMission.h"

USING_NS_CC;

class UserInfo : public CCObject
{
public:
	UserInfo();
	virtual ~UserInfo();
	bool init();
	CREATE_FUNC(UserInfo);

	void resetData();
	int getBonusById(int id);

private:
	//玩过得天数
	CC_SYNTHESIZE(int, __plaid_days, PlaidDays);
	//当前的体力值
	CC_SYNTHESIZE(int, __cur_physical, CurrentPhysical);
	//当前的金钱
	CC_SYNTHESIZE(int, __cur_gold, CurrentGold);
	//当前的体魄1
	CC_SYNTHESIZE(int, __cur_tipo, CurrentTiPo);
	//当前的魅力2
	CC_SYNTHESIZE(int, __cur_meili, CurrentMeiLi);
	//当前的智力3
	CC_SYNTHESIZE(int, __cur_zhili, CurrentZhiLi);
	//当前的情商4
	CC_SYNTHESIZE(int, __cur_eq, CurrentEQ);
	//当前的感性5
	CC_SYNTHESIZE(int, __cur_ganxing, CurrentGanXing);
	//当前的体魄加成
	CC_SYNTHESIZE(float, __cur_tipo_bonus, CurrentTiPoBonus);
	//当前的魅力加成
	CC_SYNTHESIZE(float, __cur_meili_bonus, CurrentMeiLiBonus);
	//当前的智力加成
	CC_SYNTHESIZE(float, __cur_zhili_bonus, CurrentZhiLiBonus);
	//当前的情商加成
	CC_SYNTHESIZE(float, __cur_eq_bonus, CurrentEQBonus);
	//当前的感性加成
	CC_SYNTHESIZE(float, __cur_ganxing_bonus, CurrentGanXingBonus);
	//当前拥有体魄物品的等级
	CC_SYNTHESIZE(int, __cur_goods_level_tipo, CurrentGoodsLevelTiPo);
	//当前拥有魅力物品的等级
	CC_SYNTHESIZE(int, __cur_goods_level_meili, CurrentGoodsLevelMeiLi);
	//当前拥有智力物品的等级
	CC_SYNTHESIZE(int, __cur_goods_level_zhili, CurrentGoodsLevelZhiLi);
	//当前拥有情商物品的等级
	CC_SYNTHESIZE(int, __cur_goods_level_eq, CurrentGoodsLevelEQ);
	//当前拥有感性物品的等级
	CC_SYNTHESIZE(int, __cur_goods_level_ganxing, CurrentGoodsLevelGanXing);
	//当前任务ID
	CC_SYNTHESIZE(int, __cur_mission_id, CurrentMissionId);
	//当前任务的消耗是否扣除
	CC_SYNTHESIZE(bool, __cur_mission_is_consume, CurrentMissionIsConsume);
	//当前小节ID
	CC_SYNTHESIZE(int, __cur_section_id, CurrentSectionId);
	//当前剧情ID
	CC_SYNTHESIZE(int, __cur_plot_id, CurrentPlotId);
	//当前章节ID
	CC_SYNTHESIZE(int, __cur_chapter_id, CurrentChapterId);
	//当前追求目标
	CC_SYNTHESIZE(int, __cur_wooer, CurrentWooer);
	//当前女主角的好感度
	CC_SYNTHESIZE(int, __cur_favor, CurrentFavor);
};

#endif  //__USER_INFO_H__