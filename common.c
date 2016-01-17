#include "quakedef.h"

// Command line arguments
int32 com_argc = 1;
uint8* com_largv[MAX_NUM_ARGVS + 1];

int32 COM_CheckParm(uint8* parm)
{
	for (int32 i = 1; i < com_argc; i++)
	{
		if (!Q_strcmp(parm, com_largv[i]))
		{
			return i;
		}
	}

	return 0;
}