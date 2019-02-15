#pragma once
//����һ���ϰ汾����ײ�ж� �Ѿ���̭
extern class sprite;
extern class collision
{
public:
	collision();
	~collision();
	//��ȡ��ת��������ڴ�������ϵ
	utils::usePoint getPivotPoint(sprite ** sp);
	//��ȡ�����������Ͻǵ�λ��
	utils::usePoint getPivotLocal(sprite ** sp);
	//��ȡ��ת�Ƕ� ����ھ�������ϵ
	float getRotate(sprite ** sp);
	//��ȡ��ת����������Ͻ�����
	utils::usePoint getRotatePoint(sprite ** sp);
	//��ȡ��ת��ĵ�
	utils::usePoint getRotatePoint2(utils::usePoint p1,utils::usePoint p2,int angle);
	//����λ��
	utils::usePoint transitionPoint(utils::usePoint p1, int x, int y);
	//������λ��
	utils::usePoint polarCoordinates(utils::usePoint point,int angle,int distance);
	vector <utils::usePoint> getRotatePoints(sprite **sp);
	float getKeyMax(vector <utils::usePoint> arr,string key);
	float getKeyMin(vector <utils::usePoint> arr, string key);
	bool isXj(float a1, float a2, float b1, float b2);
	void collision::getPoint1Arr(sprite **sp1, vector <utils::usePoint> &pointArr1);
	bool obbTest(sprite **sp1, sprite ** sp2);
	bool obb(sprite **sp1, sprite ** sp2);
	float pointAngleInfo(utils::usePoint point1, utils::usePoint point2);
};

