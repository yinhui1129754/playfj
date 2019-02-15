#pragma once
class colVec
{
public:
	colVec();//���캯��
	~colVec();//��������
	bool colVec::obb(sprite **sp, sprite **sp2);//���ģʽobb 
	bool colVec::obb(utils::useSpSt st1, utils::useSpSt st2);//���ģʽobb 
	bool colVec::aabb(sprite **sp, sprite **sp2);//���ģʽaabb ������ģʽ
	bool colVec::aabb(sprite *sp, sprite *sp2);
	void colVec::getShapePoints(sprite **sp,const int num);//��ȡ��״�ĵ�
	void colVec::initVec();//����ת��Ϊ��λ����
	void colVec::getOneVec(const utils::usePoint &p1, const utils::usePoint &p2,int num);
	bool colVec::getVecProjection();//��ȡ����ͶӰ
	bool colVec::comparePoints(const int num);//�Աȵ����Ϣ�ж��Ƿ���ײ
	void colVec::getSLCoordinateSystem(sprite **sp, const int num);//��ȡ�ֲ�����ϵ����Ϣδ��ת
	void colVec::getShapePoints(const utils::useSpSt st, const int num);//�Խṹ����ʽ��ȡ����Ϣ ����Ԥ�ж�
	void colVec::getSLCoordinateSystem(const utils::useSpSt st, const int num);//�Խṹ����ʽ��ȡ����ϢԤ�ж�
	void colVec::polarCoordinates(const utils::usePoint &p,float angle,float distance,utils::usePoint &cp);//������λ��
	float colVec::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2);//��ȡ����֮��ĽǶ�
	float colVec::pointAngleInfo(const POINT point1, const POINT point2);
	float colVec::bezierCurve(float p0, float p1, float p2, float t); //����������
private:
	vector <utils::usePoint> vec;//���浥λ����
	vector <vector<utils::usePoint>> points;//������״�����Ϣ
	vector <utils::usePoint> proPoint;//ͶӰ����Ϣ����ĵ��Ǵ�������ֵ����Сֵ
private:
	void colVec::clear(); //������е�Ļ���
};

