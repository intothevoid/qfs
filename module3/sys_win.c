#include <Windows.h>

int BufferWidth = 640;
int BufferHeight = 480;
int Running = 1;

void* BackBuffer;
BITMAPINFO BitMapInfo = { 0 };


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (uMsg)
	{
		case WM_KEYUP:
			Running = 0;
			break;
		
		default:
			Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
	}

	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLIne, int nShowCmd)
{
	// Define our window class
	WNDCLASSEX  wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "Module3";

	// Register window class
	RegisterClassEx(&wc);

	// Window styles
	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	RECT r = { 0 };
	r.right = BufferWidth;
	r.bottom = BufferHeight;
	AdjustWindowRectEx(&r, dwStyle, 0, dwExStyle);

	// Create Window
	HWND MainWindow = CreateWindowEx(
		dwExStyle,
		"Module3",
		"Lesson 3.2",
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		hInstance,
		0);

	ShowWindow(MainWindow, nShowCmd);

	// Define our Bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 32;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = malloc(BufferWidth * BufferHeight * 4); // 4 bytes per pixel

	MSG msg;
	while (Running)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		int* MemowryWalker = (int*)BackBuffer;

		for (int Height = 0; Height < BufferHeight; Height++)
		{
			for (int  Width = 0; Width < BufferWidth; Width++)
			{
				char Red = 0xFF;
				char Green = 0;
				char Blue = 0;

				*MemowryWalker++ = ((Red << 16) | (Green << 8) | Blue);
			}
		}
	}


	

	return EXIT_SUCCESS;
}
