#pragma once
#include "DisplayObject.h"
extern class DemoApp;
class sprite :public DisplayObject
{
public:
	//textSprite
	sprite(int x,int y);
	//default
	sprite(DemoApp * app, WCHAR * url, string spriteType="default",int width=-1,int height = -1);
	sprite(DemoApp * app, ID2D1Bitmap * url, string spriteType = "default", int width = -1, int height = -1);
	sprite(ID2D1Bitmap *url, string spriteType = "default", int w2=-1, int h2=-1);
	~sprite();
	//drawSprite
	sprite(DemoApp*app);
	sprite(DemoApp *app, void(*drawCall)(sprite *sp,DemoApp *app));
	virtual void render(DemoApp*);
	u_rect * frame = NULL;
public:
	ID2D1Bitmap * img;
	string  status = "sprite";
	string spriteType = "default";//animateSprite fillSprite textSprite
	
	
	//animateSprite
	vector<u_rect  >frameArr;//帧数组
	unsigned int nowFrame = 0;//当前帧
	float speedTime = 0;//毫秒
	float speedNowTime = 0;//毫秒
	int loop = -1;
	void (*amtEnd)(sprite *);
	//fillSprite

	//textSprite
	string txt = "";
	UINT rgb = 0x000000;
	float  alpha = 1;
	float getTxtWidth(DemoApp * app);
	float getTxtHeight(DemoApp * app);

	//drawSprite
	DemoApp * app = NULL;
	void (*drawCall)(sprite *sp,DemoApp *app);
};

