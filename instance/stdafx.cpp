// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// d2dWin32.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "../stdafx.h"
// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������
wchar_t * g_chartowchar2(const char* cchar){
	wchar_t *m_wchar;

	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}

float random() {
	static int i = 0;
	i++;
	srand(time(NULL)*i);
	float a = (float)(rand() % 1000) / 1000;
	return a;
}