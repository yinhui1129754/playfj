#pragma once
extern  class aircraft;
extern class user;
extern class enemy;
class power : public aircraft
{
public:
	power();
	~power();
	power(sprite * spr);
	BOOL frame();
	float speed = 5.0;
	int moveType = 0;//0向下移动 1 斜线移动 2上移动

	//伤害相关
	int hurt = 5;
	void hurtUser(user *);
	void hurtEnemy(enemy *);
	//移动相关
	POINT * start;
	POINT * center;
	POINT * end;
	float t;
	BOOL  getCenter();
	int isUser;
	float moveAng;
};

