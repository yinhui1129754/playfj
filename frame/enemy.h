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

	//�л����� 0�����ƶ� 1�����ƶ�������
	int enemyType;
	int addNumFrame;
	int subNumFrame;
	int bufNumFrame;

	//�Ƿ���ʾ����ֵ
	int isShowPH;


	//�ӵ�
	int powerNum; //�ӵ�����
	void  sendPower(int id);
	void  sendPower(int id,POINT p);
	void  sendPower();
	void  sendPower(POINT p);
	int powerId; //�ӵ������ͼƬid
	int powerIdAuto; //�Զ������ӵ���ͼƬid
	int powerType; //�����ӵ�����
	int powerSendNum; //�����ӵ���ǰ���
	int powerSendAllNum; //�����ӵ��ܼ��
	int hurt; //�˺�
	vector<POINT> sendPoints; //�Զ������ӵ���
	void addSendPoint(POINT p); //���������ӵ���
	int powerTypeAuto; //�Զ������ӵ�����
	int powerSendNumAuto; //�Զ������ӵ���ǰ���
	int powerSendAllNumAuto; //�Զ������ӵ��ܼ��

	//����name
	LPWSTR name;
	int stringWidth;
	void setName(LPWSTR);
	//�����ص�
	void deathCall();
};

