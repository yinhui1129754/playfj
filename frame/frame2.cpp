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
void frame2::init(DemoApp * app, colVec * colObj){
	frame2::scene = new action(app);
	frame2::app = app;
	//frame2::scene->addTicker(frame2::tk1);
	frame2::colObj = colObj;
	app->use_onClick["frame2"] = frame2::onClick;
	frame2::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame2::maxBox);
	frame2::firstVisible = FALSE;
}
void frame2::destory() {
	
};
void frame2::drawCall(sprite *sp, DemoApp *app) {
	IDWriteTextFormat * u_forMat = app->content->createFont(32.0,L"微软雅黑");
	wstringstream ss;
	ss << L"第" ;
	ss << 1;
	ss << L"关";
	app->content->strokeStyle(0xffffff, 1);
	D2D1_SIZE_F SF;
	app->content->getTextInfo((LPWSTR)(ss.str().c_str()), SF);
	app->content->drawText((LPWSTR)ss.str().c_str(),app->width/2-SF.width/2*32/16,40, u_forMat);
	u_forMat->Release();
	u_forMat = NULL;
};
void frame2::visible(){
	if (!frame2::firstVisible) {
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
		
		sprite * gs1 = new sprite(frame2::app,L"img/frame2/gameBg1.jpg");
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


		frame2::maxBox->addChild(bg);
		frame2::maxBox->addChild(back);
		frame2::maxBox->addChild(text2);
		frame2::maxBox->addChild(gs1);
		frame2::maxBox->addChild(begin);
		frame2::maxBox->addChild(dSpri);
	}
	
	frame2::firstVisible = TRUE;
};
void frame2::tk1FunC(DemoApp **app, ticker * tk) {

}
void frame2::onClick(int x, int y) {
	sprite * sn = frame2::maxBox->getChildById("back");
	sprite * begin = frame2::maxBox->getChildById("begin");
	if (sn->inRect(frame2::app->mouse)) {
		frame2::app->nowScene = 0;
		frame0::visible();
	}
	else if (begin->inRect(frame2::app->mouse)) {
		frame2::app->nowScene = 3;
		frame3::visible();
	}
}

