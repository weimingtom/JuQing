#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "DataNpc.h"
#include "DataChapter.h"
#include "DataMission.h"

USING_NS_CC;

class UserInfo : public CCObject
{
public:
	UserInfo();
	virtual ~UserInfo();
	bool init();
	CREATE_FUNC(UserInfo);

	void addDataNpcToArray(DataNpc* npc_data);
	DataNpc* getDataNpcFromArray(int id);
	void addDataChapterToArray(DataChapter* chapter_data);
	DataChapter* getDataChapterFromArray(int id);
	void addDataMissionToArray(DataMission* mission_data);
	DataMission* getDataMissionFromArray(int id);

private:
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc������
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_chapter, ArrOfDataChapter);//�½ڵ�����
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_mission, ArrOfDataMission);//�½ڵ�����
	//���������
	CC_SYNTHESIZE(int, __plaid_days, PlaidDays);
	//��ǰ������ֵ
	CC_SYNTHESIZE(int, __cur_physical, CurrentPhysical);
	//��ǰ�Ľ�Ǯ
	CC_SYNTHESIZE(int, __cur_gold, CurrentGold);
	//��ǰ������
	CC_SYNTHESIZE(int, __cur_tipo, CurrentTiPo);
	//��ǰ������
	CC_SYNTHESIZE(int, __cur_meili, CurrentMeiLi);
	//��ǰ������
	CC_SYNTHESIZE(int, __cur_zhili, CurrentZhiLi);
	//��ǰ������
	CC_SYNTHESIZE(int, __cur_eq, CurrentEQ);
	//��ǰ�ĸ���
	CC_SYNTHESIZE(int, __cur_ganxing, CurrentGanXing);
	//��ǰ����ID
	CC_SYNTHESIZE(int, __cur_mission_id, CurrentMissionId);
	//��ǰС��ID
	CC_SYNTHESIZE(int, __cur_section_id, CurrentSectionId);
	//��ǰ����ID
	CC_SYNTHESIZE(int, __cur_plot_id, CurrentPlotId);
	//��ǰ׷��Ŀ��
	CC_SYNTHESIZE(int, __cur_wooer, CurrentWooer);
	//��ǰ�½�ID
	//CC_SYNTHESIZE(int, __cur_chapter_id, CurrentChapterId);
};

#endif  //__USER_INFO_H__