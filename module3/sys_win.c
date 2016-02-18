#include <Windows.h>

int BufferWidth = 640;
int BufferHeight = 480;
int Running = 1;
int BytesPerPixel = 1;
void* BackBuffer;


typedef struct 
{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD acolors[256];
}dibinfo_t;

dibinfo_t BitMapInfo = { 0 };

// 32 bit version of DrawRect
void DrawRect32(int X, int Y, int Width, int Height, unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char* Buffer)
{
	unsigned int Color = ((Red << 16) | (Green << 8) | Blue);

	if (X < 0)
		X = 0;

	if (Y < 0)
		Y = 0;

	if ((X + Width) > BufferWidth)
	{
		Width = BufferWidth - X;
	}

	if ((Y + Height) > BufferHeight)
	{
		Height = BufferHeight - Y;
	}

	Buffer += (BufferWidth * BytesPerPixel * Y) + (X * BytesPerPixel);

	int* BufferWalker = (int*)Buffer;

	for (int HeightWalker = 0; HeightWalker < Height; HeightWalker++)
	{
		for (int WidthWalker = 0; WidthWalker < Width; WidthWalker++)
		{
			*BufferWalker++ = Color;
		}

		Buffer += BufferWidth * BytesPerPixel;
		BufferWalker = (int *)Buffer;
	}
}

// 8 bit version of our DrawRect function
void DrawRect8(int X, int Y, int Width, int Height, unsigned char Color, unsigned char* Buffer)
{
	if (X < 0)
		X = 0;

	if (Y < 0)
		Y = 0;

	if ((X + Width) > BufferWidth)
	{
		Width = BufferWidth - X;
	}

	if ((Y + Height) > BufferHeight)
	{
		Height = BufferHeight - Y;
	}

	Buffer += (BufferWidth * BytesPerPixel * Y) + (X * BytesPerPixel);

	unsigned char* BufferWalker = (unsigned char*)Buffer;

	for (int HeightWalker = 0; HeightWalker < Height; HeightWalker++)
	{
		for (int WidthWalker = 0; WidthWalker < Width; WidthWalker++)
		{
			*BufferWalker++ = Color;
		}

		Buffer += BufferWidth * BytesPerPixel;
		BufferWalker = (unsigned char*)Buffer;
	}

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (uMsg)
	{
		case WM_DESTROY:
			Running = 0;
			break;

		case WM_KEYUP:
			//Running = 0;
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

	BOOL FullScreen = FALSE;

	if (FullScreen)
	{
		DEVMODE dmScreenSettings = { 0 };
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = BufferWidth;
		dmScreenSettings.dmPelsHeight = BufferHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
		{
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
		}
		else
		{
			FullScreen = FALSE;
		}
	}

	RECT r = { 0 };
	r.right = BufferWidth;
	r.bottom = BufferHeight;
	AdjustWindowRectEx(&r, dwStyle, 0, dwExStyle);

	// Create Window
	HWND MainWindow = CreateWindowEx(
		dwExStyle,
		"Module3",
		"Lesson 3.3",
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		hInstance,
		0);

	if (FullScreen)
		SetWindowLong(MainWindow, GWL_STYLE, 0);

	ShowWindow(MainWindow, nShowCmd);

	// Define our Bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = -BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = malloc(BufferWidth * BufferHeight * BytesPerPixel); 

	if (BytesPerPixel == 1)
	{
		BitMapInfo.acolors[0].rgbRed = 0;
		BitMapInfo.acolors[0].rgbGreen = 0;
		BitMapInfo.acolors[0].rgbBlue = 0;

		for (int i = 1; i < 256; i++)
		{
			BitMapInfo.acolors[i].rgbRed = rand() % 256;
			BitMapInfo.acolors[i].rgbGreen = rand() % 256;
			BitMapInfo.acolors[i].rgbBlue = rand() % 256;
		}
	}

	MSG msg;
	while (Running)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// For 32 bits per pixel we draw in the following way
		if (BytesPerPixel == 4)
		{
			int* MemoryWalker = (int*)BackBuffer;

			for (int Height = 0; Height < BufferHeight; Height++)
			{
				for (int Width = 0; Width < BufferWidth; Width++)
				{
					unsigned char Red = rand() % 256;
					unsigned char Green = rand() % 256;
					unsigned char Blue = rand() % 256;

					*MemoryWalker++ = ((Red << 16) | (Green << 8) | Blue);
				}
			}
			DrawRect32(10, 10, 300, 150, 255, 0, 255, BackBuffer);
		}
		else
		{
			// For 8 bits per pixel we draw in the following way
			unsigned char* MemoryWalker = (unsigned char*)BackBuffer;

			for (int Height = 0; Height < BufferHeight; Height++)
			{
				for (int Width = 0; Width < BufferWidth; Width++)
				{
					*MemoryWalker++ = rand() % 256;
				}
			}
			DrawRect8(10, 10, 300, 150, 1, BackBuffer);
		}

		HDC dc = GetDC(MainWindow);

		StretchDIBits(dc,
			0, 0, BufferWidth, BufferHeight,
			0, 0, BufferWidth, BufferHeight,
			BackBuffer, (BITMAPINFO *)&BitMapInfo,
			DIB_RGB_COLORS, SRCCOPY);

		DeleteDC(dc);
	}

	return EXIT_SUCCESS;
}
