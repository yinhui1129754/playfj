// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// d2dWin32.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "../stdafx.h"
// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������
wchar_t * g_chartowchar2(const char* cchar){
	return utils::user_LPCSTRToLPWSTR(cchar);
}

float random() {
	static int i = 0;
	i++;
	srand(time(NULL)*i);
	float a = (float)(rand() % 1000) / 1000;
	return a;
}