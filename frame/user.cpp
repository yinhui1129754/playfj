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
	this->powerId = 1;
	this->hurtEnemy = -1;
	this->isJnNum = 3;
	this->jnAllimer = 400;
	this->jnTimer = 0;
	this->jnCreateTimmer =0;
	this->jnCreateAllTimmer = 30;
	this->jnId = 4;
	this->jnzxId = 0;

	
	this->powerSendNumAuto =0; //自动发送子弹当前间隔
	this->powerSendAllNumAuto =30; //自动发送子弹总间隔
	this->powerIdAuto =5; //自动发射子弹的图片id
	this->hurtAuto =3;
};
void user::addSendPoint(POINT p) {
	this->sendPoints.push_back(p);
}; //新增发射子弹点
user::~user()
{
}
void user::sendPower() {
	this->sendPower(this->powerId);
};
void user::sendPower(int id) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	pw->view->setX(this->view->g_x + this->view->getWidth() / 2 - pw->view->getWidth() / 2);
	pw->view->setY(this->view->g_y);
	pw->hurt = this->hurtAuto;
	pw->moveType = 2;

	frame3::addUserPower(pw);
};
void user::sendPowerJn(int id) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	sprite * sp = new sprite(frame3::omapenemy["userView"][this->jnzxId]->img);


	pw->view->setX(random()*frame3::app->width);
	pw->view->setY(frame3::app->height);
	pw->moveType = 2;
	pw->powerType = 1;
	pw->deathView = frame3::omapenemy["death"][1];
	frame3::addUserPower(pw);
	sp->setX(pw->view->getWidth() / 2 - sp->getWidth() / 2);
	sp->setY(pw->view->getHeight());
	pw->view->addChild(sp);

}
void  user::sendPower(int id, POINT p) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	pw->moveType = 2;
	pw->view->setX(this->view->g_x + p.x - pw->view->getWidth() / 2);
	pw->view->setY(this->view->g_y + p.y - pw->view->getWidth() / 2);
	frame3::addUserPower(pw);
};
void  user::sendPower(POINT p) {
	this->sendPower(this->powerIdAuto, p);
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
			this->sendPower();
			this->sendNowJg = this->sendAllJg;
		}
		else {
			this->sendNowJg--;
		}
	}
	int i = 0;
	for (i; i < this->sendPoints.size(); i++) {
		if (this->powerSendNumAuto <= 0) {
			this->sendPower(this->sendPoints[i]);
			if (i == this->sendPoints.size() - 1) {
				this->powerSendNumAuto = this->powerSendAllNumAuto;
			}
		}
	}
	if (i > 0) {
		this->powerSendNumAuto--;
	}



	if (this->jnTimer > 0) {
		this->jnTimer--;
		if (this->jnCreateTimmer <= 0) {
			this->sendPowerJn(this->jnId);
			this->jnCreateTimmer = this->jnCreateAllTimmer;
		}
		else {
			this->jnCreateTimmer--;
		}
	}

};
void user::sendJn() {
	if (this->jnTimer > 0) {
		return;
	}
	if (this->isJnNum > 0) {
		this->isJnNum--;
	}
	else {
		return;
	}
	this->jnTimer = this->jnAllimer;
}
