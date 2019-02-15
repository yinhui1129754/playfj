#pragma once
class action;
class DemoApp;
 namespace frame1{
	extern action * scene ;
	extern DemoApp * app;
	extern colVec *colObj;
	extern DisplayObject * maxBox;
	extern float zoom;
	extern bool isInit;
	extern void init(DemoApp * app, colVec * colObj);
	extern void onClick(int x, int y);
	extern void visible();
	extern vector <utils::usePoint> p1;
	extern void tk1FunC(DemoApp **app, ticker * tk);
	extern void destory();
	extern BOOL firstVisible;
}