#include "../stdafx.h"
#include "frame2.h"
#include "frame3.h"
#include "../instance/colVec.h"
#include "aircraft.h"
#include "enemy.h"
#include "power.h"
#include "user.h"

//action * frame3::scene = NULL;
action *frame3::scene = NULL;
DemoApp * frame3::app = NULL;
colVec * frame3::colObj = NULL;
DisplayObject * frame3::maxBox = NULL;
float frame3::zoom = 0.7;
bool frame3::isInit = false;
vector <utils::usePoint> frame3::p1;
BOOL frame3::firstVisible = FALSE;
float frame3::drawCallY = 0;
DWORD frame3::thredId;
DWORD frame3::thredId2;
DWORD frame3::thredId3;
oMap<string, vector<sprite *>> frame3::omapenemy;
vector<user * > frame3::userList;
vector<enemy * >  frame3::enemyList;
lua_State * frame3::ulua_l = luaL_newstate();
vector<power *>frame3::powerList;
vector<power *>frame3::powerUserList;
//移动线程
HANDLE  frame3::thredHandle;
//碰撞线程
HANDLE  frame3::thredHandle2;
//lua线程
HANDLE  frame3::thredHandle3;

void frame3::init(DemoApp * app, colVec * colObj){
	frame3::scene = new action(app);
	frame3::app = app;
	//frame3::scene->addTicker(frame3::tk1);
	frame3::colObj = colObj;
	app->use_onClick["frame3"] = frame3::onClick;
	app->use_onKeyDown["frame3"] = frame3::keydown;
	app->use_onKeyUp["frame3"] = frame3::keyup;
	frame3::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame3::maxBox);
	frame3::firstVisible = FALSE;

	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy01.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy02.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy03.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy04.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy05.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy06.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy07.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy08.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy09.png"));
	frame3::omapenemy["enemy"].push_back(new sprite(frame3::app, L"img/frame3/enemy/enemy010.png"));
	frame3::omapenemy["user"].push_back(new sprite(frame3::app, L"img/frame3/player.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd2.png"));
	frame3::omapenemy["death"].push_back(new sprite(frame3::app, L"img/frame3/deathboom.png"));
}
void frame3::destory() {
	
};
void frame3::drawCall(sprite *sp, DemoApp *app) {

	app->content->fillImage(sp->img,0,0,sp->width,sp->height,0, frame3::drawCallY);
};
BOOL frame3::addUser(user * u) {
	frame3::userList.push_back(u);
	frame3::maxBox->addChild(u->view);
	return TRUE;
};
BOOL frame3::addPower(power * pw) {
	frame3::powerList.push_back(pw);
	frame3::maxBox->addChild(pw->view);
	pw->isUser = 0;
	return TRUE;
};
BOOL frame3::addUserPower(power * pw) {
	frame3::powerUserList.push_back(pw);
	frame3::maxBox->addChild(pw->view);
	pw->isUser = 1;
	return TRUE;
};
BOOL frame3::addEnemy(enemy * en) {
	frame3::enemyList.push_back(en);
	frame3::maxBox->addChild(en->view);
	return TRUE;
}
enemy * frame3::getEnemy(int id) {
	int i = 0;
	for (i = 0; i < frame3::enemyList.size(); i++) {
		if (id == frame3::enemyList[i]->id) {

			return frame3::enemyList[i];
		}
	}
	
	return NULL;
};
BOOL frame3::removeEnemy(int id) {
	
	enemy * sp = frame3::getEnemy(id);
	
	if (sp == NULL) {
		
		return FALSE;
	}
	
	vector<enemy *>::iterator s = find(frame3::enemyList.begin(), frame3::enemyList.end(), sp);
	if ( s== frame3::enemyList.end()) {
		return FALSE;
	}
	frame3::enemyList.erase(s);
	frame3::maxBox->removeChild(sp->view);
	return TRUE;
};
BOOL frame3::removePower(power * pw) {
	vector<power *>::iterator s = find(frame3::powerList.begin(), frame3::powerList.end(), pw);
	if (s == frame3::powerList.end()) {
		return FALSE;
	}
	frame3::powerList.erase(s);
	frame3::maxBox->removeChild(pw->view);
	return TRUE;
};
BOOL frame3::removePowerEx(power * pw) {
	if (pw->isUser == 0) {
		return frame3::removePower(pw);
	}
	else {
		return frame3::removeUserPower(pw);
	}
};
BOOL frame3::removeUserPower(power * pw) {
	vector<power *>::iterator s = find(frame3::powerUserList.begin(), frame3::powerUserList.end(), pw);
	if (s == frame3::powerUserList.end()) {
		return FALSE;
	}
	frame3::powerUserList.erase(s);
	frame3::maxBox->removeChild(pw->view);
	return TRUE;
};
DWORD WINAPI frame3::threadCall(LPVOID p) {
	int i = 0;
	int len = 0;
	while (true) {
		Sleep(1000 / 64);
		//场景背景移动
		frame3::drawCallY++;
		// 用户队列
		len = frame3::userList.size();
		for (i = 0; i < len; i++) {
			frame3::userList[i]->frame();
		}
	}
	return 1;
}
DWORD WINAPI frame3::threadCall3(LPVOID p) {
	//lua队列
	int i = 0;
	int len = 0;
	while (true) {
		Sleep(1000 / 64);
		lua_getglobal(frame3::ulua_l, "frame");
		lua_pushnumber(frame3::ulua_l, frame2::app->width);
		lua_pushnumber(frame3::ulua_l, frame2::app->height);
		lua_pushnumber(frame3::ulua_l, frame3::drawCallY);
		lua_pcall(frame3::ulua_l, 3, 1, 0);
	}

}
DWORD WINAPI frame3::threadCall2(LPVOID p) {
	int i = 0;
	int len = 0;
	int i2 = 0;
	while (true) {
		Sleep(1000 / 64);
		
		//敌机子弹队列
		for (i = 0; i < frame3::powerList.size(); i++) {
			if (frame3::colObj->aabb(frame3::powerList[i]->view, frame3::userList[0]->view)) {
				frame3::powerList[i]->hurtUser(frame3::userList[0]);
				frame3::removePower(frame3::powerList[i]);
				i--;
				break;
			}
			if (frame3::powerList[i]->frame()) {
				i--;
				break;
			};
		}
		for (i = 0; i < frame3::powerUserList.size(); i++) {
			frame3::powerUserList[i]->frame();
		}

		for (i2 = 0; i2 < frame3::enemyList.size(); i2++) {
			if (frame3::enemyList[i2]->frame()) {
				i--;
				break;
			};
			for (i = 0; i < frame3::powerUserList.size(); i++) {
				if (frame3::enemyList[i2]->isDeath == 0 && frame3::colObj->aabb(frame3::enemyList[i2]->view, frame3::powerUserList[i]->view)) {
					frame3::powerUserList[i]->hurtEnemy(frame3::enemyList[i2]);
					frame3::removeUserPower(frame3::powerUserList[i]);
					i--;
					break;
				}
			}
		}
		
		
	
	}
	return 1;
}
void frame3::visible(){
	if (!frame3::firstVisible) {
		sprite * bg = new sprite(frame3::app, L"img/Interface/bg2.jpg");
		bg->width = app->width;
		bg->height = app->height;
		
		sprite * back = new sprite(frame3::app, L"img/system/back.png");
		back->zoom = 14 / 200.0;
		back->setX(8);
		back->setY(8);
		back->setId("back");
		
		sprite * drawSprite = new sprite(frame3::app, L"img/frame2/gameBg1.jpg");
		drawSprite->spriteType = "drawSprite";
		drawSprite->setX(0);
		drawSprite->setY(0);
		drawSprite->width = frame3::app->width;
		drawSprite->height = frame3::app->height;
		drawSprite->drawCall = frame3::drawCall;


		frame3::maxBox->addChild(bg);
		frame3::maxBox->addChild(drawSprite);
		
		frame3::thredHandle= CreateThread(NULL, 0, frame3::threadCall, 0, 0, &frame3::thredId); // 创建线程
		frame3::thredHandle2 = CreateThread(NULL, 0, frame3::threadCall2, 0, 0, &frame3::thredId2); // 创建线程
		frame3::thredHandle3 = CreateThread(NULL, 0, frame3::threadCall3, 0, 0, &frame3::thredId3); // 创建线程
		user * ur =new user(frame3::omapenemy["user"][0],200);
		frame3::addUser(ur);
		ur->view->g_y = app->height + ur->view->height + 10;
		ur->userType = 1;
		ur->view->setX(frame3::app->width / 2 - ur->view->width / 2);
		frame3::maxBox->addChild(back);
		int bRet = luaL_loadfile(frame3::ulua_l, "u_lua/frame1");
		if (bRet) {
			utils::AlertOut(L"load lua file faile", 0);
		}
		lua_pcall(frame3::ulua_l, 0, 0, 0);
		

	}
	
	frame3::firstVisible = TRUE;
};

