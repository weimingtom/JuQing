#include "DataMission.h"

DataMission::DataMission()
:__id(0)
, __type(0)
, __title(NULL)
, __content(NULL)
, __target(NULL)
, __reward(0)
{
}


DataMission::~DataMission()
{
}

//�����ʼ��ԭʼ0״̬
bool DataMission::init()
{
	return true;
}
