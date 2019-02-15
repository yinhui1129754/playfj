#include "../stdafx.h"
#include "createBefore.h"

#include "../frame/frame0.h"
#include "../frame/frame1.h"
#include "../frame/frame2.h"
#include "../frame/frame3.h"
#include "../frame/frame_lua.h"

DemoApp * l_app = NULL;
//窗口显示之前调用
void createBefore::createWindowBefore(DemoApp * app) {
	vector <string> arr;
	
	app->getSource(arr);

}

//窗口显示之后调用
void createBefore::createWindow(DemoApp * app) {
	l_app = app;
	colVec * colObj = new colVec();
	frame0::init(app, colObj);
	app->addScene(frame0::scene);
	frame0::visible();

	frame1::init(app, colObj);
	app->addScene(frame1::scene);

	frame2::init(app, colObj);
	app->addScene(frame2::scene);

	frame3::init(app, colObj);
	app->addScene(frame3::scene);

	l_app->systemInterface["close"] = l_app->content->getSoucre(L"img/system/close.png");
	l_app->systemInterface["minbtn"] = l_app->content->getSoucre(L"img/system/sx.png");
	l_app->content->resize(l_app->width, l_app->height);

	frame_lua::init();


};
void messageMapping::onKeyDown(int code) {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onKeyDown.find(a) != -1) {
		l_app->use_onKeyDown[a](code);
	}
}
void messageMapping::onKeyUp(int code) {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onKeyUp.find(a) !=-1) {
		l_app->use_onKeyUp[a](code);
	}
}
void messageMapping::onClick(int x, int y) {
	string a = g_concat("frame",l_app->nowScene);
	if (l_app->use_onClick.find(a)!=-1) {
		l_app->use_onClick[a](x, y);
	}
}
void messageMapping::onMouseDown(int x, int y) {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onMouseDown.find(a) != -1) {
		l_app->use_onMouseDown[a](x, y);
	}
}
void messageMapping::onMouseUp(int x, int y) {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onMouseUp.find(a) != -1) {
		l_app->use_onMouseUp[a](x, y);
	}
}
void messageMapping::onMouseMove(int x, int y) {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onMouseMove.find(a) != -1) {
		l_app->use_onMouseMove[a](x, y);
	}
}
void messageMapping::onClose() {
	string a = g_concat("frame", l_app->nowScene);
	if (l_app->use_onClose.find(a) != -1) {
		l_app->use_onClose[a]();
	}
}