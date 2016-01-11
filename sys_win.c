#include <Windows.h>

#define MAX_NUM_ARGVS 50

int argc = 1;
char* largv[MAX_NUM_ARGVS];

int COM_CheckParm(char* parm)
{
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(parm, largv[i]))
		{
			return i;
		}
	}

	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	largv[argc] = "";

	while (*lpCmdLine && (argc < MAX_NUM_ARGVS))
	{
		while (*lpCmdLine && (*lpCmdLine <= 32 || *lpCmdLine > 126))
			lpCmdLine++;

		if (*lpCmdLine)
		{
			largv[argc++] = lpCmdLine;

			while (*lpCmdLine && (*lpCmdLine > 32 && *lpCmdLine <= 126))
				lpCmdLine++;
		}

		if (*lpCmdLine)
			*lpCmdLine++ = 0;
	}

	// Clear out
	largv[argc] = "";

	// Tests
	// int test = COM_CheckParm("-setalpha");
	// int value = atoi(largv[3]);

	return 0;
}