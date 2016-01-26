#include <Windows.h>

BOOL IsRunning = TRUE;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Catch any relevant messages here
	// Switch (uMsg)
	LRESULT Result = 0;

	switch (uMsg)
	{
		case WM_KEYUP:
			IsRunning = FALSE;
			Result = 56;
			break;
		case WM_ACTIVATE:
		case WM_CREATE:
		case WM_DESTROY:
			break;
		default:
			Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return Result;
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
		"Lesson 2.3",
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

	LARGE_INTEGER Frequency; 
	QueryPerformanceFrequency(&Frequency);

	double SecondsPerTick = 1 / (double)Frequency.QuadPart;

	LARGE_INTEGER Tick, Tock; 
	QueryPerformanceCounter(&Tick);

	MSG msg;
	while (IsRunning)
	{
		// Check with OS
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Update game
		// Draw graphics
		QueryPerformanceCounter(&Tock);

		__int64 interval = Tock.QuadPart - Tick.QuadPart;
		double SecondsGoneBy = (double)interval * SecondsPerTick; // No. of ticks * seconds per tick

		char buf[64] = { 0 };
		sprintf_s(buf, 64, "Total Time: %3.7f \n", SecondsGoneBy);
		OutputDebugString(buf);
	
		QueryPerformanceCounter(&Tick);
	}
	return 0;
}

