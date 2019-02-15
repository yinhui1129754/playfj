#include "../stdafx.h"
#include "frame2.h"
#include "frame3.h"
#include "../instance/colVec.h"
#include "aircraft.h"
#include "enemy.h"
#include "power.h"
#include "user.h"
#include "frame_lua.h"
void frame_lua::init() {
	/* 注册函数 */
	//string
	lua_register(frame3::ulua_l, "debugOut", frame_lua::debugOut);
	//imgId PH x y zoom moveType speed
	lua_register(frame3::ulua_l, "u_createEnemy", frame_lua::createEnemy);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyX", frame_lua::setEnemyX);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyY", frame_lua::setEnemyY);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyMoveTypeY", frame_lua::setEnemyMoveTypeY);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyMoveTypeX", frame_lua::setEnemyMoveTypeX);
	//enemy id 
	lua_register(frame3::ulua_l, "u_getEnemyY", frame_lua::getEnemyY);
	//enemy id 
	lua_register(frame3::ulua_l, "u_getEnemyX", frame_lua::getEnemyX);
	//enemy id
	lua_register(frame3::ulua_l, "u_removeEnemy", frame_lua::removeEnemy);
	//imgId
	lua_register(frame3::ulua_l, "u_getImgWidth", frame_lua::getImgWidth);
	lua_register(frame3::ulua_l, "u_getImgHeight", frame_lua::getImgHeight);
 
	//注册函数库
	luaL_requiref(frame3::ulua_l, "math", luaopen_math, 1);
	lua_pop(frame3::ulua_l, 1);
	luaL_requiref(frame3::ulua_l, "os", luaopen_os, 1);
	lua_pop(frame3::ulua_l, 1);
}
static int frame_lua::setEnemyMoveTypeX(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int val =lua_tonumber(L, 2);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		lua_pushnumber(L, 1);
	}
	a->moveType2 = val;
	return 1;
};
static int frame_lua::setEnemyMoveTypeY(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int val = lua_tonumber(L, 2);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		lua_pushnumber(L, 1);
	}
	a->moveType = val;
	return 1;
};
static int frame_lua::getImgWidth(lua_State * L) {
	int n = lua_gettop(L);
	int imgId = lua_tonumber(L, 1);
	if (imgId <= frame3::omapenemy["enemy"].size() - 1) {
		lua_pushnumber(L, frame3::omapenemy["enemy"][imgId]->getWidth());
	}
	else {
		lua_pushnumber(L, -1);
	}
	return 1;
};
static int frame_lua::getImgHeight(lua_State * L) {
	int n = lua_gettop(L);
	int imgId = lua_tonumber(L, 1);
	if (imgId <= frame3::omapenemy["enemy"].size() - 1) {
		lua_pushnumber(L, frame3::omapenemy["enemy"][imgId]->getHeight());
	}
	else {
		lua_pushnumber(L, -1);
	}
	return 1;
};
static int frame_lua::debugOut(lua_State * L) {
	int n = lua_gettop(L);
	string s;
	for (int i = 1; i <= n; i++) {
		s += lua_tostring(L, i);
	}
	utils::DebugOut(utils::user_stringToLPWSTR(s), 0);
	
	return 0;
}
static int frame_lua::removeEnemy(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	
	frame3::removeEnemy(enId);
	return 0;
};
static int frame_lua::createEnemy(lua_State * L) {
	int n = lua_gettop(L);
	int imgId = lua_tointeger(L, 1);//图片id
	int PH = lua_tointeger(L, 2);//生命值
	int X = lua_tointeger(L, 3);//初始X
	int Y = lua_tointeger(L, 4);//初始Y
	float zoom = lua_tonumber(L, 5);//缩放
	int moveType = lua_tonumber(L, 6);//移动类型
	float  speed = lua_tonumber(L, 7);//移动速度
	enemy * en = new enemy(frame3::omapenemy["enemy"][imgId], PH);
	en->view->setX(X);
	en->view->setY(Y);
	en->view->zoom = zoom;
	en->speed = speed;
	en->moveType = moveType;
	en->deathView = new sprite(frame3::omapenemy["death"][0]->img);
	en->deathHeight = 92;
	en->deathWidth = 94;
	en->deathFrame = 0;
	frame3::addEnemy(en);
	lua_pushnumber(L, en->id);
	return 1;
}
static int frame_lua::setEnemyX(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	
	enemy * a = frame3::getEnemy(enId);
	//utils::DebugOut(L"id %d \n", enId);
	if (a == NULL) {
		
		return 0;
	}
	a->view->setX(x);
	return 0;
}
static int frame_lua::getEnemyX(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	enemy * a = frame3::getEnemy(enId);
	//utils::DebugOut(L"id %d \n", enId);
	if (a == NULL) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushnumber(L, a->view->g_x);
	return 1;
}
static int frame_lua::getEnemyY(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);

	enemy * a = frame3::getEnemy(enId);

	if (a == NULL) {
		
		lua_pushnil(L);
		return 1;
	}
	lua_pushnumber(L, a->view->g_y);
	return 1;
}
static int frame_lua::setEnemyY(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		return 0;
	}
	a->view->setY(y);
	return 0;
}
static int frame_lua::getEnemyWidth(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushnumber(L, a->view->getWidth());
	return 1;
};
static int frame_lua::getEnemyHeight(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushnumber(L, a->view->getHeight());
	return 1;
};