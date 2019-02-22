#pragma once
class aircraft
{
public:
	aircraft();
	~aircraft();
	//构造函数
	aircraft(sprite * spr, int PH);
	//视图
	sprite * view=NULL;
	//死亡视图
	sprite * deathView = NULL;
	int isDeath ;
	int deathNum ;//死亡存活时间
	int deathWidth;
	int deathHeight;
	int deathFrame;
	//生命值
	int PH;
	int maxPH;
	//方向类型 0 ↓ 1↑ 2← 3→
	int angle_type; //0,1,2,3 四个方向 同时控制子弹的发射方向
};

