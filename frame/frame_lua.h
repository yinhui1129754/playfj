#pragma once
extern class action;
extern class DemoApp;
extern class user;
extern class enemy;
extern class power;
//我们用名字空间来区分场景~~
 namespace frame_lua{
	 void init();
	 static int debugOut(lua_State * L);
	 //enemy 
	 static int createEnemy(lua_State * L);
	 static int setEnemyX(lua_State * L);
	 static int setEnemyY(lua_State * L);
	 static int getEnemyX(lua_State * L);
	 static int getEnemyY(lua_State * L);
	 static int removeEnemy(lua_State * L);
	 static int getEnemyWidth(lua_State * L);
	 static int getEnemyHeight(lua_State * L);
	 static int getImgWidth(lua_State * L);
	 static int getImgHeight(lua_State * L);
	 static int setEnemyMoveTypeX(lua_State * L);
	 static int setEnemyMoveTypeY(lua_State * L);
	 static int setEnemyPowerNum(lua_State * L);
	 static int setEnemyAttr(lua_State * L);
	 static int addEnemyAutoSend(lua_State * L);
	 static int setEnemyName(lua_State *L);
	 static int nextGs(lua_State *L);
	 //非enemy
	 static int createProp(lua_State * L);

	 //frame2
	 static int addGs(lua_State * L);
}