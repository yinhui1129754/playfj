
#include "../stdafx.h"
#include "aircraft.h"
#include"user.h"
#include "power.h"
#include "enemy.h"
#include "frame3.h"


power::power()
{
}


power::~power()
{
}
BOOL  power::getCenter() {
	this->center->x = this->start->x / 2 + this->end->x / 2;
	this->center->y = this->start->y / 2 + this->end->y / 2;
	return TRUE;
};
power::power(sprite * spr):aircraft(spr,10) {
	this->start = new POINT;
	this->center = new POINT;
	this->end = new POINT;
	this->t = 0;
	this->moveAng = 361.0f;
};
BOOL power::frame() {
	if (this->angle_type == 0) {
		if (this->moveType == 0) {
			this->view->setY(this->view->g_y + this->speed);
		}
		else if (this->moveType == 1) {
			utils::usePoint up = {
				this->view->g_x,this->view->g_y
			};
			if (this->moveAng > 360.0f) {
				this->moveAng= frame3::colObj->pointAngleInfo(*this->start, *this->end);
			}
			utils::usePoint up2 = {
				0,0
			};
			frame3::colObj->polarCoordinates(up, this->moveAng,this->speed,up2);
			this->view->setX(up2.x);
			this->view->setY(up2.y);
		}
		else if (moveType == 2) {
			this->view->setY(this->view->g_y - this->speed);
		}
	}
	if (this->view->g_x > frame3::app->width+ this->view->getWidth()*2 || 
		this->view->g_x < -this->view->getWidth() * 2||
		this->view->g_y > frame3::app->height + this->view->getWidth() * 2 ||
		this->view->g_y < - this->view->getHeight() * 2
		) {
		frame3::removePowerEx(this);
	}
	return FALSE;

}
void power::hurtUser(user * u) {
	u->PH -= this->hurt;
};
void power::hurtEnemy(enemy *e) {
	e->PH -= this->hurt;
	if (e->PH <= 0) {
		e->PH = 0;
		e->isDeath = 1;
		e->view->img = e->deathView->img;
		e->view->width = e->deathWidth;
		e->view->height = e->deathHeight;
		e->view->zoom = 1;
		e->view->speedTime = 50;
		e->view->spriteType = "animateSprite";
		for (int i = 0; i < 6; i++) {
			u_rect a = { 0,e->deathHeight*i,e->deathWidth,e->deathHeight };
			e->view->frameArr.push_back(a);
		}
	}
};