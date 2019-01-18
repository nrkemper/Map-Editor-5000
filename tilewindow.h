#ifndef __TILEWINDOW_H__
#define __TILEWINDOW_H__

#define DEFAULT_COLPADDING		2//in pixels
#define DEFAULT_ROWPADDING		2
#define DEFAULT_LEFTPADDING		5
#define DEFAULT_RIGHTPADDING	5
#define DEFAULT_TOPPADDING		5
#define DEFAULT_BOTTOMPADDING	5

#include "sprite.h"

typedef struct tilewindow_s
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			toppadding;
	int			bottompadding;
	int			leftpadding;
	int			rightpadding;
	int			rowPadding;
	int			colPadding;
} tilewindow_t;

extern tilewindow_t		tilewindow;

void TW_InitTileWindow (void);
void TW_DrawTileWindow (void);
int TW_LoadTile (const char* file);
int TW_RemoveTile (int index);
void TW_Shutdown (void);

#endif