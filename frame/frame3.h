#pragma once
extern class action;
extern class DemoApp;
extern class user;
extern class enemy;
extern class power;
//我们用名字空间来区分场景~~
 namespace frame3{
	 //场景 一个有场景的概念
	extern action * scene ;
	//提供窗口 渲染循环的核心一个对象
	extern DemoApp * app;
	//碰撞逻辑处理对象
	extern colVec *colObj;
	//最大的容器
	extern DisplayObject * maxBox;
	//缩放因素 0-1
	extern float zoom;
	extern bool isInit;
	extern void init(DemoApp * app, colVec * colObj);
	
	extern void visible();
	extern vector <utils::usePoint> p1;

	//场景关闭的处理函数
	extern void destory();
	extern BOOL firstVisible;
	
	//绘图回调
	extern void drawCall(sprite *sp, DemoApp *app);
	extern float drawCallY;
	
	//逻辑线程
	extern DWORD thredId;
	extern DWORD WINAPI threadCall(LPVOID p);
	extern HANDLE thredHandle;


	extern DWORD thredId2;
	extern DWORD WINAPI threadCall2(LPVOID p);
	extern HANDLE thredHandle2;

	extern DWORD thredId3;
	extern DWORD WINAPI threadCall3(LPVOID p);
	extern HANDLE thredHandle3;
	//控制属性
	extern oMap<string, vector<sprite *>> omapenemy; //资源缓存类型

	//操作方法
	extern vector<user * > userList;
	extern BOOL addUser(user *);
	extern vector<enemy * > enemyList;
	extern BOOL addEnemy(enemy *);
	extern enemy * getEnemy(int id);
	extern BOOL removeEnemy(int id);

	//子弹相关
	extern vector<power *> powerList;
	extern BOOL addPower(power *);
	extern BOOL removePower(power *);
	extern BOOL removePowerEx(power *);
	extern vector<power *> powerUserList;
	extern BOOL addUserPower(power *);
	extern BOOL removeUserPower(power *);
	//消息回调函数
	extern void onClick(int x, int y);
	extern void keydown( int);
	extern void keyup( int);

	//lua
	//1.创建Lua状态  
	extern lua_State * ulua_l;
//	int bRet = luaL_loadfile(L, "u_lua/frae1");
	//bRet = lua_pcall(L, 0, 0, 0);
}