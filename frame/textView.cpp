#include "../stdafx.h"
#include "aircraft.h"
#include "user.h"
#include "frame3.h"
#include "power.h"
#include "textView.h"




textView::textView():aircraft()
{
	this->txt = "";
	this->txtWidth = 0;
	this->speed =3;
	this->moveType = 1;
	this->moveType2 = 2;
	this->chFrame = 100;
}


textView::~textView()
{
}
BOOL textView::frame() {

	if (this->moveType == 0) {
		this->view->setY(this->view->g_y + this->speed);
	}
	else if (this->moveType == 1) {
		this->view->setY(this->view->g_y - this->speed);
	}
	if (this->moveType2 == 0) {
		this->view->setX(this->view->g_x + this->speed);
	}
	else if (this->moveType2 == 1) {
		this->view->setX(this->view->g_x - this->speed);
	}
	if (this->chFrame <= 0) {
		frame3::removeTextView(this);
		return TRUE;
	}
	else {
		this->chFrame--;
	}
	return FALSE;
}
BOOL textView::setTxt(string lpw,int color) {
	this->txt = lpw;
	D2D1_SIZE_F S;
	LPWSTR a = g_chartowchar2(txt.c_str());
	frame3::app->content->getTextInfo(a, S);
	free(a);
	this->txtWidth = S.width;
	this->view = new sprite(0, 0);
	view->spriteType = "textSprite";
	view->txt = lpw;
	view->rgb = color;
	view->width = S.width;
	view->height = 45;
	return TRUE;
};
