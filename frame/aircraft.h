#pragma once
class aircraft
{
public:
	aircraft();
	~aircraft();
	//���캯��
	aircraft(sprite * spr, int PH);
	//��ͼ
	sprite * view=NULL;
	//������ͼ
	sprite * deathView = NULL;
	int isDeath ;
	int deathNum ;//�������ʱ��
	int deathWidth;
	int deathHeight;
	int deathFrame;
	//����ֵ
	int PH;
	int maxPH;
	//�������� 0 �� 1�� 2�� 3��
	int angle_type; //0,1,2,3 �ĸ����� ͬʱ�����ӵ��ķ��䷽��
};

