#pragma once
extern class aircraft;
class prop :public aircraft
{
public:
	prop();
	~prop();
	BOOL frame();
	//�ƶ���ʽ
	int moveType; //0��ǰ�� 1����� 2���ƶ�
	int moveType2; //0������ 1������ 2���ƶ�
	float speed;

	int pzNum;
	BOOL pzCall();
	int propType;
	int val;
	//init
	void init();
	int frameNum;
	//���캯��
	prop(sprite * spr);
};

