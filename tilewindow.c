#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tilewindow.h"
#include "frame.h"
#include "vid.h"
#include "sprite.h"

tilewindow_t		tilewindow;

void TW_InitTileWindow (void)
{
	int		i;

	tilewindow.x				= frame.middle.x0;
	tilewindow.y				= frame.righthor.y0;
	tilewindow.width			= vid.width - tilewindow.x;
	tilewindow.height			= vid.height - tilewindow.y;
	tilewindow.toppadding		= DEFAULT_TOPPADDING;
	tilewindow.bottompadding	= DEFAULT_BOTTOMPADDING;
	tilewindow.leftpadding		= DEFAULT_LEFTPADDING;
	tilewindow.rightpadding		= DEFAULT_RIGHTPADDING;
	tilewindow.rowPadding		= DEFAULT_ROWPADDING;
	tilewindow.colPadding		= DEFAULT_COLPADDING;

}

void TW_DrawTileWindow (void)
{


}			

int TW_LoadTile (const char* file)
{

}

int TW_RemoveTile (int index)
{

}

void TW_Shutdown (void)
{

}