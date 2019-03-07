#include "../stdafx.h"
#include "frame2.h"
#include "frame3.h"
#include "../instance/colVec.h"
#include "aircraft.h"
#include "enemy.h"
#include "prop.h"
#include "power.h"
#include "textView.h"
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
DWORD frame3::thredId = 1;
DWORD frame3::thredId2 = 2;
DWORD frame3::thredId3 = 3;
oMap<string, vector<sprite *>> frame3::omapenemy;
vector<user * > frame3::userList;
vector<enemy * >  frame3::enemyList;
lua_State * frame3::ulua_l = luaL_newstate();
vector<power *>frame3::powerList;
vector<power *>frame3::powerUserList;
vector<prop *> frame3::propList;
vector<textView *> frame3::textViewList;
BOOL frame3::thredRun = TRUE;
BOOL frame3::thredRun2 = TRUE;
BOOL frame3::thredRun3 = TRUE;
int frame3::model = 0;
LPWSTR  frame3::modelTxt = NULL;
LPWSTR  frame3::modelTitle = NULL;
LPWSTR frame3::okTxt = L"确认";
LPWSTR frame3::noTxt = L"取消";

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
	frame3::maxBox->drawCallList.push_back(frame3::drawCallInfo);
	//敌机视图
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
	//用户飞机视图
	frame3::omapenemy["user"].push_back(new sprite(frame3::app, L"img/frame3/player/player01.png"));
	frame3::omapenemy["user"].push_back(new sprite(frame3::app, L"img/frame3/player/player02.png"));
	frame3::omapenemy["user"].push_back(new sprite(frame3::app, L"img/frame3/player/player03.png"));
	//子弹视图
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd2.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd3.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd4.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/dd.png"));
	frame3::omapenemy["power"].push_back(new sprite(frame3::app, L"img/frame3/zd5.png"));
	
	//死亡视图
	frame3::omapenemy["death"].push_back(new sprite(frame3::app, L"img/frame3/deathboom.png"));
	frame3::omapenemy["death"].push_back(new sprite(frame3::app, L"img/frame3/death2.png"));

	//界面杂项视图
	frame3::omapenemy["userView"].push_back(new sprite(frame3::app, L"img/frame3/dd2.png"));
	//道具视图
	frame3::omapenemy["prop"].push_back(new sprite(frame3::app, L"img/frame3/s1.png"));
	frame3::omapenemy["prop"].push_back(new sprite(frame3::app, L"img/frame3/s2.png"));
	frame3::omapenemy["prop"].push_back(new sprite(frame3::app, L"img/frame3/s3.png"));
	
}
void frame3::destory() {
	frame3::thredRun = FALSE;
	WaitForSingleObject(frame3::thredHandle, INFINITE);
	frame3::thredRun2 = FALSE;
	WaitForSingleObject(frame3::thredHandle2, INFINITE);
	frame3::thredRun3 = FALSE;
	WaitForSingleObject(frame3::thredHandle3, INFINITE);

	int i = 0;
	for (i = 0; i < frame3::propList.size(); i++) {
		if (frame3::removeProp(frame3::propList[i])) {
			i--;
		};
	}
	//移除敌机
	for (i = 0; i < frame3::enemyList.size(); i++) {
		if (frame3::removeEnemy(frame3::enemyList[i]->id)) {
			i--;
		};
	}
	//移除敌机子弹
	for (i = 0; i < frame3::powerList.size(); i++) {
		if (frame3::removePower(frame3::powerList[i])) {
			i--;
		};
	}
	//移除用户子弹
	for (i = 0; i < frame3::powerUserList.size(); i++) {
		if (frame3::removeUserPower(frame3::powerUserList[i])) {
			i--;
		};
	}
	//初始化Y
	frame3::drawCallY = 0;
	//移除用户飞机
	for (i = 0; i < frame3::userList.size(); i++) {
		if (frame3::removeUser(frame3::userList[i])) {
			i--;
		};
	}
};
BOOL frame3::createProp(int enId, int imgId, int type) {
	prop * pp = new prop(frame3::omapenemy["prop"][imgId]);
	pp->propType = type;
	enemy * a= frame3::getEnemy(enId);
	pp->init();
	frame3::addProp(pp);
	if (a == NULL) {
		return FALSE;
	}
	pp->view->setX(a->view->g_x);
	pp->view->setY(a->view->g_y);
	return TRUE;
};
void frame3::drawCall(sprite *sp, DemoApp *app) {

	app->content->fillImage(sp->img,0,0,sp->width,sp->height,0, frame3::drawCallY);

};
void frame3::drawCallInfo(DemoApp *app) {
	int i = 0;
	app->content->strokeStyle(0xffffff, 1);
	app->content->fillStyle(0x00ff00, 1);
	app->content->drawRect(40, 7, 100, 15);
	if ((float)frame3::userList[0]->PH <= 0) {
		app->content->fillRect(40, 7, 0, 15);
	}
	else {
		app->content->fillRect(40, 7, (float)frame3::userList[0]->PH / frame3::userList[0]->maxPH * 100, 15);
	}
	for (i = 0; i < frame3::userList[0]->isJnNum; i++) {
		app->content->drawImage(frame3::omapenemy["power"][frame3::userList[0]->jnId]->img,
			i*frame3::omapenemy["power"][frame3::userList[0]->jnId]->getWidth()+10,
			app->height - frame3::omapenemy["power"][frame3::userList[0]->jnId]->getHeight()*0.7, 
			frame3::omapenemy["power"][frame3::userList[0]->jnId]->getWidth()*0.5,
			frame3::omapenemy["power"][frame3::userList[0]->jnId]->getHeight()*0.5);
	}
	if (frame3::userList[0]->hurtEnemy != -1) {
		enemy * d = (enemy *)frame3::userList[0]->hurtEnemy;
		if (d->isDeath == 1) {
			frame3::userList[0]->hurtEnemy = -1;
		}
		if (d->name != NULL) {
			app->content->drawText(d->name, 0, 36);
			app->content->drawRect(d->stringWidth + 5, 39, 100, 15);
			app->content->fillRect(d->stringWidth + 5, 39, (float)d->PH / d->maxPH * 100, 15);
		}
	}
	
	if (frame3::model == 1) {
		app->content->fillStyle(0xff9917, 0.8);
		app->content->fillRect(30, (frame3::app->height - 500 )/ 2, frame3::app->width - 60, 500-50);
		app->content->strokeStyle(0x000000, 1);
		app->content->drawText(frame3::modelTitle, 30+10, (frame3::app->height - 500) / 2+4, frame3::app->width - 60, 30);
		app->content->fillStyle(0xffffff, 0.8);
		app->content->fillRect(30, (frame3::app->height - 500) / 2+30, frame3::app->width - 60, 500-80);
		app->content->strokeStyle(0x000000, 1);
		app->content->drawText(frame3::modelTxt, 30+10, (frame3::app->height - 500) / 2 + 30, frame3::app->width - 80, 500 - 80);


		app->content->fillStyle(0xffffff, 0.8);
		app->content->fillRect(30, (frame3::app->height - 500) / 2 + 500-30, 80, 30);
		app->content->strokeStyle(0x000000, 1);
		app->content->drawText(frame3::okTxt, 30+ 22, (frame3::app->height - 500) / 2 + 500 - 30+4, 80, 30);
		app->content->fillStyle(0xffffff, 0.8);
		app->content->fillRect(30+ frame3::app->width - 60-80, (frame3::app->height - 500) / 2 + 500 - 30, 80, 30);
		app->content->strokeStyle(0x000000, 1);
		app->content->drawText(frame3::noTxt, 30 + frame3::app->width - 60 - 80+22, (frame3::app->height - 500) / 2 + 500 - 30+4, 80, 30);

	}
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
BOOL frame3::addProp(prop * pp) {
	frame3::propList.push_back(pp);
	frame3::maxBox->addChild(pp->view);
	return TRUE;
};
BOOL frame3::addTextView(textView * tv) {
	frame3::textViewList.push_back(tv);
	frame3::maxBox->addChild(tv->view);
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
void frame3::deathCall(enemy * en) {
	lua_getglobal(frame3::ulua_l, "deathCall");
	lua_pushnumber(frame3::ulua_l, en->id);
	if (lua_pcall(frame3::ulua_l, 1, 0, 0 )!= 0) {
		utils::AlertOut(L"error:death error code",0);
		string s= lua_tostring(frame3::ulua_l, -1);
		MessageBoxA(NULL, s.c_str(), "as", MB_OK);
	}
	
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

	frame3::maxBox->removeChild(sp->view);
	frame3::enemyList.erase(s);
	/*if (sp->name != NULL) {
		free(sp->name);
	}*/
	delete sp;
	return TRUE;
};
BOOL frame3::removePower(power * pw) {
	vector<power *>::iterator s = find(frame3::powerList.begin(), frame3::powerList.end(), pw);
	if (s == frame3::powerList.end()) {
		return FALSE;
	}
	frame3::maxBox->removeChild(pw->view);
	frame3::powerList.erase(s);
	delete pw;
	return TRUE;
};
BOOL frame3::removeTextView(textView * tv) {
	vector<textView *>::iterator s = find(frame3::textViewList.begin(), frame3::textViewList.end(), tv);
	if (s == frame3::textViewList.end()) {
		return FALSE;
	}
	frame3::maxBox->removeChild(tv->view);
	frame3::textViewList.erase(s);

	delete tv;
	return TRUE;
};
BOOL frame3::removeProp(prop * pp) {
	vector<prop *>::iterator s = find(frame3::propList.begin(), frame3::propList.end(), pp);
	if (s == frame3::propList.end()) {
		return FALSE;
	}
	frame3::maxBox->removeChild(pp->view);
	frame3::propList.erase(s);
	
	delete pp;
	return TRUE;
};

BOOL frame3::removeUser(user * ur) {
	vector<user *>::iterator s = find(frame3::userList.begin(), frame3::userList.end(), ur);
	if (s == frame3::userList.end()) {
		return FALSE;
	}
	frame3::maxBox->removeChild(ur->view);
	frame3::userList.erase(s);
	delete ur;
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
	frame3::maxBox->removeChild(pw->view);
	frame3::powerUserList.erase(s);
	delete pw;
	return TRUE;
};

int frame3::showTool(LPWSTR lpw) {
	frame3::modelTxt = lpw;
	frame3::modelTitle = L"标题";
	frame3::model = 1;
	return 1;
}
void frame3::nextGk() {

	if (!(frame2::gs + 1 > frame2::gkDesList.size())) {
		frame2::gs++;
		frame3::showTool(L"恭喜过关了哦!!,点击确认进入下一关,点击取消返回选择关卡的页面");
		
	}
	else {
		MessageBoxA(frame3::app->getHwnd(), "恭喜过了最后一关了哦，好厉害", "恭喜", MB_OK);
	}
};
DWORD WINAPI frame3::threadCall(LPVOID p) {
	int i = 0;
	int len = 0;
	while (frame3::thredRun) {
		Sleep(1000 / 64);
		if (frame3::model == 1) {
			continue;
		}
		//场景背景移动
		frame3::drawCallY++;
		// 用户队列
		len = frame3::userList.size();
		for (i = 0; i < len; i++) {
			frame3::userList[i]->frame();
		}
		for (i = 0; i < frame3::propList.size(); i++) {
			if (frame3::propList[i]->frame()) {
				i--;
				continue;
			};
		}
		for (i = 0; i < frame3::textViewList.size(); i++) {
			if (frame3::textViewList[i]->frame()) {
				i--;
				continue;
			};
		}
	}
	return 1;
}
DWORD WINAPI frame3::threadCall3(LPVOID p) {
	//lua队列
	int i2 = 0;
	int i = 0;
	int len = 0;
	while (frame3::thredRun3) {
		Sleep(1000 / 64);
		if (frame3::model == 1) {
			continue;
		}
		lua_getglobal(frame3::ulua_l, "frame");
		lua_pushnumber(frame3::ulua_l, frame2::app->width);
		lua_pushnumber(frame3::ulua_l, frame2::app->height);
		lua_pushnumber(frame3::ulua_l, frame3::drawCallY);
		if (lua_pcall(frame3::ulua_l, 3, 0,0) != 0) {
			utils::AlertOut(L"error:lua frame error", 0);
			string s = lua_tostring(frame3::ulua_l, -1);
			MessageBoxA(NULL, s.c_str(), "as", MB_OK);
			return 0;
		};
		for (i2 = 0; i2 < frame3::enemyList.size(); i2++) {
			if (frame3::enemyList[i2]->frame()) {
				i2--;
				continue;
			};
			if (frame3::enemyList[i2]->isDeath != 0) {
				continue;
			}
			for (i = 0; i < frame3::powerUserList.size(); i++) {
				if (frame3::powerUserList[i]->isDeath == 0 && frame3::colObj->aabb(frame3::enemyList[i2]->view, frame3::powerUserList[i]->view)) {
					frame3::powerUserList[i]->hurtEnemy(frame3::enemyList[i2]);
					if (frame3::powerUserList[i]->powerType == 0) {
						frame3::removeUserPower(frame3::powerUserList[i]);
						i--;
						continue;
					}
					else {
						frame3::powerUserList[i]->deathCall();
					}
				}
			}
		}
		for (i = 0; i < frame3::powerUserList.size(); i++) {
			frame3::powerUserList[i]->frame();
		}

	}
	return 1;
}
DWORD WINAPI frame3::threadCall2(LPVOID p) {
	int i = 0;
	int len = 0;
	int i2 = 0;
	while (frame3::thredRun2) {
		Sleep(1000 / 64);
		if (frame3::model == 1) {
			continue;
		}
		//敌机子弹队列
		for (i = 0; i < frame3::powerList.size(); i++) {
	
			if (frame3::colObj->aabb(frame3::powerList[i]->view, frame3::userList[0]->view)) {
				frame3::powerList[i]->hurtUser(frame3::userList[0]);
				frame3::removePower(frame3::powerList[i]);
				i--;
				continue;
			}
			if (frame3::powerList[i]->frame()) {
				i--;
				continue;
			};
		}

	
	}
	return 1;
}
void frame3::visible(){
	frame3::thredRun = TRUE;
	frame3::thredRun2 = TRUE;
	frame3::thredRun3 = TRUE;
	frame3::model = 0;
	if (!frame3::firstVisible) {
		sprite * bg = new sprite(frame3::app, L"img/Interface/bg2.jpg");
		bg->width = app->width;
		bg->height = app->height;
		
		sprite * back = new sprite(frame3::app, L"img/system/back.png");
		back->zoom = 14 / 200.0;
		back->setX(8);
		back->setY(8);
		back->setId("back");
		
		sprite * drawSprite = new sprite(frame2::omapenemy["gs"][frame2::gs]->img);
		drawSprite->setId("drawSprite");
		drawSprite->spriteType = "drawSprite";
		drawSprite->setX(0);
		drawSprite->setY(0);
		drawSprite->width = frame3::app->width;
		drawSprite->height = frame3::app->height;
		drawSprite->drawCall = frame3::drawCall;


		frame3::maxBox->addChild(bg);
		frame3::maxBox->addChild(drawSprite);
		
		frame3::thredHandle = CreateThread(NULL, 0, frame3::threadCall, 0, 0, &frame3::thredId); // 创建线程
		frame3::thredHandle2 = CreateThread(NULL, 0, frame3::threadCall2, 0, 0, &frame3::thredId2); // 创建线程
		frame3::thredHandle3 = CreateThread(NULL, 0, frame3::threadCall3, 0, 0, &frame3::thredId3); // 创建线程
		
		frame3::maxBox->addChild(back);
	}
	else {
		sprite * drawSprite = frame3::maxBox->getChildById("drawSprite");
		drawSprite->img = frame2::omapenemy["gs"][frame2::gs]->img;
		frame3::thredHandle = CreateThread(NULL, 0, frame3::threadCall, 0, 0, &frame3::thredId); // 创建线程
		frame3::thredHandle2 = CreateThread(NULL, 0, frame3::threadCall2, 0, 0, &frame3::thredId2); // 创建线程
		frame3::thredHandle3 = CreateThread(NULL, 0, frame3::threadCall3, 0, 0, &frame3::thredId3); // 创建线程
	}

	//添加用户飞机
	user * ur = new user(frame3::omapenemy["user"][1], 200);
	frame3::addUser(ur);
	ur->view->g_y = app->height + ur->view->height + 10;
	ur->userType = 1;
	ur->view->setX(frame3::app->width / 2 - ur->view->width / 2);
	POINT p;
	p.x = 0;
	p.y = 0;
	ur->addSendPoint(p);
	POINT p2;
	p2.x = ur->view->getWidth();
	p2.y = 0;
	ur->addSendPoint(p2);
	//执行lua脚本
	string url = "u_lua/frame";
	stringstream ss;
	ss << url;
	ss << (frame2::gs + 1);
	url = ss.str();
	int bRet = luaL_loadfile(frame3::ulua_l, url.c_str());
	if (bRet) {
		utils::AlertOut(L"load lua file faile", 0);
	}
	lua_pcall(frame3::ulua_l, 0, 0, 0);
	frame3::firstVisible = TRUE;
};

void frame3::onClick(int x, int y) {
	sprite * sn = frame3::maxBox->getChildById("back");
	if (sn->inRect(frame3::app->mouse)) {
		frame3::app->nowScene = 2;
		frame2::visible();
		frame3::destory();
	}
	RECT rc = {
		30, (frame3::app->height - 500) / 2 + 500 - 30, 80, 30
	};
	RECT rc2 = {
		30 + frame3::app->width - 60 - 80, (frame3::app->height - 500) / 2 + 500 - 30, 80, 30
	};
	POINT * mouse = app->mouse;
	if (frame3::model == 1) {
		if ((mouse->x >= rc.left&&mouse->x <= rc.left + rc.right && mouse->y > rc.top&&mouse->y <= rc.top + rc.bottom)) {
			frame3::destory();
			frame3::visible();
		}
		if ((mouse->x >= rc2.left&&mouse->x <= rc2.left + rc2.right && mouse->y > rc2.top&&mouse->y <= rc2.top + rc2.bottom)) {
			frame3::app->nowScene = 2;
			frame2::visible();
			frame3::destory();
		}
	}
}
void frame3::keydown(int code) {
	if (!frame3::thredRun||frame3::model == 1) {
		return;
	}
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
	if (!frame3::thredRun) {
		return;
	}
	if (code == 65|| code == 68) {
		frame3::userList[0]->isMoveX = 0;
	}
	if (code == 83 || code == 87) {
		frame3::userList[0]->isMoveY = 0;
	}
	if (code == 74) {
		frame3::userList[0]->isSend = 0;
	}
	if (code == 75) {
		frame3::userList[0]->sendJn();
	}
};

