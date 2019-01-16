#ifndef __MOUSE_H__
#define __MOUSE_H__

#define CURSOR_DEFAULT		0
#define CURSOR_RESIZE_NS	1
#define CURSOR_RESIZE_EW	2

typedef struct point_s
{
	int		x;
	int		y;
} point_t;

typedef struct mousestate_s
{
	char		lbutton;
	char		rbutton;
	char		mbutton;
	char		x1;
	char		x2;
	point_t		lbuttonpressxy;//where the left button was pressed
} mousestate_t;

mousestate_t	mouse;

void M_InitMouse (void);
void M_ProcessInput (int msg, int wParam, int lParam);
void M_SetCursor (void);
void M_Shutdown (void);

#endif