#ifndef __FRAME_H__
#define __FRAME_H__

#define HOVER_MIDDLE				0x01
#define HOVER_LEFTHORIZONTAL		0x01 << 1
#define HOVER_RIGHTHORIZONTAL		0x01 << 2

typedef struct border_s
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
} border_t;

typedef struct frame_s
{
	border_t	lefthor;
	border_t	middle;
	border_t	righthor;
} frame_t;

extern frame_t	frame;
extern int		hoveringEastWest;
extern int		hoveringNorthSouth;
extern int		draglefthorizontal;
extern int		dragmiddle;
extern int		dragrighthorizontal;

void F_InitFrame (void);
void F_DrawFrame (void);
void F_MoveMiddleBorder (int x);
void F_MoveLeftHorizontalBorder (int y);
void F_MoveRightHorizontalBorder (int y);
int F_IsHovering (int mouse_x, int mouse_y);
#endif