void frame3::onClick(int x, int y) {
	sprite * sn = frame3::maxBox->getChildById("back");
	if (sn->inRect(frame3::app->mouse)) {
		frame3::app->nowScene = 2;
		frame2::visible();
	}
}
void frame3::keydown(int code) {
	if (frame3::userList[0]->userType == 0) {
		
		if (code == 83) {
			frame3::userList[0]->isMoveY = 1;
			frame3::userList[0]->moveTypeY = 1;
		}
		else if (code == 87) {
			frame3::userList[0]->isMoveY = 1;
			frame3::userList[0]->moveTypeY = 0;
		}
		if (code == 65) {
			frame3::userList[0]->isMoveX = 1;
			frame3::userList[0]->moveTypeX = 0;
		}
		else if (code == 68) {
			frame3::userList[0]->isMoveX = 1;
			frame3::userList[0]->moveTypeX = 1;
		}
		else if (code == 74) {
			frame3::userList[0]->isSend = 1;
		}
	}

};

void frame3::keyup(int code) {
	if (code == 65|| code == 68) {
		frame3::userList[0]->isMoveX = 0;
	}
	if (code == 83 || code == 87) {
		frame3::userList[0]->isMoveY = 0;
	}
	if (code == 74) {
		frame3::userList[0]->isSend = 0;
	
	}
};

