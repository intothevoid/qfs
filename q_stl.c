#include "quakedef.h"

// Copy strings
void Q_strcpy(uint8* dst, const uint8* src) 
{
	while (*src)
		*dst++ = *src++;

	*dst = '\0';
}

// Copy strings, with size
void Q_strncpy(uint8* dst, const uint8* src, int32 len) 
{
	if (len < 0)
		return;

	while (*src && len)
	{
		*dst++ = *src++;
		--len;
	}

	while (len)
	{
		*dst = '\0';
		--len;
	}
}

// Length of a string
int32 Q_strlen(uint8* str)
{
	int32 len = 0;

	while (str[len])
		++len;

	return len;
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
