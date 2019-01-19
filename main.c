#include <Windows.h>
#include <WindowsX.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vid.h"
#include "frame.h"
#include "mouse.h"
#include "mapwindow.h"
#include "resource.h"
#include "tilewindow.h"
#include "map.h"

HINSTANCE	global_hInstance;
HINSTANCE	global_hPrevInstance;
int			global_nCmdShow;
HWND		main_window;

void DrawWindow ()
{
	memset (vid.buffer, 0xff, vid.width * vid.height * sizeof (pixel));
	F_DrawFrame ();
	//MAPW_DrawMapWindow ();
	TW_DrawTileWindow ();
	VID_UpdateScreen ();
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_COMMAND:
			switch (LOWORD (wParam))
			{
				case ID_FILE_OPEN:
				case ID_FILE_SAVE:
				case ID_FILE_SAVEAS:
					MessageBox (NULL, "NOT FUCKING SET YET!!&$*$MKSHS*", "ERROR", MB_OK);
					break;

				case ID_FILE_LOAD_TILE:
					{
						OPENFILENAME	file;
						char			filename[256]="";//FIXME: change this to max path

						ZeroMemory (&file, sizeof (file));
						file.lStructSize	= OPENFILENAME_SIZE_VERSION_400;
						file.hwndOwner		= hwnd;
						file.lpstrFilter	= "Sprite Files (*.spt)\0*.spt\0All Files (*.*)\0*.*\0";
						file.lpstrFile		= filename;
						file.nMaxFile		= 256;
						file.Flags			= OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						file.lpstrDefExt	= "spt";

						if (GetOpenFileName (&file))
						{
							MAP_AddTile (filename);
						}
						else
						{
							char	buffer[500];

							sprintf (buffer, "Failed to open file %s", file.lpstrFile);
							MessageBox (NULL, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
						}
						DrawWindow ();
					}
					break;

				case ID_FILE_EXIT:

				case ID_EDIT_UNDO:
				case ID_EDIT_CUT:
				case ID_EDIT_COPY:
				case ID_EDIT_PASTE:
				case ID_EDIT_DELETE:
					MessageBox (NULL, "NOT FUCKING SET YET!!&$*$MKSHS*", "ERROR", MB_OK);
					break;
			}
			break;
		case WM_MOUSEMOVE:
			{
				int		x, y;

				x = GET_X_LPARAM(lParam);
				y = GET_Y_LPARAM(lParam);

				if (x < mapwindow.width && y < mapwindow.height)
				{
					MAPW_HighlightTile (x, y);
					VID_UpdateScreen ();
				}

				if (draglefthorizontal)
				{
					F_MoveLeftHorizontalBorder (y);
					DrawWindow ();
				}
				else if (dragmiddle)
				{
					F_MoveMiddleBorder (x);
					DrawWindow ();
				}
				else if (dragrighthorizontal)
				{
					F_MoveRightHorizontalBorder (y);
					DrawWindow ();
				}
				else
				{
					int		hoverstate;

					hoverstate = F_IsHovering (x, y);

					if (hoverstate & HOVER_MIDDLE)
					{
						hoveringEastWest = 1;
					}
					else if (hoverstate & HOVER_LEFTHORIZONTAL)
					{
						hoveringNorthSouth = 1;
					}
					else if (hoverstate & HOVER_RIGHTHORIZONTAL)
					{
						hoveringNorthSouth = 1;
					}
					else
					{
						hoveringEastWest = 0;
						hoveringNorthSouth = 0;
					}
				}
			}
			break;

		case WM_LBUTTONDOWN:
			{
				int		x, y, hoverstate;
			
				x = GET_X_LPARAM(lParam);
				y = GET_Y_LPARAM(lParam);

				hoverstate = F_IsHovering (x, y);

				if (hoverstate & HOVER_LEFTHORIZONTAL)
				{
					draglefthorizontal = 1;
				}
				else if (hoverstate & HOVER_MIDDLE)
				{
					dragmiddle = 1;
				}
				else if (hoverstate & HOVER_RIGHTHORIZONTAL)
				{
					dragrighthorizontal = 1;
				}
				else
				{
					draglefthorizontal = dragmiddle = dragrighthorizontal = 0;
				}
			}
			break;

		case WM_LBUTTONUP:
			draglefthorizontal = dragmiddle = dragrighthorizontal = 0;
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_LEFT:
					mapwindow.offset_x--;
					DrawWindow();
					break;

				case VK_RIGHT:
					mapwindow.offset_x++;
					DrawWindow();
					break;

				case VK_UP:
					mapwindow.offset_y--;
					DrawWindow();
					break;

				case VK_DOWN:
					mapwindow.offset_y++;
					DrawWindow();
					break;
			}
			break;

		case WM_SETCURSOR:	
			M_SetCursor ();
			break;

		//FIXME: F_Resize ()
		case WM_SIZE:
			{
				RECT	rect;
				int		oldWidth, oldHeight;

				oldWidth = vid.width;
				oldHeight = vid.height;

				GetClientRect (main_window, &rect);
				VID_Resize (rect.right, rect.bottom);
				
				frame.lefthor.y0 = frame.lefthor.y1 = ceil (((double)frame.lefthor.y0 / (double)oldHeight) * (double)vid.height);
				frame.middle.x0 = frame.middle.x1 = ceil(((double)frame.middle.x0 / (double)oldWidth) * (double)vid.width);
				frame.righthor.y0 = frame.righthor.y1 = ceil (((double)frame.righthor.y0 / (double)oldHeight) * (double)vid.height);

				DrawWindow ();
			}
			break;

		case WM_CLOSE:
			if (MessageBox (NULL, "Are you sure you want to quit?", "Quit?", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				VID_Shutdown ();
				M_Shutdown ();
				MAPW_Shutdown ();
				TW_Shutdown ();
				MAP_Shutdown ();
			}
			break;

		case WM_DESTROY:
			PostQuitMessage (0);
			break;
		
		default:
			return DefWindowProc (hwnd, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;

	global_hInstance		= hInstance;
	global_hPrevInstance	= hPrevInstance;
	global_nCmdShow			= nCmdShow;

	VID_InitVGA ();
	MAP_InitMap ();
	M_InitMouse ();
	F_InitFrame ();
	MAPW_InitMapWindow ();
	TW_InitTileWindow ();

	DrawWindow ();

	while (GetMessage (&msg, main_window, 0, 0) > 0)
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return 0;
}