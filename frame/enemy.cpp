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
	this->powerSendAllNum = 30;
	this->powerSendNum = 1;
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
	int local_juli = this->getJl(frame3::userList[0]);
	if (local_juli < 500) {
		if (this->powerNum > 0) {
			if (this->powerSendNum <= 0) {
				this->sendPower(0);
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
	return FALSE;
};