#pragma once
extern  class aircraft;
extern class power;
class user : public aircraft
{
public:
	user();
	~user();
	//���캯��
	user(sprite * spr, int PH);
	void frame();

	//move
	int moveTypeX = 0; //0,1
	int moveTypeY = 0;
	int isMoveX = 0;
	int isMoveY = 0;
	float speed = 5;
	//�û�����״̬ 0�û����Բ���1�û����ܲ���
	int userType = 0;
	int userTypeStatus = 0; //��ʼ�����Ķ���
	void sendPower(int id);

	//�ӵ����
	int isSend ; // �Ƿ����ӵ�
	int hurt ;
	int sendAllJg;
	int sendNowJg ;
};

