#ifndef __graphics_H__
#define __graphics_H__

#include "ili9320.h"

// a 2D vertex
typedef struct VERTEX2DI_TYP
{
	int x,y; // the vertex
} VERTEX2DI, *VERTEX2DI_PTR;

// a 2D vertex
typedef struct VERTEX2DF_TYP
{
	float x,y; // the vertex
} VERTEX2DF, *VERTEX2DF_PTR;



// a 2D polygon
typedef struct POLYGON2D_TYP
{
	unsigned char state;        // state of polygon
	unsigned char num_verts;    // number of vertices
	int x0,y0;        // position of center of polygon
	int xv,yv;        // initial velocity
	LCD_Color_t color;      // could be index or PALETTENTRY
	VERTEX2DF vlist[8]; // pointer to vertex list

} POLYGON2D, *POLYGON2D_PTR;



int Draw_Polygon2D(POLYGON2D_PTR poly);
int Translate_Polygon2D(POLYGON2D_PTR poly, int dx, int dy);
int Rotate_Polygon2D(POLYGON2D_PTR poly, int theta);
void DrawSolidTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color );
void Draw_Line(float x1, float y1, float x2, float y2, u16 color);
void Draw_Rect(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width,
                u16 color);

int fsin( short alpha);
int fcos( short alpha);

#endif
