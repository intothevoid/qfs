#include "quakedef.h"
#include "winquake.h"

static BOOL IsRunning = TRUE;

HINSTANCE GlobalInstance;

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

void Sys_SendKeyEvents(void)
{
	MSG msg;

	// Check with OS
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Sys_Shutdown()
{
	IsRunning = FALSE;
}


int32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCommand)
{
	GlobalInstance = hInstance;

	COM_ParseCmdLine(lpCmdLine);

	Host_Init();

	// Initialize time
	float oldtime = Sys_InitFloatTime();

	while (IsRunning)
	{
		// Get the elapsed time
		float newtime = Sys_FloatTime();
		Host_Frame(newtime - oldtime);
		oldtime = newtime;
	}

	Host_Shutdown();

	return 0;
}


