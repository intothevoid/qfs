#include "winquake.h"
#include "quakedef.h"

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 cmdShow)
{
	com_largv[com_argc] = "";

	COM_ParseCmdLine(lpCmdLine);
	
	// Tests
	// int32 test = COM_CheckParm("-setalpha");
	// int32 value = Q_atoi(com_largv[3]); 
	// int32 result = Q_strcmp("test", "tester");
	// uint8 dst[200] = { 0 };
	// Q_strcpy(dst, "hello there!");
	// int32 len = Q_strlen("foo bar baz pew");
	// Q_strncpy(dst, "lasers pew!", 5);

	return 0;
}
