#include <Windows.h>
#include <stdint.h>

#define MAX_NUM_ARGVS 50

// Faster typing
#define int8 int8_t
#define int32 int32_t 
#define uint8 uint8_t 
#define uint32 uint32_t

// Command line arguments
int32 argc = 1;
uint8* largv[MAX_NUM_ARGVS+1];

int32 COM_CheckParm(uint8* parm)
{
	for (int32 i = 1; i < argc; i++)
	{
		if (!strcmp(parm, largv[i]))
		{
			return i;
		}
	}

	return 0;
}

// Compare two strings
// Return 0 if equal, -1 if s1 < s2 else 1
int32 Q_strcmp(uint8* s1, uint8* s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
			return 0;

		++s1;
		++s2;
	}

	return ((*s1 < *s2) ? -1 : 1);
}

// Convert string to its integer value
// Support hexadecimal
int32 Q_atoi(int8* str)
{
	int32 sign = 1;
	int32 val = 0;
	uint8 c;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	// Hexadecimal
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
	{
		// Move past 0x
		str += 2;

		while (1)
		{			
			c = *str;
			str++;

			if (c >= '0' && c <= '9')
				val = val * 16 + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = val * 16 + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = val * 16 + c - 'A' + 10;
			else
				return val * sign;
		}
	}

	// Decimal
	while (1)
	{
		c = *str;
		str++;

		if (c < '0' || c > '9')
			return sign * val;
		
		val = val * 10 + c - '0';
	}
}

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 cmdShow)
{
	largv[argc] = "";

	while (*lpCmdLine && (argc < MAX_NUM_ARGVS+1))
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

	// Tests
	// int32 test = COM_CheckParm("-setalpha");
	// int32 value = Q_atoi(largv[3]);
	// int32 result = Q_strcmp("test", "tester");

	return 0;
}

