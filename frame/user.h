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
	long long hurtEnemy;


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
	void sendPower();
	void sendPowerJn(int id);


	//�ӵ����
	int isSend ; // �Ƿ����ӵ�
	int hurt ;
	int sendAllJg;
	int sendNowJg ;
	int powerId;

	vector<POINT> sendPoints; //�Զ������ӵ���
	void addSendPoint(POINT p); //���������ӵ���

	int powerSendNumAuto; //�Զ������ӵ���ǰ���
	int powerSendAllNumAuto; //�Զ������ӵ��ܼ��
	int powerIdAuto; //�Զ������ӵ���ͼƬid
	int hurtAuto;
	void  sendPower(int id, POINT p);
	void  sendPower(POINT p);

	//����1
	int jnTimer; //���ܵ�ǰ���ͷ�ʱ��
	int jnAllimer; //���ܵĳ���ʱ��
	int isJnNum; //��������
	int jnCreateTimmer; //�����ڵ�ʱ����
	int jnCreateAllTimmer; //��ǰ�����ļ��
	int jnId; //���ܵ�����ͼƬid
	int jnzxId; //����β�������id
	void sendJn();
};

