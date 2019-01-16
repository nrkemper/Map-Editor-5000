#include <Windows.h>
#include <stdlib.h>
#include "vid.h"
#include "resource.h"

vid_t	vid;

extern HINSTANCE	global_hInstance;
extern HINSTANCE	global_hPrevInstance;
extern int			global_nCmdShow;
extern HWND			main_window;

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void VID_InitVGA (void)
{
	RECT	rect;
	WNDCLASSEX	wc;
	const char	className[] = "Main Window Class";

	wc.cbSize        = sizeof(WNDCLASSEX);
		wc.style         = 0;
		wc.lpfnWndProc   = WndProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = global_hInstance;
		wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor       = NULL;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wc.lpszMenuName  = MAKEINTRESOURCE (IDR_MAINMENU);
		wc.lpszClassName = className;
		wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx (&wc))
	{
		MessageBox (NULL, "Unable to register main window class", "ERROR!", MB_OK | MB_ICONEXCLAMATION);
		exit (-1);
	}

	main_window = CreateWindowEx (
					WS_EX_CLIENTEDGE,
					className,
					"Map Editor 5000",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT,
					500, 500,
					NULL, NULL,
					global_hInstance,
					NULL);

	if (main_window == NULL)
	{
		MessageBox (NULL, "Unable to create main window", "ERROR!", MB_OK | MB_ICONEXCLAMATION);
		exit (-1);
	}

	UpdateWindow (main_window);
	ShowWindow (main_window, global_nCmdShow);

	GetClientRect (main_window, &rect);

	//windows pixel format: aaaaaaaarrrrrrrrggggggggbbbbbbbb
	vid.pfrmt.bitspixel		= 32;
	vid.pfrmt.alphashift	= 24;
	vid.pfrmt.alphamask		= 0x000000ff << vid.pfrmt.alphashift;
	vid.pfrmt.redshift		= 16;
	vid.pfrmt.redmask		= 0x000000ff << vid.pfrmt.redshift;	
	vid.pfrmt.greenshift	= 8;
	vid.pfrmt.greenmask		= 0x000000ff << vid.pfrmt.greenshift;	
	vid.pfrmt.blueshift		= 0;
	vid.pfrmt.bluemask		= 0x000000ff << vid.pfrmt.blueshift;
	vid.width				= rect.right;
	vid.height				= rect.bottom;	

	VID_CreateBuffer ();
}

void VID_CreateBuffer (void)
{
	vid.buffer = (pixel*) malloc (vid.width * vid.height * sizeof (pixel));
	memset (vid.buffer, 0xff, vid.width * vid.height * sizeof (pixel));
}

void VID_Resize (int width, int height)
{
	vid.width	= width;
	vid.height	= height;

	VID_DestroyVGA();
	VID_CreateBuffer ();
}

void VID_DestroyVGA (void)
{
	if (vid.buffer)
		free (vid.buffer);
}


void VID_UpdateScreen (void)
{
	HDC				screenHDC, memHDC;
	HBITMAP			hbmBuffer, hbmOldBuffer;

	screenHDC		= GetDC (main_window);
	memHDC			= CreateCompatibleDC (screenHDC);

	hbmBuffer		= CreateBitmap (vid.width, vid.height, 1, vid.pfrmt.bitspixel, vid.buffer);
	hbmOldBuffer	= (HBITMAP)SelectObject (memHDC, hbmBuffer);

	BitBlt (screenHDC, 0, 0, vid.width, vid.height, memHDC, 0, 0, SRCCOPY);

	SelectObject (memHDC, hbmOldBuffer);

	DeleteObject (hbmBuffer);
	ReleaseDC (main_window, screenHDC);
	DeleteDC (memHDC);
}

void VID_Shutdown (void)
{
	if (vid.buffer)
		free (vid.buffer);

	DestroyWindow (main_window);
}