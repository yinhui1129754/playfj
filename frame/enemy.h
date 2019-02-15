#pragma once
extern class aircraft;
class enemy :public aircraft
{
public:
	enemy();
	~enemy();
	//构造函数
	enemy(sprite * spr, int PH);
	BOOL frame();

	//move
	
	float speed;
	float getJl(user *u);
	//移动形式
	int moveType; //0向前走 1向后走 2不移动
	int moveType2; //0向右走 1向左右 2不移动
	//用户操作状态 1移动状态消失 0 不操作移动状态 1移动状态会改变的移动
	int userType;
	int userTypeStatus = 0; //初始创建的动画
	int id;



	//子弹
	int powerNum;
	void  sendPower(int id);
	int powerType;
	int powerSendNum;
	int powerSendAllNum;
};

