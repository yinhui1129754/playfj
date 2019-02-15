#include "../stdafx.h"
#include "frame0.h"
#include "frame1.h"
#include "frame2.h"
#include "../instance/colVec.h"
//action * frame0::scene = NULL;
action *frame0::scene = NULL;
DemoApp * frame0::app = NULL;
colVec * frame0::colObj = NULL;
DisplayObject * frame0::maxBox = NULL;
float frame0::zoom = 0.7;
bool frame0::isInit = false;
vector <utils::usePoint> frame0::p1;
BOOL frame0::firstVisible = FALSE;
void frame0::init(DemoApp * app, colVec * colObj){
	frame0::scene = new action(app);
	frame0::app = app;
	//frame0::scene->addTicker(frame0::tk1);
	frame0::colObj = colObj;
	app->use_onClick["frame0"] = frame0::onClick;
	frame0::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame0::maxBox);
	frame0::firstVisible = FALSE;
}
void frame0::destory() {
	
};
void frame0::visible(){
	
	if (frame0::firstVisible != TRUE) {
		sprite * bg = new sprite(frame0::app, L"img/Interface/startbg.jpg");
		bg->width = app->width;
		bg->height = app->height;

		sprite * lg = new sprite(frame0::app, L"img/Interface/login.png");
		lg->zoom = frame0::zoom;

		sprite * sn = new sprite(frame0::app, L"img/Interface/sign.png");
		sn->zoom = frame0::zoom;
		sn->setId("start");
		sprite * about = new sprite(frame0::app, L"img/Interface/about.png");
		about->zoom = frame0::zoom;
		about->setId("about");
		frame0::maxBox->addChild(bg);
		frame0::maxBox->addChild(lg);
		frame0::maxBox->addChild(sn);
		frame0::maxBox->addChild(about);

		lg->setX((bg->getWidth() / 2 - lg->getWidth() / 2));
		lg->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15);

		sn->setX((bg->getWidth() / 2 - sn->getWidth() / 2));
		about->setX((bg->getWidth() / 2 - about->getWidth() / 2));
		sn->setY((bg->getHeight() / 2 - lg->getHeight() / 2) + 30 - bg->getHeight() / 100 * 15 + lg->getHeight() + 30);
		about->setY((bg->getHeight() / 2 - lg->getHeight() / 2) + 30 - bg->getHeight() / 100 * 15 + lg->getHeight() + 30 + about->getHeight() + 30);
	}
	frame0::firstVisible = TRUE;
};
void frame0::tk1FunC(DemoApp **app, ticker * tk) {

}
void frame0::onClick(int x, int y) {
	sprite * sn = frame0::maxBox->getChildById("start");
	sprite * about = frame0::maxBox->getChildById("about");
	if (about->inRect(frame0::app->mouse)) {
		frame0::app->nowScene = 1;
		frame1::visible();
	}
	else if (sn->inRect(frame0::app->mouse)) {
		HIMC imm = ImmGetContext(frame0::app->getHwnd());
		DWORD a, b;
		ImmGetConversionStatus(imm, &a, &b);
		if (!ImmSetConversionStatus(imm, a, IME_CMODE_ALPHANUMERIC)) {
			utils::AlertOut(L"error:%d", GetLastError());
		};
		frame0::app->nowScene = 2;
		frame2::visible();
	}
}

