#include "winquake.h"
#include "quakedef.h"

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 cmdShow)
{
	com_largv[com_argc] = "";

	while (*lpCmdLine && (com_argc < MAX_NUM_ARGVS+1))
	{
		while (*lpCmdLine && (*lpCmdLine <= 32 || *lpCmdLine > 126))
			lpCmdLine++;

		if (*lpCmdLine)
		{
			com_largv[com_argc++] = lpCmdLine;

			while (*lpCmdLine && (*lpCmdLine > 32 && *lpCmdLine <= 126))
				lpCmdLine++;
		}

		if (*lpCmdLine)
			*lpCmdLine++ = 0;
	}

	// Tests
	int32 test = COM_CheckParm("-setalpha");
	int32 value = Q_atoi(com_largv[3]);
	int32 result = Q_strcmp("test", "tester");

	return 0;
}

