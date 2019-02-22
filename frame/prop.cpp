#include "../stdafx.h"
#include "aircraft.h"
#include "user.h"
#include "textView.h"
#include "frame3.h"
#include "power.h"
#include "prop.h"



prop::prop()
{
}
prop::prop(sprite * spr):aircraft(spr,10) {
	this->moveType = 0;
	this->moveType2 = 0;
	this->speed = 3.0f;
	this->pzNum = 20;
	this->frameNum = 6;
	this->propType = 0; // 0 
	this->val = 10;
};

prop::~prop()
{

}
void prop::init() {
	int local_w = this->view->width;
	int local_h = this->view->height;
	this->view->width = this->view->height;
	this->view->zoom = 1;
	this->view->speedTime = 50;
	this->view->spriteType = "animateSprite";
	for (int i = 0; i < this->frameNum; i++) {
		u_rect a = { this->view->height*i,0,this->view->width,this->view->height };
		this->view->frameArr.push_back(a);
	}
}
BOOL prop::frame() {
	if (this->angle_type == 0) {
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
	}
	if (this->view->g_x >= frame3::app->width - this->view->getWidth()) {
		if (this->pzCall()) {
			this->moveType2 = 1;
		}
	}


	if (this->view->g_x <=0 ) {
		if (this->pzCall()) {
			this->moveType2 = 0;
		}
		
	}
	if (this->view->g_y >= frame3::app->height - this->view->getHeight()) {
		if (this->pzCall()) {
			this->moveType = 1;
		}
		
	}
	if (this->view->g_y <= 0) {
		if (this->pzCall()) {
			this->moveType = 0;
		}
	}
	if (frame3::colObj->aabb(frame3::userList[0]->view, this->view)) {
		textView * tv = new textView;
		if (this->propType == 0) {
			frame3::userList[0]->PH += this->val;
			if (frame3::userList[0]->PH >= frame3::userList[0]->maxPH) {
				frame3::userList[0]->PH = frame3::userList[0]->maxPH;
			}
			tv->setTxt("PH»Ö¸´",0xffffff);
			
		
		}
		else if (this->propType == 1) {
			frame3::userList[0]->isJnNum += this->val;
			tv->setTxt("¼¼ÄÜµ¼µ¯¼Ó1", 0xffffff);
		}
		else if (this->propType == 2) {
			frame3::userList[0]->hurt += this->val;
			tv->setTxt("j¹¥»÷ÉËº¦ÌáÉý", 0xffffff);
		}
		tv->view->setX(this->view->g_x);
		tv->view->setY(this->view->g_y);
		frame3::addTextView(tv);
		frame3::removeProp(this);
		return TRUE;
	}
	if (this->view->g_x > frame3::app->width + this->view->getWidth() * 2 ||
		this->view->g_x < -this->view->getWidth() * 2 ||
		this->view->g_y > frame3::app->height + this->view->getWidth() * 2 ||
		this->view->g_y < -this->view->getHeight() * 2
		) {
		frame3::removeProp(this);
		return TRUE;
	}
	return FALSE;
}
BOOL prop::pzCall() {
	if (this->pzNum <= 0) {
		return FALSE;
	}
	else {
		this->pzNum--;
		return TRUE;
	}
}
