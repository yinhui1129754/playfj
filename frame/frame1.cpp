#include "../stdafx.h"
#include "frame0.h"
#include "frame1.h"
#include "../instance/colVec.h"
//action * frame1::scene = NULL;
action *frame1::scene = NULL;
DemoApp * frame1::app = NULL;
colVec * frame1::colObj = NULL;
DisplayObject * frame1::maxBox = NULL;
float frame1::zoom = 0.7;
bool frame1::isInit = false;
vector <utils::usePoint> frame1::p1;
BOOL frame1::firstVisible = FALSE;
void frame1::init(DemoApp * app, colVec * colObj){
	frame1::scene = new action(app);
	frame1::app = app;
	//frame1::scene->addTicker(frame1::tk1);
	frame1::colObj = colObj;
	app->use_onClick["frame1"] = frame1::onClick;
	frame1::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame1::maxBox);
	frame1::firstVisible = FALSE;
}
void frame1::destory() {
	
};
void frame1::visible(){
	if (!frame1::firstVisible) {
		sprite * bg = new sprite(frame1::app, L"img/Interface/bg2.jpg");
		bg->width = app->width;
		bg->height = app->height;
		
		sprite * back = new sprite(frame1::app, L"img/system/back.png");
		back->zoom = 14 / 200.0;
		back->setX(8);
		back->setY(8);
		back->setId("back");
		 
		sprite * text = new sprite(0, 0);
		text->spriteType = "textSprite";
		text->txt = "QQ邮箱:375361172@qq.com；";
		text->rgb = 0xffffff;
		text->setX(8);
		text->setY(35);
		text->width = 400;
		text->height = 45;
	

		sprite * text2 = new sprite(0, 0);
		text2->spriteType = "textSprite";
		text2->txt = "我的git:https://github.com/yinhui1129754；";
		text2->rgb = 0xffffff;
		text2->setX(8);
		text2->setY(75);
		text2->width = 400;
		text2->height = 45;
		
		sprite * text3 = new sprite(0, 0);
		text3->spriteType = "textSprite";
		text3->txt = "我的vc论坛:https://www.cctry.com/home.php?mod=space&uid=485516&do=thread&view=me&from=space；";
		text3->rgb = 0xffffff;
		text3->setX(8);
		text3->setY(115);
		text3->width = 400;
		text3->height = 45;

		sprite * text4 = new sprite(0, 0);
		text4->spriteType = "textSprite";
		text4->txt = "---------------------------------------------------------------操作说明:\nw上移动， s下移动，a左移动，d右移动;\nj子弹，k技能                            ---------------------------------------------------------------";
		text4->rgb = 0xffffff;
		text4->setX(8);
		text4->setY(205);
		text4->width = 440;
		text4->height = 45;


		sprite * imgFz = new sprite(frame1::app, L"img/Interface/aa.png");



		frame1::maxBox->addChild(bg);

		frame1::maxBox->addChild(imgFz);
		frame1::maxBox->addChild(back);
		frame1::maxBox->addChild(text);

		frame1::maxBox->addChild(text2);
		frame1::maxBox->addChild(text3);
		frame1::maxBox->addChild(text4);
	
	}
	
	frame1::firstVisible = TRUE;
};
void frame1::tk1FunC(DemoApp **app, ticker * tk) {

}
void frame1::onClick(int x, int y) {
	sprite * sn = frame1::maxBox->getChildById("back");
	if (sn->inRect(frame1::app->mouse)) {
		frame1::app->nowScene = 0;
		frame0::visible();
	}
}

