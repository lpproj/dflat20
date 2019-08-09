/* ---------------- video.h ----------------- */

#ifndef VIDEO_H
#define VIDEO_H

#include "rect.h"

void getvideo(RECT, void far *);
void storevideo(RECT, void far *);
extern unsigned video_mode;
extern unsigned video_page;
extern unsigned video_columns;
extern unsigned video_rows;
void wputch(WINDOW, int, int, int);
unsigned int GetVideoChar(int, int);
void PutVideoChar(int, int, int);
void get_videomode(void);
void wputs(WINDOW, void *, int, int);
void scroll_window(WINDOW, RECT, int);

#define clr(fg,bg) ((fg)|((bg)<<4))
#define vad(x,y) ((y)*(video_columns*2)+(x)*2)
#define ismono() (video_mode == 7)
#if defined DOSV
#define istext() (video_mode < 4 || video_mode == 0x70)
#else
#define istext() (video_mode < 4)
#endif
#define videochar(x,y) (GetVideoChar(x,y) & 255)

#endif
