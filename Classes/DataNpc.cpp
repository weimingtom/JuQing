#include "DataNpc.h"

DataNpc::DataNpc()
:__id(0)
, __name(CCString::create("name"))
, __des(CCString::create("des"))
, __favor_max(0)
, __favor_cur(0)
{
}


DataNpc::~DataNpc()
{
}

//�����ʼ��ԭʼ0״̬
bool DataNpc::init()
{
	return true;
}
