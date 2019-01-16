#include "frame.h"
#include "mapwindow.h"
#include "vid.h"

frame_t		frame;

//FLAGS
int			hoveringEastWest=0;
int			hoveringNorthSouth=0;
int			draglefthorizontal=0;
int			dragmiddle=0;
int			dragrighthorizontal=0;

void F_InitFrame (void)
{
	frame.middle.x0 = vid.width / 3 * 2;
	frame.middle.x1	= vid.width / 3 * 2;
	frame.middle.y0 = 0;
	frame.middle.y1 = vid.height;

	frame.lefthor.x0 = 0;
	frame.lefthor.x1 = vid.width;
	frame.lefthor.y0 = vid.height / 3 * 2;
	frame.lefthor.y1 = vid.height / 3 * 2;

	frame.righthor.x0 = frame.middle.x0 +1;
	frame.righthor.x1 = vid.width;
	frame.righthor.y0 = vid.height / 3;
	frame.righthor.y0 = vid.height / 3;

	F_DrawFrame ();
}

void F_DrawFrame (void)
{
	int		x, y;

	//Draw middle border
	for (y=0 ; y<vid.height ; y++)
	{
		*(vid.buffer + (y * vid.width) + frame.middle.x0 - 1)	= RGBTOPIXEL (0x33, 0x33, 0x33, 0);
		*(vid.buffer + (y * vid.width) + frame.middle.x0)		= RGBTOPIXEL (0x66, 0x66, 0x66, 0);
		*(vid.buffer + (y * vid.width) + frame.middle.x0 + 1)	= RGBTOPIXEL (0x33, 0x33, 0x33, 0);
	}

	for (x=0 ; x<frame.middle.x0 ; x++)
	{	
		*(vid.buffer + ((frame.lefthor.y0 - 1) * vid.width) + x)= RGBTOPIXEL (0x33, 0x33, 0x33, 0);
		*(vid.buffer + (frame.lefthor.y0 * vid.width) + x)		= RGBTOPIXEL (0x66, 0x66, 0x66, 0);
		*(vid.buffer + ((frame.lefthor.y0 + 1) * vid.width) + x)= RGBTOPIXEL (0x33, 0x33, 0x33, 0);
	}
	
	for (x=frame.middle.x0+1 ; x<vid.width ; x++)
	{
		*(vid.buffer + ((frame.righthor.y0 - 1) * vid.width) + x) = RGBTOPIXEL (0x33, 0x33, 0x33, 0);
		*(vid.buffer + (frame.righthor.y0 * vid.width) + x) = RGBTOPIXEL (0x66, 0x66, 0x66, 0);
		*(vid.buffer + ((frame.righthor.y0 + 1) * vid.width) + x) = RGBTOPIXEL (0x33, 0x33, 0x33, 0);
	}
}

void F_MoveMiddleBorder (int x)
{
	if (x < 1)
		x = 1;

	if (x > vid.width - 2)
		x = vid.width - 2;

	frame.middle.x0 = frame.middle.x1 = x;
	mapwindow.width = x - 1;
}

void F_MoveLeftHorizontalBorder (int y)
{
	if (y < 1)
		y = 1;

	if (y > vid.height - 2)
		y = vid.height - 2;

	frame.lefthor.y0 = frame.lefthor.y1 = y;
	mapwindow.height = y - 1;
}

void F_MoveRightHorizontalBorder (int y)
{
	if (y < 1)
		y = 1;

	if (y > vid.height - 2)
		y = vid.height - 2;

	frame.righthor.y0 = frame.righthor.y1 = y;
}

int F_IsHovering (int mouse_x, int mouse_y)
{
	int		ret = 0;

	if (mouse_x <= frame.middle.x0 + 3 && mouse_x >= frame.middle.x0 - 3)
		ret |= HOVER_MIDDLE;

	if (mouse_y <= frame.lefthor.y0 + 3 && mouse_y >= frame.lefthor.y0 - 3)
		if (mouse_x < frame.middle.x0)
			ret |= HOVER_LEFTHORIZONTAL;

	if (mouse_y <= frame.righthor.y0 + 3 && mouse_y >= frame.righthor.y0 - 3)
		if (mouse_x > frame.middle.x0)
			ret |= HOVER_RIGHTHORIZONTAL;

	return ret;
}