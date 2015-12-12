#include "Topwo.h"

Topwo* Topwo::__Topwo = 0;

Topwo::Topwo()
{
}

Topwo::~Topwo()
{
}
Topwo* Topwo::getInstance()
{
	if (!__Topwo)
	{
		__Topwo = new Topwo();
		__Topwo->__init();
	}
	return __Topwo;
}
bool Topwo::__init()
{
	std::srand((twuint)time(static_cast<time_t*>(0)));

	__TopwoTools = TopwoTools::create();
	__TopwoTools->retain();

	__TopwoPlatform = TopwoPlatform::create();
	__TopwoPlatform->retain();

	__TopwoAudio = TopwoAudio::create();
	__TopwoAudio->retain();

	__TopwoData = TopwoData::create();
	__TopwoData->retain();

	return true;
}

const char* Topwo::getVersion()
{
	return "http://www.topwo.com(人物面向右的 敌人是面向左的)";
}
TopwoTools* Topwo::getTopwoTools()
{
	return __TopwoTools;
}
TopwoPlatform* Topwo::getTopwoPlatform()
{
	return __TopwoPlatform;
}
TopwoAudio* Topwo::getTopwoAudio()
{
	return __TopwoAudio;
}
TopwoData* Topwo::getTopwoData()
{
	return __TopwoData;
}