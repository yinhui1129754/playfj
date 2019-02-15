#pragma once
extern class action;
extern class DemoApp;
extern class user;
extern class enemy;
extern class power;
//���������ֿռ������ֳ���~~
 namespace frame3{
	 //���� һ���г����ĸ���
	extern action * scene ;
	//�ṩ���� ��Ⱦѭ���ĺ���һ������
	extern DemoApp * app;
	//��ײ�߼��������
	extern colVec *colObj;
	//��������
	extern DisplayObject * maxBox;
	//�������� 0-1
	extern float zoom;
	extern bool isInit;
	extern void init(DemoApp * app, colVec * colObj);
	
	extern void visible();
	extern vector <utils::usePoint> p1;

	//�����رյĴ�����
	extern void destory();
	extern BOOL firstVisible;
	
	//��ͼ�ص�
	extern void drawCall(sprite *sp, DemoApp *app);
	extern float drawCallY;
	
	//�߼��߳�
	extern DWORD thredId;
	extern DWORD WINAPI threadCall(LPVOID p);
	extern HANDLE thredHandle;


	extern DWORD thredId2;
	extern DWORD WINAPI threadCall2(LPVOID p);
	extern HANDLE thredHandle2;

	extern DWORD thredId3;
	extern DWORD WINAPI threadCall3(LPVOID p);
	extern HANDLE thredHandle3;
	//��������
	extern oMap<string, vector<sprite *>> omapenemy; //��Դ��������

	//��������
	extern vector<user * > userList;
	extern BOOL addUser(user *);
	extern vector<enemy * > enemyList;
	extern BOOL addEnemy(enemy *);
	extern enemy * getEnemy(int id);
	extern BOOL removeEnemy(int id);

	//�ӵ����
	extern vector<power *> powerList;
	extern BOOL addPower(power *);
	extern BOOL removePower(power *);
	extern BOOL removePowerEx(power *);
	extern vector<power *> powerUserList;
	extern BOOL addUserPower(power *);
	extern BOOL removeUserPower(power *);
	//��Ϣ�ص�����
	extern void onClick(int x, int y);
	extern void keydown( int);
	extern void keyup( int);

	//lua
	//1.����Lua״̬  
	extern lua_State * ulua_l;
//	int bRet = luaL_loadfile(L, "u_lua/frae1");
	//bRet = lua_pcall(L, 0, 0, 0);
}