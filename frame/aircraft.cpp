#include "../stdafx.h"
#include "aircraft.h"


aircraft::aircraft()
{
}


aircraft::~aircraft()
{
}
aircraft::aircraft(sprite * spr, int PH) {
	this->view = new sprite(spr->img);//这里需要新产生一个指针不然我们不能让每一个实例对象保持独立性
	this->PH = PH;
	this->angle_type = 0;
	this->isDeath = 0;
	this->deathNum = 24;//死亡存活时间
	this->deathWidth = 0;
	this->deathHeight =0;
	this->deathFrame = 0;
};
