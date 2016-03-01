#include "vid.h"

int BufferWidth = 640;
int BufferHeight = 480;
int WindowWidth = 640;
int WindowHeight = 480;
int BytesPerPixel = 1;
void* BackBuffer;

BITMAPINFO BitMapInfo = { 0 };

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Catch any relevant messages here
	// Switch (uMsg)
	LRESULT Result = 0;

	switch (uMsg)
	{
	case WM_ACTIVATE:
		break;

	case WM_CREATE:
		break;

	case WM_DESTROY:
		Sys_Shutdown();
		PostQuitMessage(0);
		break;

	default:
		Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return Result;
}

void  VID_Init(void)
{
	// Define our window class
	WNDCLASSEX  wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc =  MainWndProc;
	wc.hInstance = GlobalInstance;
	wc.lpszClassName = "Module3";

	if (!RegisterClassEx(&wc))
		exit(EXIT_FAILURE);

	HWND mainWindow = NULL;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	DWORD WindowExStyle = 0;
	
	/*BOOL FullScreen = FALSE;

	if (FullScreen)
	{
	DEVMODE dmScreenSettings = { 0 };
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth = BufferWidth;
	dmScreenSettings.dmPelsHeight = BufferHeight;
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
	{
	dwExStyle = WS_EX_APPWINDOW;
	dwStyle = WS_POPUP;
	}
	else
	{
	FullScreen = FALSE;
	}
	}*/

	RECT r = { 0 };
	r.right = WindowWidth;
	r.bottom = WindowHeight;
	AdjustWindowRectEx(&r, WindowStyle, 0, WindowExStyle);

	// Create Window
	HWND MainWindow = CreateWindowEx(
		WindowExStyle,
		"Module3",
		"Lesson 3.5",
		WindowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		GlobalInstance,
		0);

	// Show window created
	ShowWindow(MainWindow, SW_SHOWDEFAULT);
	
	HDC DeviceContext = GetDC(MainWindow);
	PatBlt(DeviceContext, 0, 0, BufferWidth, BufferHeight, BLACKNESS);
	ReleaseDC(MainWindow, DeviceContext);

	// Define our Bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = -BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = malloc(BufferWidth * BufferHeight * BytesPerPixel);
}

void VID_Shutdown(void)
{

}