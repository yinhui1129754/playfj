#pragma once
extern  class aircraft;
extern class power;
class user : public aircraft
{
public:
	user();
	~user();
	//构造函数
	user(sprite * spr, int PH);
	void frame();

	//move
	int moveTypeX = 0; //0,1
	int moveTypeY = 0;
	int isMoveX = 0;
	int isMoveY = 0;
	float speed = 5;
	//用户操作状态 0用户可以操作1用户不能操作
	int userType = 0;
	int userTypeStatus = 0; //初始创建的动画
	void sendPower(int id);

	//子弹相关
	int isSend ; // 是否发送子弹
	int hurt ;
	int sendAllJg;
	int sendNowJg ;
};

