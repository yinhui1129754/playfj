#pragma once
extern class aircraft;
class prop :public aircraft
{
public:
	prop();
	~prop();
	BOOL frame();
	//移动形式
	int moveType; //0向前走 1向后走 2不移动
	int moveType2; //0向右走 1向左右 2不移动
	float speed;

	int pzNum;
	BOOL pzCall();
	int propType;
	int val;
	//init
	void init();
	int frameNum;
	//构造函数
	prop(sprite * spr);
};

