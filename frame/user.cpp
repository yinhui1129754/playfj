#include "../stdafx.h"
#include "aircraft.h"
#include "power.h"
#include "user.h"
#include "frame3.h"

user::user()
{
}
user::user(sprite * spr, int PH):aircraft(spr, PH){
	this->isSend = 0; // 是否发送子弹
	this->hurt = 5;
	this->sendAllJg = 20;
	this->sendNowJg = 1;
};

user::~user()
{
}
void user::sendPower(int id) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	pw->view->setX(this->view->g_x + this->view->getWidth() / 2 - pw->view->getWidth() / 2);
	pw->view->setY(this->view->g_y);
	pw->moveType = 2;

	frame3::addUserPower(pw);
};
void user::frame() {
	//控制移动
	if (this->userType == 0) {
		if (this->isMoveX == 1) {
			if (this->moveTypeX == 1) {
				if (this->view->g_x + this->speed < frame3::app->width- this->view ->getWidth()/2) {
					this->view->setX(this->view->g_x + this->speed);
				}
				
			}
			else if (this->moveTypeX == 0) {
				if (this->view->g_x - this->speed > -this->view->getWidth() / 2) {
					this->view->setX(this->view->g_x - this->speed);
				}
				
			}
		}
		if (this->isMoveY == 1) {
			if (this->moveTypeY == 1) {
				if (this->view->g_y + this->speed < frame3::app->height - this->view->getHeight() / 2) {
					this->view->setY(this->view->g_y + this->speed);
				}
				
			}
			else if (this->moveTypeY == 0) {
				if (this->view->g_y + this->speed > - this->view->getHeight() / 2) {
					this->view->setY(this->view->g_y - this->speed);
				}
				
			}
		}
	}
	if (this->userType == 1&&this->view->g_y <= frame3::app->height - this->view->height-100) {
		this->userType = 0;
	}
	else if(this->userTypeStatus == 0&&this->userType == 1){
		this->view->setY(this->view->g_y - this->speed);
	}
	if (this->isSend == 1) {
		if (this->sendNowJg <= 0) {
			this->sendPower(1);
			this->sendNowJg = this->sendAllJg;
		}
		else {
			this->sendNowJg--;
		}
		
	}
};
