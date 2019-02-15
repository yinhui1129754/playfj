// d2dWin32.cpp : 定义应用程序的入口点。
//

#include "../stdafx.h"
#include "d2dWin32.h"
//#include "frame0.h"
void frame1(DemoApp*);
DemoApp __app;


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (__app.m_hwnd == NULL|| __app.public_ismove==FALSE) {
		return CallNextHookEx(0, nCode, wParam, lParam);
	}
	switch (wParam) {
	case WM_MOUSEMOVE:
		if (__app.public_ismove == TRUE) {
			RECT clientRect;
			GetClientRect(__app.m_hwnd, &clientRect);
			POINT p;
			GetCursorPos(&p);
			int x = __app.startMouse.right + (p.x - __app.startMouse.left);
			int y = __app.startMouse.bottom + (p.y - __app.startMouse.top);
		
			MoveWindow(__app.m_hwnd, x, y, clientRect.right, clientRect.bottom, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		__app.public_ismove = FALSE;
		break;
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	HHOOK hhk = NULL;
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{

			__app.addFun(frame1);
		
			hhk = SetWindowsHookExA(WH_MOUSE_LL, (HOOKPROC)MouseProc, GetModuleHandle(0), 0);
			if (SUCCEEDED(__app.Initialize()))
			{
				__app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}
	if (hhk != NULL) {
		UnhookWindowsHookEx(hhk);
	}
	
	return 0;
}


void frame1(DemoApp *app) {
	if (!(app)->sceneArr.empty()) {
		(app)->sceneArr[(app)->nowScene]->render(&app);
	
		/*app->content->fillStyle(0x000000,0.3);
		app->content->fillRect(clientRect.right-60,0,60,30);*/

		app->content->drawImage(app->systemInterface["close"],app->width-22, 8, 14, 14, 0, 0, app->systemInterface["close"]->GetSize().width, app->systemInterface["close"]->GetSize().height);
		app->content->drawImage(app->systemInterface["minbtn"], app->width - 22-30, 12, 14, 5, 0, 0, app->systemInterface["minbtn"]->GetSize().width, app->systemInterface["minbtn"]->GetSize().height);

	}
	/*unsigned int len = frame0::p1.size();
	for (unsigned int i = 0;i < len;i++) {
		(app)->content->drawArc(frame0::p1[i].x, frame0::p1[i].y, 10, 10);
	}*/
}