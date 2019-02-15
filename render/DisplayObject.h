#pragma once
//#include "DemoApp.h"
class DemoApp;
class sprite;
class DisplayObject
{
public:
	DisplayObject();
	~DisplayObject();
	virtual int addChild(sprite * child);
	virtual int removeChild(sprite * child);
	virtual void render(DemoApp * app);
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setX(int x);
	virtual void setY(int y);
	virtual void setId(string id);
	virtual float getWidth();
	virtual float getHeight();
	DisplayObject(float x, float y);
	virtual sprite *  DisplayObject::getChildById(string id);
	virtual bool DisplayObject::inRect(POINT * pt);
	virtual void initG_x();
	virtual void initG_y();

public:
	string status = "DisplayObject";
	POINT scale;//��������
	utils::usePoint pivot = {0.5,0.5};//�任����ϵԭ��0-1�����sprite���
	int angle;//�Ƕ�
	float width = 0;
	float height = 0;
	float x = 0;//�ֲ�����ϵx
	float y = 0;//�ֲ�����ϵy
	float g_x = 0;//ȫ������ϵX
	float g_y = 0;//ȫ������ϵY
	float zoom = 1;
	bool visible = true;
	string id = "";
	//����ʾ��������
	vector <sprite * >children;
	sprite * parent = NULL;
	oMap<string,int> use_int;
	oMap<string, string>use_str;


};

