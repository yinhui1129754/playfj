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
	int moveType = 0;//0�����ƶ� 1 б���ƶ� 2���ƶ�

	//�˺����
	int hurt = 5;
	void hurtUser(user *);
	void hurtEnemy(enemy *);
	//�ƶ����
	POINT * start;
	POINT * center;
	POINT * end;
	float t;
	BOOL  getCenter();
	int isUser;
	float moveAng;
};

