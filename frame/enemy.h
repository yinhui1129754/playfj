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

	//敌机类型 0向下移动 1波浪移动过类型
	int enemyType;
	int addNumFrame;
	int subNumFrame;
	int bufNumFrame;

	//是否显示生命值
	int isShowPH;


	//子弹
	int powerNum; //子弹数量
	void  sendPower(int id);
	void  sendPower(int id,POINT p);
	void  sendPower();
	void  sendPower(POINT p);
	int powerId; //子弹发射的图片id
	int powerIdAuto; //自动发射子弹的图片id
	int powerType; //发送子弹类型
	int powerSendNum; //发送子弹当前间隔
	int powerSendAllNum; //发送子弹总间隔
	int hurt; //伤害
	vector<POINT> sendPoints; //自动发射子弹点
	void addSendPoint(POINT p); //新增发射子弹点
	int powerTypeAuto; //自动发射子弹类型
	int powerSendNumAuto; //自动发送子弹当前间隔
	int powerSendAllNumAuto; //自动发送子弹总间隔

	//设置name
	LPWSTR name;
	int stringWidth;
	void setName(LPWSTR);
	//死亡回调
	void deathCall();
};

