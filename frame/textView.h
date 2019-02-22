#pragma once
extern class aircraft;
class textView :public aircraft
{
public:
	textView();
	~textView();
	BOOL frame();
	string txt;
	int txtWidth;
	BOOL setTxt(string lpw, int color=0xffffff);
	float speed;
	int moveType;
	int moveType2;
	int chFrame;
};

