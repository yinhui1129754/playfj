
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
	this->powerType = 0; //×Óµ¯ÀàÐÍ
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
		if (this->powerType != 0&&this->isDeath!=0) {
			if (this->deathNum >= 0) {
				this->deathNum--;
			}
			else {
				frame3::removePowerEx(this);
				return TRUE;
			}
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
	if (e->isShowPH == 1) {
		frame3::userList[0]->hurtEnemy = (long long)e;
	}
	if (e->PH <= 0) {
		e->deathCall();
	}
};
void power::deathCall() {
	if (this->powerType == 1&&this->deathView!=NULL) {
		int local_w = this->view->width;
		int local_h = this->view->height;
		this->PH = 0;
		this->isDeath = 1;
		this->view->img = this->deathView->img;
		this->view->width = this->deathView->getWidth();
		this->view->height = this->deathView->getHeight();
		this->view->zoom = 1;
		this->view->setX(this->view->g_x - (this->view->width - local_w) / 2);
		this->view->setY(this->view->g_y - (this->view->height - local_h) / 2);
		this->moveType = -1;
		sprite * sp = this->view->children[0];
		this->view->children.pop_back();
		delete sp;
	}

};