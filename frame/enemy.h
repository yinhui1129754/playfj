#pragma once
extern class aircraft;
class enemy :public aircraft
{
public:
	enemy();
	~enemy();
	//���캯��
	enemy(sprite * spr, int PH);
	BOOL frame();

	//move
	
	float speed;
	float getJl(user *u);
	//�ƶ���ʽ
	int moveType; //0��ǰ�� 1����� 2���ƶ�
	int moveType2; //0������ 1������ 2���ƶ�
	//�û�����״̬ 1�ƶ�״̬��ʧ 0 �������ƶ�״̬ 1�ƶ�״̬��ı���ƶ�
	int userType;
	int userTypeStatus = 0; //��ʼ�����Ķ���
	int id;



	//�ӵ�
	int powerNum;
	void  sendPower(int id);
	int powerType;
	int powerSendNum;
	int powerSendAllNum;
};

