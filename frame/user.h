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
	long long hurtEnemy;


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
	void sendPower();
	void sendPowerJn(int id);


	//子弹相关
	int isSend ; // 是否发送子弹
	int hurt ;
	int sendAllJg;
	int sendNowJg ;
	int powerId;

	vector<POINT> sendPoints; //自动发射子弹点
	void addSendPoint(POINT p); //新增发射子弹点

	int powerSendNumAuto; //自动发送子弹当前间隔
	int powerSendAllNumAuto; //自动发送子弹总间隔
	int powerIdAuto; //自动发射子弹的图片id
	int hurtAuto;
	void  sendPower(int id, POINT p);
	void  sendPower(POINT p);

	//技能1
	int jnTimer; //技能当前的释放时间
	int jnAllimer; //技能的持续时间
	int isJnNum; //技能数量
	int jnCreateTimmer; //创建炮弹时间间隔
	int jnCreateAllTimmer; //当前创建的间隔
	int jnId; //技能导弹的图片id
	int jnzxId; //技能尾巴杂项的id
	void sendJn();
};

