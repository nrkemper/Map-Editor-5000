#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

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
	tilewindow.nTiles			= 0;
	tilewindow.nMaxTiles		= MAX_TILE_INCREASE;
	tilewindow.tiles			= 0;
	tilewindow.toppadding		= DEFAULT_TOPPADDING;
	tilewindow.bottompadding	= DEFAULT_BOTTOMPADDING;
	tilewindow.leftpadding		= DEFAULT_LEFTPADDING;
	tilewindow.rightpadding		= DEFAULT_RIGHTPADDING;
	tilewindow.rowPadding		= DEFAULT_ROWPADDING;
	tilewindow.colPadding		= DEFAULT_COLPADDING;

	tilewindow.tiles = (sprite_t**) malloc (tilewindow.nMaxTiles * sizeof (sprite_t*));

	if (tilewindow.tiles == NULL)
	{
		MessageBox (NULL, "Error allocating memory for tiles", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	}

	for (i=0 ; i<tilewindow.nMaxTiles ; i++)
		tilewindow.tiles[i] = 0;
}

void TW_DrawTileWindow (void)
{

}

int TW_LoadTile (const char* file)
{
	if (tilewindow.nTiles < tilewindow.nMaxTiles - 1)
	{
		tilewindow.tiles[tilewindow.nTiles] = LoadSpriteFile (file);

		if (tilewindow.tiles[tilewindow.nTiles] != NULL)
		{
			MessageBox (NULL, "Successfully load tile", "SUCCESS", MB_OK);
		}
		else
		{
			char		buffer[256];

			sprintf (buffer, "Failed to load tile: %s", file);
			MessageBox (NULL, buffer, "ERROR", MB_OK);
		}
	}
}

int TW_RemoveTile (int index)
{

}

void TW_Shutdown (void)
{
	int			i;

	for (i=0 ; i<tilewindow.nMaxTiles ; i++)
	{
		if (tilewindow.tiles[i])
		{
			FreeSprite (tilewindow.tiles[i]);
		}
	}

	free (tilewindow.tiles);
}