#include <Windows.h>

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Catch any relevant messages here
	// Switch (uMsg)
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCommand)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Module 2";

	if (!RegisterClass(&wc))
		exit(EXIT_FAILURE);

	HWND mainWindow = NULL;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r = { 0 };
	r.top = r.left;
	r.right = 800;
	r.bottom = 600;

	AdjustWindowRect(&r, WindowStyle, 0);

	mainWindow = CreateWindowEx(
		0,
		"Module 2",
		"Lesson 2.1",
		WindowStyle,
		200,
		200,
		r.right - r.left,
		r.bottom - r.top,	
		NULL,
		NULL,
		hInstance,
		0);

	// Show window created
	ShowWindow(mainWindow, SW_SHOWDEFAULT);

	HDC DeviceContext = GetDC(mainWindow);
	PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
	ReleaseDC(mainWindow, DeviceContext);

	return 0;
}

