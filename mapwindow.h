#ifndef __MAPWINDOW_H__
#define __MAPWINDOW_H__

#define DEFAULT_BORDER_WIDTH_X	1
#define DEFAULT_BORDER_WIDTH_Y	1

typedef struct mapwindow_s
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				offset_x;
	int				offset_y;
	char			borderwidthX;
	char			borderwidthY;
} mapwindow_t;

extern mapwindow_t		mapwindow;

void MAPWIN_InitMapWindow (void);
void MAPWIN_DrawMapWindow (void);
void MAPWIN_HighlightTile (int x, int y);
void MAPWIN_Shutdown (void);

#endif