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
	//imgId PH x y zoom moveType speed enemyType powerType
	lua_register(frame3::ulua_l, "u_createEnemy", frame_lua::createEnemy);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyX", frame_lua::setEnemyX);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyY", frame_lua::setEnemyY);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyMoveTypeY", frame_lua::setEnemyMoveTypeY);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyMoveTypeX", frame_lua::setEnemyMoveTypeX);
	//enemy id val
	lua_register(frame3::ulua_l, "u_setEnemyPowerNum", frame_lua::setEnemyPowerNum);


	//enemy id  获取敌机的x y
	lua_register(frame3::ulua_l, "u_getEnemyY", frame_lua::getEnemyY);
	//enemy id 
	lua_register(frame3::ulua_l, "u_getEnemyX", frame_lua::getEnemyX);
	//enemy id
	lua_register(frame3::ulua_l, "u_removeEnemy", frame_lua::removeEnemy);
	//enemy id type val
	lua_register(frame3::ulua_l, "u_setEnemyAttr", frame_lua::setEnemyAttr);
	//enemy id x y 
	lua_register(frame3::ulua_l, "u_addEnemyAutoSend", frame_lua::addEnemyAutoSend);
	
	//imgId 获取图片宽度和高度
	lua_register(frame3::ulua_l, "u_getImgWidth", frame_lua::getImgWidth);
	lua_register(frame3::ulua_l, "u_getImgHeight", frame_lua::getImgHeight);
	//设置单位名称
	lua_register(frame3::ulua_l, "u_setEnemyName", frame_lua::setEnemyName);
	//设置单位名称
	lua_register(frame3::ulua_l, "u_nextGs", frame_lua::nextGs);

	//创建道具 enId imgId type
	lua_register(frame3::ulua_l, "nu_createProp", frame_lua::createProp);

	luaL_openlibs(frame3::ulua_l);


	//frame2
	lua_register(frame2::ulua_l, "u_addGs", frame_lua::addGs);
	luaL_openlibs(frame2::ulua_l);

}
//frame2
static int frame_lua::addGs(lua_State * L) {
	int n = lua_gettop(L);
	string gkurl = lua_tostring(L, 1);
	string gkDes = lua_tostring(L, 2);
	LPWSTR gkUrl2 = utils::user_stringToLPWSTR(gkurl);
	LPWSTR gkDes2 = utils::user_stringToLPWSTR(gkDes);
	frame2::omapenemy["gs"].push_back(new sprite(frame2::app, gkUrl2));
	frame2::gkDesList.push_back(gkDes2);
	return 0;
}

//frame3
static int frame_lua::nextGs(lua_State * L) {
	frame3::nextGk();
	return 0;
}

static int frame_lua::createProp(lua_State * L){
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int imgId = lua_tonumber(L, 2);
	int type = lua_tonumber(L, 3);
	frame3::createProp(enId, imgId, type);
	return 0;
};

static int frame_lua::setEnemyPowerNum(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int val = lua_tonumber(L, 2);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		a->powerNum = val;
		lua_pushnumber(L, 1);
	}

	return 1;
};
static int frame_lua::setEnemyName(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	string  val = lua_tostring(L,2);
	LPWSTR val2 = utils::user_stringToLPWSTR(val);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		a->setName(val2);
		lua_pushnumber(L, 1);
	}
	return 1;
}
static int frame_lua::setEnemyAttr(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int type = lua_tonumber(L, 2);
	int num = lua_tonumber(L, 3);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		switch (type) {
		case 0:
			//y轴加帧的数量
			a->addNumFrame = num;
			break;
		case 1:
			//y轴减帧的数量
			a->subNumFrame = num;
			break;
		case 2:
			//发送子弹类型
			a->powerType = num;
			break;
		case 3:
			//自动发射子弹类型
			a->powerTypeAuto = num;
			break;
			//发射子弹图片id
		case 4:
			a->powerId = num;
			break;
		case 5:
			//自动发射子弹图片id
			a->powerIdAuto = num;
			break;
		case 6:
			a->isShowPH = num;
			break;
		}
		lua_pushnumber(L, 1);
	}

	return 1;
};

static int frame_lua::addEnemyAutoSend(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int x = lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		POINT p;
		p.x = x;
		p.y = y;
		a->addSendPoint(p);
		lua_pushnumber(L, 1);
	}
	return 1;
};
static int frame_lua::setEnemyMoveTypeX(lua_State * L) {
	int n = lua_gettop(L);
	int enId = lua_tonumber(L, 1);
	int val =lua_tonumber(L, 2);
	enemy * a = frame3::getEnemy(enId);
	if (a == NULL) {
		lua_pushnumber(L, -1);
	}
	else {
		a->moveType2 = val;
		lua_pushnumber(L, 1);
	}
	
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
		a->moveType = val;
		lua_pushnumber(L, 1);
	}
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
	int enemyType = lua_tonumber(L, 8);//敌机类型
	int powerType = lua_tonumber(L, 9);//子弹类型
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
	en->enemyType = enemyType;
	en->powerType = powerType;
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