#ifndef __TOPWO_H__
#define __TOPWO_H__
#include "Topwo/TopwoDefine.h"
#include "Topwo/TopwoAudio.h"
#include "Topwo/TopwoTools.h"
#include "Topwo/TopwoPlatform.h"
#include "Topwo/TopwoData.h"
#include "Topwo/TopwoLabel.h"

class Topwo{
public:
	static Topwo* getInstance();
	const char* getVersion();


	TopwoTools* getTopwoTools();
	TopwoPlatform* getTopwoPlatform();
	TopwoAudio* getTopwoAudio();
	TopwoData* getTopwoData();
private:
	Topwo();
	virtual ~Topwo();
	bool __init();

	static Topwo *__Topwo;//µ¥Àý

	TopwoTools* __TopwoTools;
	TopwoPlatform* __TopwoPlatform;
	TopwoAudio* __TopwoAudio;
	TopwoData* __TopwoData;
};
#endif  //__TOPWO_H__