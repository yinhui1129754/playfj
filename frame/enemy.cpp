#include "../stdafx.h"
#include "aircraft.h"
#include "user.h"
#include "frame3.h"
#include "power.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}
enemy::enemy(sprite * spr, int PH):aircraft(spr, PH)
{

	this->id = utils::GetId(); //id
	this->speed = 5; //移动速度
	this->moveType = 0; //y移动类型
	this->moveType2 = 0; //x移动类型
	this->userType = 0; //操作类型
	this->powerNum = 5; //子弹数量
	this->powerType = 1; //子弹类型
	this->powerSendAllNum = 30;//发送间隔
	this->powerSendNum = 1; //当前发送间隔
	this->powerSendAllNumAuto = 30;//发送间隔
	this->powerSendNumAuto = 1; //当前发送间隔

	this->hurt = 5; //伤害数值
	this->enemyType = 0;//敌机类型
	this->powerTypeAuto = 0;//自动发射子弹的类型
	this->powerId = 0; //发射子弹的图片id
	this->powerIdAuto = 0; //自动发射子弹的图片id
	this->isShowPH = 0; //被攻击的时候是否显示生命值 
	this->name = NULL;
	this->stringWidth = 0;
}
void  enemy::sendPower() {
	this->sendPower(this->powerId);
}
void enemy::setName(LPWSTR  ws) {
	this->name = ws;
	D2D1_SIZE_F S;
	frame3::app->content->getTextInfo(ws, S);
	this->stringWidth = S.width;
}
void  enemy::sendPower(POINT p) {
	this->sendPower(this->powerIdAuto,p);
}
void  enemy::sendPower(int id) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	if (powerType == 0) {
		pw->moveType = powerType;
		pw->view->setX(this->view->g_x + this->view->getWidth() / 2 - pw->view->getWidth() / 2);
		pw->view->setY(this->view->g_y + this->view->getHeight() - pw->view->getWidth() / 2);
		frame3::addPower(pw);
	}
	else if (powerType == 1) {
		pw->moveType = powerType;
		pw->view->setX(this->view->g_x + this->view->getWidth() / 2 - pw->view->getWidth() / 2);
		pw->view->setY(this->view->g_y + this->view->getHeight() - pw->view->getWidth() / 2);
		pw->start->x = pw->view->g_x;
		pw->start->y = pw->view->g_y;
		pw->end->x = frame3::userList[0]->view->g_x+ frame3::userList[0]->view ->getWidth()/2;
		pw->end->y = frame3::userList[0]->view->g_y+ frame3::userList[0]->view->getHeight() / 2;

		pw->speed = 4;
		pw->getCenter();
		frame3::addPower(pw);
	}
};
void  enemy::sendPower(int id,POINT p) {
	power * pw = new power(frame3::omapenemy["power"][id]);
	if (powerTypeAuto== 0) {
		pw->moveType = powerTypeAuto;
		pw->view->setX(this->view->g_x +p.x - pw->view->getWidth() / 2);
		pw->view->setY(this->view->g_y + p.y - pw->view->getWidth() / 2);
		frame3::addPower(pw);
	}
	else if (powerTypeAuto == 1) {
		pw->moveType = powerTypeAuto;
		pw->view->setX(this->view->g_x + p.x - pw->view->getWidth() / 2);
		pw->view->setY(this->view->g_y + p.y - pw->view->getWidth() / 2);
		pw->start->x = pw->view->g_x;
		pw->start->y = pw->view->g_y;
		pw->end->x = frame3::userList[0]->view->g_x + frame3::userList[0]->view->getWidth() / 2;
		pw->end->y = frame3::userList[0]->view->g_y + frame3::userList[0]->view->getHeight() / 2;
		pw->speed = 4;
		pw->getCenter();
		frame3::addPower(pw);
	}
};
float enemy::getJl(user *u) {
	float x = 0;
	
	if (this->view->g_x > u->view->g_x) {
		x = this->view->g_x - u->view->g_x;
	}
	else {
		x = u->view->g_x - this->view->g_x;
	}
	float y = 0;
	if (this->view->g_y > u->view->g_y) {
		y = this->view->g_y - u->view->g_y;
	}
	else {
		y = u->view->g_y - this->view->g_y;
	}

	return (int)sqrt(x*x + y * y);
}
void enemy::deathCall() {
	int local_w = this->view->width;
	int local_h = this->view->height;
	this->PH = 0;
	this->isDeath = 1;
	this->view->img = this->deathView->img;
	this->view->width = this->deathWidth;
	this->view->height = this->deathHeight;
	this->view->zoom = 1;
	this->view->speedTime = 50;
	this->view->spriteType = "animateSprite";
	this->view->setX(this->view->g_x - (this->view->width - local_w)/2);
	this->view->setY(this->view->g_y - (this->view->height - local_h)/2);
	for (int i = 0; i < 6; i++) {
		u_rect a = { 0,this->deathHeight*i,this->deathWidth,this->deathHeight };
		this->view->frameArr.push_back(a);
	}
	frame3::deathCall(this);
}
BOOL enemy::frame() {
	if (this->userType == 1) {
		return FALSE;
	}
	
	if (this->isDeath == 1) {
		if (this->deathNum <= 0) {
			frame3::removeEnemy(this->id);
			return TRUE;
		}
		else {
			this->deathNum--;
		}
		return FALSE;
	}
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
	if (this->isDeath==0&&frame3::colObj->aabb(frame3::userList[0]->view, this->view)) {
		this->deathCall();
		frame3::userList[0]->PH -= this->hurt;
		return TRUE;
	}
	if (this->enemyType == 1) {
		if (this->addNumFrame >= 0) {
			this->moveType = 0;
			this->addNumFrame--;
		}
		else if (this->subNumFrame >= 0) {
			this->moveType = 1;
			this->subNumFrame--;
		}
		else {
			this->moveType = 0;
		}
	}
	else if (this->enemyType == 2) {
		if (this->view->g_x > frame3::app->width - this->view->getWidth()) {
			this->moveType2 = 1;
		}
		else if (this->view->g_x < 0) {
			this->moveType2 = 0;
		}
		if (this->moveType == 0) {
			if (this->bufNumFrame <= 0) {
				this->bufNumFrame = this->subNumFrame;
				this->moveType = 1;
			}
			else {
				this->bufNumFrame--;
			}
		}
		else if (this->moveType == 1) {
			if (this->bufNumFrame <= 0) {
				this->bufNumFrame = this->addNumFrame;
				this->moveType = 0;
			}
			else {
				this->bufNumFrame--;
			}
		}
	}
	int local_juli = this->getJl(frame3::userList[0]);
	if (local_juli < 500) {
		if (this->powerNum > 0) {
			if (this->powerSendNum <= 0) {
				this->sendPower();
				this->powerNum--;
				this->powerSendNum = this->powerSendAllNum;
			}
			else {
				this->powerSendNum--;
			}
		}
	}
	else if (local_juli >= 1400+this->view->getWidth()) {
		frame3::removeEnemy(this->id);
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
	
	return FALSE;
};
void enemy::addSendPoint(POINT p) {
	this->sendPoints.push_back(p);
};