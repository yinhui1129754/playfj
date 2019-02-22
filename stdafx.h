// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "instance/targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

#include <functional>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
//C++���п�
#include <iostream>
#include <thread>
#include <sstream>

#include <set>
#define M_PI       3.14159265358979323846   // pi
#include <cmath>
#include <time.h>
#include "frame/MiniDump.h"
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment(lib,"Imm32.lib")
#include <vector>
using namespace std;
extern "C"
{
#include "lua/lua.h"  
#include "lua/lauxlib.h"  
#include "lua/lualib.h"  
}



#include "instance/utils.h"
#include"instance/oMap.h"
//#include "oMap.h"
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
wchar_t * g_chartowchar2(const char* cchar);
template <typename T1, typename T2>
string g_concat(const T1 &v1, const T2 &v2)
{
	stringstream ss;
	ss << v1 << v2;
	return ss.str();
}
float random();
typedef struct  {
	int x;
	int y;
	int width;
	int height;
} u_rect;
// �ڴ˴����ó�����Ҫ��������ͷ
#include <gdiplus.h> 
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

#include "render/ticker.h"
#include "render/action.h"
#include "render/sprite.h"
#include "render/Content.h"
#include "instance/DemoApp.h"
#include "instance/colVec.h"