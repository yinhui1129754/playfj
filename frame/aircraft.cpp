#include "../stdafx.h"
#include "aircraft.h"


aircraft::aircraft()
{
}


aircraft::~aircraft()
{
}
aircraft::aircraft(sprite * spr, int PH) {
	this->view = new sprite(spr->img);//������Ҫ�²���һ��ָ�벻Ȼ���ǲ�����ÿһ��ʵ�����󱣳ֶ�����
	this->PH = PH;
	this->angle_type = 0;
	this->isDeath = 0;
	this->deathNum = 24;//�������ʱ��
	this->deathWidth = 0;
	this->deathHeight =0;
	this->deathFrame = 0;
};
