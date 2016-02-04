#include "quakedef.h"
#include "winquake.h"

static BOOL IsRunning = TRUE;

////////////////////////////////////////////////////////
//			TIMER CODE
////////////////////////////////////////////////////////
static double GTimePassed = 0;
static double SecondsPerTick = 0;
static __int64 GTimeCount = 0;

float Sys_InitFloatTime()
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	SecondsPerTick = 1 / (double)Frequency.QuadPart;

	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);

	GTimeCount = Counter.QuadPart;
	return 0;
}

float Sys_FloatTime()
{
	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);

	__int64 interval = Counter.QuadPart - GTimeCount;
	GTimeCount = Counter.QuadPart;

	double SecondsGoneBy = (double)interval * SecondsPerTick; // No. of ticks * seconds per tick
	GTimePassed += SecondsGoneBy;

	return (float)GTimePassed;
}
////////////////////////////////////////////////////////
//			TIMER CODE END
////////////////////////////////////////////////////////

void Sys_Shutdown()
{
	IsRunning = FALSE;
}

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

int32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCommand)
{
	COM_ParseCmdLine(lpCmdLine);

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
		"Lesson 2.6",
		WindowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

	Host_Init();

	// Initialize time
	float oldtime = Sys_InitFloatTime();
	//float TargetTime = 1.0f / 60.0f; // 60 fps is ideal
	//float TimeAccumulated = 0;

	MSG msg;
	while (IsRunning)
	{
		// Check with OS
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Get the elapsed time
		float newtime = Sys_FloatTime();
		//TimeAccumulated += newtime - oldtime;
		Host_Frame(newtime - oldtime);
		oldtime = newtime;

		/*if (TimeAccumulated > TargetTime)
		{
			// Update game
			Host_Frame(TargetTime);
			TimeAccumulated -= TargetTime;
		}*/
	}

	Host_Shutdown();

	return 0;
}


