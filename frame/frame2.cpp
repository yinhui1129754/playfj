#include "../stdafx.h"
#include "frame0.h"
#include "frame2.h"
#include "frame3.h"
#include "../instance/colVec.h"
//action * frame2::scene = NULL;
action *frame2::scene = NULL;
DemoApp * frame2::app = NULL;
colVec * frame2::colObj = NULL;
DisplayObject * frame2::maxBox = NULL;
float frame2::zoom = 0.7;
bool frame2::isInit = false;
vector <utils::usePoint> frame2::p1;
BOOL frame2::firstVisible = FALSE;
int frame2::gs = 0;
oMap<string, vector<sprite *>> frame2::omapenemy;
LPWSTR frame2::gkdes = L"";
vector<LPWSTR> frame2::gkDesList;
lua_State * frame2::ulua_l = luaL_newstate();
void frame2::init(DemoApp * app, colVec * colObj){
	frame2::scene = new action(app);
	frame2::app = app;
	//frame2::scene->addTicker(frame2::tk1);
	frame2::colObj = colObj;
	app->use_onClick["frame2"] = frame2::onClick;
	app->use_onMouseMove["frame2"] = frame2::mouseMove;
	frame2::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame2::maxBox);
	frame2::firstVisible = FALSE;
	/*frame2::omapenemy["gs"].push_back(new sprite(frame2::app, L"img/frame2/gameBg1.jpg"));
	frame2::omapenemy["gs"].push_back(new sprite(frame2::app, L"img/frame2/2dBg1.jpg"));

	frame2::gkDesList.push_back(L"这是第一关,这里有很简单和很少的敌人和较短的关卡时间");
	frame2::gkDesList.push_back(L"这是第二关,这里有很简单和很少的敌人和较短的关卡时间,这里的作战是再太空上哦");*/


	frame2::omapenemy["next"].push_back(new sprite(frame2::app, L"img/frame2/syy_1.png"));
	frame2::omapenemy["next"].push_back(new sprite(frame2::app, L"img/frame2/syy_2.png"));
	frame2::omapenemy["next"].push_back(new sprite(frame2::app, L"img/frame2/xyy_1.png"));
	frame2::omapenemy["next"].push_back(new sprite(frame2::app, L"img/frame2/xyy_2.png"));
}
void frame2::destory() {

};
void frame2::drawCall(sprite *sp, DemoApp *app) {
	IDWriteTextFormat * u_forMat = app->content->createFont(32.0,L"微软雅黑");
	wstringstream ss;
	ss << L"第" ;
	ss << (frame2::gs+1);
	ss << L"关";
	app->content->strokeStyle(0xffffff, 1);
	D2D1_SIZE_F SF;
	app->content->getTextInfo((LPWSTR)(ss.str().c_str()), SF);
	app->content->drawText((LPWSTR)ss.str().c_str(),app->width/2-SF.width/2*32/16,40, u_forMat);

	app->content->drawText((LPWSTR)ss.str().c_str(), app->width / 2 - SF.width / 2 * 32 / 16, 40, u_forMat);
	app->content->drawText(frame2::gkdes, 10, 100, app->width - 20, 200);
	u_forMat->Release();
	u_forMat = NULL;
};
void frame2::visible(){
	if (!frame2::firstVisible) {
		string url = "frame2.lua";
		int bRet = luaL_loadfile(frame2::ulua_l, url.c_str());
		if (bRet) {
			utils::AlertOut(L"load lua file faile", 0);
		}
		lua_pcall(frame2::ulua_l, 0, 0, 0);
		sprite * bg = new sprite(frame2::app, L"img/Interface/bg2.jpg");
		bg->width = app->width;
		bg->height = app->height;
		
		sprite * back = new sprite(frame2::app, L"img/system/back.png");
		back->zoom = 14 / 200.0;
		back->setX(8);
		back->setY(8);
		back->setId("back");
			
		sprite * text2 = new sprite(0, 0);
		text2->spriteType = "textSprite";
		text2->txt = "请选择关数";
		text2->rgb = 0xffffff;
		int width = text2->getTxtWidth(frame2::app);
		text2->setX((frame2::app->width- width)/2);
		text2->setY(4);
		text2->width = width;
		text2->height = 45;
		
		sprite * gs1 = new sprite(frame2::omapenemy["gs"][frame2::gs]->img);
		frame2::gkdes = frame2::gkDesList[frame2::gs];
		gs1->setId("gs1");
		gs1->width = 300;
		gs1->height = 350;
		u_rect * rt = new u_rect;
		rt->x = 0;
		rt->y = 0;
		rt->width = gs1->img->GetSize().width;
		rt->height = 350;
		gs1->frame = rt;
		gs1->setX(frame2::app->width / 2 - gs1->width / 2);
		gs1->setY(frame2::app->height / 2 - gs1->height / 2);

		sprite * begin = new sprite(frame2::app,L"img/Interface/sign.png");
		begin->zoom = 0.8;
		begin->setX(frame2::app->width / 2 - begin->getWidth() / 2);
		begin->setY(frame2::app->height - begin->getHeight() - 60);
		begin->setId("begin");

		sprite * dSpri = new sprite(frame2::app, frame2::drawCall);
		dSpri->spriteType = "drawSprite";
		sprite * xyy = new sprite(frame2::omapenemy["next"][0]->img);
		xyy->setX(0+10);
		xyy->zoom = 0.25;
		xyy->setId("xyy");
		xyy->setY(frame2::app->height/2- xyy->getHeight()/2);
		
		sprite * syy = new sprite(frame2::omapenemy["next"][2]->img);
		syy->zoom = 0.25;
		syy->setX(frame2::app->width- syy->getWidth()-10);
		syy->setY(frame2::app->height / 2 - syy->getHeight() / 2);

		syy->setId("syy");
		
		frame2::maxBox->addChild(bg);
		frame2::maxBox->addChild(back);
		frame2::maxBox->addChild(text2);
		frame2::maxBox->addChild(gs1);
		frame2::maxBox->addChild(begin);
		frame2::maxBox->addChild(dSpri);
		frame2::maxBox->addChild(xyy);
		frame2::maxBox->addChild(syy);
		
		frame2::firstVisible = TRUE;
	}
	else {
		sprite * gs1 = frame2::maxBox->getChildById("gs1");
		gs1->img = frame2::omapenemy["gs"][frame2::gs]->img;
		frame2::gkdes = frame2::gkDesList[frame2::gs];
		gs1->setId("gs1");
	}

};
void frame2::tk1FunC(DemoApp **app, ticker * tk) {

}
void frame2::mouseMove(int x, int y) {
	sprite * syy = frame2::maxBox->getChildById("syy");
	sprite * xyy = frame2::maxBox->getChildById("xyy");
	if (xyy->inRect(frame2::app->mouse)) {
		xyy->img = frame2::omapenemy["next"][1]->img;
	}
	else {
		xyy->img = frame2::omapenemy["next"][0]->img;
	}
	if (syy->inRect(frame2::app->mouse)) {
		syy->img = frame2::omapenemy["next"][3]->img;
	}else{
		syy->img = frame2::omapenemy["next"][2]->img;
	}
}
void frame2::onClick(int x, int y) {
	sprite * sn = frame2::maxBox->getChildById("back");
	sprite * begin = frame2::maxBox->getChildById("begin");
	sprite * gs1=frame2::maxBox->getChildById("gs1");
	sprite * syy = frame2::maxBox->getChildById("syy");
	sprite * xyy = frame2::maxBox->getChildById("xyy");
	if (sn->inRect(frame2::app->mouse)) {
		frame2::app->nowScene = 0;
		frame0::visible();
		frame2::destory();
	}
	else if (begin->inRect(frame2::app->mouse)) {
		frame2::app->nowScene = 3;
		frame3::visible();
		frame2::destory();
	}
	if (syy->inRect(frame2::app->mouse)) {
		if (frame2::gs +1> frame2::omapenemy["gs"].size() - 1) {
			frame2::gs = 0;
		}
		else {
			frame2::gs++;
		}
		gs1->img = frame2::omapenemy["gs"][frame2::gs]->img;
		frame2::gkdes = frame2::gkDesList[frame2::gs];
	}
	if (xyy->inRect(frame2::app->mouse)) {
		if (frame2::gs - 1 <0) {
			frame2::gs = frame2::omapenemy["gs"].size() - 1;
		}
		else {
			frame2::gs--;
		}
		gs1->img = frame2::omapenemy["gs"][frame2::gs]->img;
		frame2::gkdes = frame2::gkDesList[frame2::gs];
	}
}

