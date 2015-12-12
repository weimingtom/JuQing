#ifndef __TOPWO_DATA_H__
#define __TOPWO_DATA_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "TopwoTools.h"

USING_NS_CC;

class TopwoData : public CCObject
{
public:
	TopwoData();
	virtual ~TopwoData();
	bool init();
	CREATE_FUNC(TopwoData);

	//�Ƿ���ڴ浵
	twbool isExistData();
	//�������
	void purgeData();

	//��ȡ
	twbool writeData();
	twbool readData();

	twbool writeData(const char* key, int value);
	int readData(const char* key);

	rapidjson::Value& getJsonValue(int index);
private:
	rapidjson::Document __doc;
};

#endif  //__TOPWO_DATA_H__