#pragma once
class action;
class DemoApp;
 namespace frame2{
	extern action * scene ;
	extern DemoApp * app;
	extern colVec *colObj;
	extern DisplayObject * maxBox;
	extern float zoom;
	extern bool isInit;
	extern void init(DemoApp * app, colVec * colObj);
	extern void onClick(int x, int y);
	extern void mouseMove(int x, int y);
	extern void visible();
	extern vector <utils::usePoint> p1;
	extern void tk1FunC(DemoApp **app, ticker * tk);
	extern void destory();
	extern BOOL firstVisible;
	extern void drawCall(sprite *sp, DemoApp *app);
	
	//�ؿ�
	extern LPWSTR gkdes;
	extern vector<LPWSTR> gkDesList;
	extern int gs;
	extern lua_State * ulua_l;
	//��������
	extern oMap<string, vector<sprite *>> omapenemy; //��Դ��������
}