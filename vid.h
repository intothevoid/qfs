#pragma once

#include "quakedef.h"
#include "winquake.h"

void VID_Init(void);
void VID_Shutdown(void);
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
