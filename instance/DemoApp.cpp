#include "../stdafx.h"
#include "../Resource.h"
#include "../trigger/createBefore.h"

DemoApp::DemoApp() :
	m_hwnd(NULL),
	content(NULL)
{

}

DemoApp::~DemoApp()
{

}

void DemoApp::addScene(action * scane) {
		this->sceneArr.push_back(scane);
};
//全屏
void DemoApp::fullSreen() {
	//int cx = GetSysTemMetrice(SM_CXSCREEN);
	if (this->isFull) {
		return;
	}
	this->isFull = true;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height =  GetSystemMetrics(SM_CYSCREEN);
	this->wLong = GetWindowLong(m_hwnd, GWL_STYLE);
	SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP); 
	SetWindowPos(this->m_hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
//取消全屏
void DemoApp::cancelFullSreen() {
		if (!this->isFull) {
			return;
		}
		this->isFull = false;
		SetWindowLong(m_hwnd, GWL_STYLE, this->wLong);
		SetWindowPos(this->m_hwnd, HWND_NOTOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
//消息循环
void DemoApp::RunMessageLoop()
{
	MSG msg;
	BOOL isLoop = TRUE;

	QueryPerformanceFrequency(&this->frequency);
	while (isLoop)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				isLoop = FALSE;
			}
		}
		if (!this->gameBool) {
			//窗口处于非激活状态防止cpu爆炸
			Sleep(10);
		}
		this->content->beginDraw();
		QueryPerformanceCounter(&this->newtime);
		this->msTime = ((float)(newtime.QuadPart - oldtime.QuadPart) / frequency.QuadPart * 1000);
		
		if (this->msTime >=(int)1000/70)
		{
			this->content->clear();
			this->OnRender();
			QueryPerformanceCounter(&this->oldtime);
		}
		this->content->closeDraw();
	}

	//CloseHandle(this->thread1);
	
}
//初始化窗口类
HRESULT DemoApp::Initialize()
{
	HRESULT hr=S_OK;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = DemoApp::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"MXSJ";
		wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, (LPCTSTR)IDI_D2DWIN32);
		RegisterClassEx(&wcex);
			



		// Create the window.
		m_hwnd = CreateWindow(
			L"MXSJ",
			L"playfj",
			WS_OVERLAPPEDWINDOW&(~WS_MAXIMIZEBOX)&(~WS_SIZEBOX)&(~WS_CAPTION),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			450,
			750,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		LONG styleLong=GetWindowLong(m_hwnd, GWL_STYLE);
		SetWindowLong(m_hwnd, GWL_STYLE, styleLong&(~WS_CAPTION));

		content = new Content(m_hwnd);
		content->strokeStyle(0xff00ff, 1);
		content->lineWidth = 2;
		content->fillStyle(0xffff00, 1);
		createBefore::createWindowBefore(this);
		
	
		
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
		
	
	}
	createBefore::createWindow(this);
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	MoveWindow(m_hwnd,(rc.right-rc.left)/2- this->width/2, ( rc.bottom- rc.top) / 2- this->height/2, this->width,this->height, TRUE);
	return hr;
}
/*void DemoApp::addScene(action * scane) {
	this->sceneArr.push_back(scane);
};*/
void DemoApp::addFun(void (*funs)(DemoApp *)) {
	vector<void (*)(DemoApp*)>::iterator it;
	it = find(this->fun.begin(), this->fun.end(), (funs));
	if (it == this->fun.end()) {
		(this->fun).push_back((funs));
	}
};
//返回窗口句柄
HWND DemoApp::getHwnd() {
	return this->m_hwnd;
};

//窗口消息处理
LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int intD = 1;
	LRESULT result = 0;
	WORD  isActive = HIWORD(wParam);
	DemoApp *pDemoApp = NULL;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	RECT topRect;
	GetWindowRect(hwnd, &topRect);
	if (message == WM_CREATE)
	{
		intD = 100;
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;

		pDemoApp = (DemoApp *)pcs->lpCreateParams;
	
		pDemoApp->width = topRect.right - topRect.left;
		pDemoApp->height = topRect.bottom - topRect.top;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pDemoApp)
		);
	

		result = 1;
	}
	else
	{
		if (intD != 100) {
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));
		//
		if (pDemoApp == NULL) {
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		
		bool wasHandled = false;

		if (pDemoApp)
		{


			switch (message)
			{
	
		
			case WM_SIZE:
			{
				
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;
			case WM_KEYUP:
				messageMapping::onKeyUp(wParam);
				result = 0;
				wasHandled = true;
				break;
		
			case WM_KEYDOWN:
				messageMapping::onKeyDown(wParam);
				result = 0;
				wasHandled = true;
				break;
			case WM_MOUSEMOVE:
				pDemoApp->mouse->x = LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseMove(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 0;
				wasHandled = true;
			
				break;
			case WM_LBUTTONUP:
				pDemoApp->mouse->x=LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseUp(pDemoApp->mouse->x, pDemoApp->mouse->y);
				messageMapping::onClick(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 1;
				wasHandled = true;
				if (pDemoApp->mouse->x<clientRect.right - 30 && pDemoApp->mouse->x>clientRect.right - 60&&
					pDemoApp->mouse->y<30 && pDemoApp->mouse->y>0
					) {
					SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
				}
				if (pDemoApp->mouse->x<clientRect.right && pDemoApp->mouse->x>clientRect.right - 30 &&
					pDemoApp->mouse->y < 30 && pDemoApp->mouse->y>0
					) {
					SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				}

				break;
			case WM_LBUTTONDOWN:
				pDemoApp->mouse->x = LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseDown(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 1;
				wasHandled = true;
				if (pDemoApp->mouse->y < 30) {
					pDemoApp->public_ismove = TRUE;
					POINT p;
					GetCursorPos(&p);
					pDemoApp->startMouse.left = p.x;
					pDemoApp->startMouse.top = p.y;
					pDemoApp->startMouse.right = topRect.left;
					pDemoApp->startMouse.bottom = topRect.top;
				}
				

				break;
			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;
			case WM_ACTIVATE:
				if (isActive > 0) {
					pDemoApp->gameBool = false;
				}
				else {
					pDemoApp->gameBool = true;
				}
				
				result = 0;
				wasHandled = true;
				break;
			case WM_DESTROY:
			{
				
				messageMapping::onClose();
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}
//render循环
HRESULT DemoApp::OnRender()
{
	LRESULT hr = S_OK;

	for (unsigned int i = 0; i < (this->fun).size();i++)
	{
		(this->fun)[i](this);
	}

	return hr;
}
//修改大小事件
void DemoApp::OnResize(UINT width, UINT height)
{

}
//获取资源方法
void DemoApp::getSource(vector<string> arr) {
	for (unsigned int i=0;i < arr.size();i++) {
		this->content->getSoucre(g_chartowchar2(arr[i].c_str()));
	}
};