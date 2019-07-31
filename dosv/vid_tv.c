/* --------------------- vid_tv.c (based on video.c) -------------------- */

#include "dflat.h"
#if defined DOSV
# define TOPVIEW 1
#endif

#if !defined pTab
# define pTab ('\t' + 0x80)
# define sTab ('\f' + 0x80)
#endif

BOOL ClipString;
static BOOL snowy;

static unsigned video_address;
#if TOPVIEW
static BOOL topview;
char far *tv_address = NULL;
static void near tvredraw(unsigned offset, int len);
static void near movetotvscreen(void *bf, unsigned offset, int len);
static void near movefromtvscreen(void *bf, unsigned offset, int len);
static unsigned short near tvpeek(unsigned vadr);
static void near tvpoke(unsigned vadr, unsigned short c);
#else
static unsigned short near vpeek(unsigned short far *vp);
static void near vpoke(unsigned short far *vp, unsigned short c);
static void movefromscreen(void *bf, unsigned offset, int len);
static void movetoscreen(void *bf, unsigned offset, int len);
#endif


/* -- read a rectangle of video memory into a save buffer -- */
void getvideo(RECT rc, void far *bf)
{
    int ht = RectBottom(rc)-RectTop(rc)+1;
    int bytes_row = (RectRight(rc)-RectLeft(rc)+1) * 2;
    unsigned vadr = vad(RectLeft(rc), RectTop(rc));
    unsigned bytes_screencol = SCREENWIDTH * 2U;
    hide_mousecursor();
    while (ht--)    {
#if TOPVIEW
        movefromtvscreen(bf, vadr, bytes_row);
#else
        movefromscreen(bf, vadr, bytes_row);
#endif
        vadr += bytes_screencol;
        bf = (char far *)bf + bytes_row;
    }
    show_mousecursor();
}

/* -- write a rectangle of video memory from a save buffer -- */
void storevideo(RECT rc, void far *bf)
{
    int ht = RectBottom(rc)-RectTop(rc)+1;
    int bytes_row = (RectRight(rc)-RectLeft(rc)+1) * 2;
    unsigned vadr = vad(RectLeft(rc), RectTop(rc));
    unsigned bytes_screencol = SCREENWIDTH * 2U;

    hide_mousecursor();
    while (ht--)    {
#if TOPVIEW
        movetotvscreen(bf, vadr, bytes_row);
#else
        movetoscreen(bf, vadr, bytes_row);
#endif
        vadr += bytes_screencol;
        bf = (char far *)bf + bytes_row;
    }
    show_mousecursor();
}

/* -------- read a character of video memory ------- */
unsigned int GetVideoChar(int x, int y)
{
    int c;
    hide_mousecursor();
#if TOPVIEW
    c = tvpeek(vad(x,y));
#else
    if (snowy)
        c = vpeek(MK_FP(video_address, vad(x,y)));
    else
        c = peek(video_address, vad(x,y));
#endif
    show_mousecursor();
    return c;
}

/* -------- write a character of video memory ------- */
void PutVideoChar(int x, int y, int c)
{
    if (x < SCREENWIDTH && y < SCREENHEIGHT)    {
        hide_mousecursor();
#if TOPVIEW
        tvpoke(vad(x,y), c);
#else
        if (snowy)
            vpoke(MK_FP(video_address, vad(x,y)), c);
        else
            poke(video_address, vad(x,y), c);
#endif
        show_mousecursor();
    }
}

BOOL CharInView(WINDOW wnd, int x, int y)
{
    WINDOW nwnd = NextWindow(wnd);
    WINDOW pwnd;
    RECT rc;
    int x1 = GetLeft(wnd)+x;
    int y1 = GetTop(wnd)+y;

    if (!TestAttribute(wnd, VISIBLE))
        return FALSE;
    if (!TestAttribute(wnd, NOCLIP))    {
        WINDOW wnd1 = GetParent(wnd);
        while (wnd1 != NULL)    {
            /* --- clip character to parent's borders -- */
            if (!TestAttribute(wnd1, VISIBLE))
                return FALSE;
            if (!InsideRect(x1, y1, ClientRect(wnd1)))
                return FALSE;
            wnd1 = GetParent(wnd1);
        }
    }
    while (nwnd != NULL)	{
        if (!isHidden(nwnd) /* && !isAncestor(wnd, nwnd) */ )	{
            rc = WindowRect(nwnd);
            if (TestAttribute(nwnd, SHADOW))    {
                RectBottom(rc)++;
                RectRight(rc)++;
            }
            if (!TestAttribute(nwnd, NOCLIP))	{
                pwnd = nwnd;
                while (GetParent(pwnd))	{
                    pwnd = GetParent(pwnd);
                    rc = subRectangle(rc, ClientRect(pwnd));
                }
            }
            if (InsideRect(x1,y1,rc))
                return FALSE;
        }
        nwnd = NextWindow(nwnd);
    }
    return (x1 < SCREENWIDTH && y1 < SCREENHEIGHT);
}

/* -------- write a character to a window ------- */
void wputch(WINDOW wnd, int c, int x, int y)
{
    if (CharInView(wnd, x, y))	{
        int ch = (c & 255) | (clr(foreground, background) << 8);
        int xc = GetLeft(wnd)+x;
        int yc = GetTop(wnd)+y;
        hide_mousecursor();
#if TOPVIEW
        tvpoke(vad(xc,yc), ch);
#else
        if (snowy)
            vpoke(MK_FP(video_address, vad(xc, yc)), ch);
        else
            poke(video_address, vad(xc, yc), ch);
#endif
        show_mousecursor();
    }
}

/* ------- write a string to a window ---------- */
void wputs(WINDOW wnd, void *s, int x, int y)
{
    int x1 = GetLeft(wnd)+x;
    int x2 = x1;
    int y1 = GetTop(wnd)+y;
    if (x1 < SCREENWIDTH && y1 < SCREENHEIGHT && isVisible(wnd))	{
        short ln[256];
        short *cp1 = ln;
        unsigned char *str = s;
        int fg = foreground;
        int bg = background;
        int len;
        int off = 0;
        while (*str)    {
            if (*str == CHANGECOLOR)    {
                str++;
                foreground = (*str++) & 0x7f;
                background = (*str++) & 0x7f;
                continue;
            }
            if (*str == RESETCOLOR)    {
                foreground = fg & 0x7f;
                background = bg & 0x7f;
                str++;
                continue;
            }
#if defined(pTab) && defined(sTab)
            if (*str == pTab || *str == sTab)
                *cp1 = ' ' | (clr(foreground, background) << 8);
            else 
#endif
                *cp1 = (*str & 255) | (clr(foreground, background) << 8);
            if (ClipString)
                if (!CharInView(wnd, x, y))
                    *cp1 = peek(video_address, vad(x2,y1));
            cp1++;
            str++;
            x++;
            x2++;
        }
        foreground = fg;
        background = bg;
        len = (int)(cp1-ln);
        if (x1+len > SCREENWIDTH)
            len = SCREENWIDTH-x1;

        if (!ClipString && !TestAttribute(wnd, NOCLIP)) {
            /* -- clip the line to within ancestor windows -- */
            RECT rc = WindowRect(wnd);
            WINDOW nwnd = GetParent(wnd);
            while (len > 0 && nwnd != NULL)	{
                if (!isVisible(nwnd))	{
                    len = 0;
                    break;
                }
                rc = subRectangle(rc, ClientRect(nwnd));
                nwnd = GetParent(nwnd);
            }
            while (len > 0 && !InsideRect(x1+off,y1,rc))	{
                off++;
                --len;
            }
            if (len > 0)    {
                x2 = x1+len-1;
                while (len && !InsideRect(x2,y1,rc))	{
                    --x2;
                    --len;
                }
            }
        }
        if (len > 0)    {
            hide_mousecursor();
#if TOPVIEW
            movetotvscreen(ln+off, vad(x1+off,y1), len*2);
#else
            movetoscreen(ln+off, vad(x1+off,y1), len*2);
#endif
            show_mousecursor();
        }
    }
}

/* --------- get the current video mode -------- */
void get_videomode(void)
{
    videomode();
    /* ---- Monochrome Display Adaptor or text mode ---- */
    snowy = FALSE;
    if (ismono())
        video_address = 0xb000;
    else    {
        /* ------ Text mode -------- */
        video_address = 0xb800 + video_page;
        if (!isEGA() && !isVGA())
            /* -------- CGA --------- */
            snowy = cfg.snowy;
    }
#if TOPVIEW
    if (tv_address == NULL) {
        union REGS regs;
        struct SREGS sregs;
        regs.h.ah = 0xfe;
        regs.x.di = 0;
        sregs.es = video_address;
        int86x(VIDEO, &regs, &regs, &sregs);
        tv_address = MK_FP(sregs.es, regs.x.di);
        topview = (sregs.es != video_address || regs.x.di);
        if (topview) {
            snowy = FALSE;
        }
    }
#endif
}

/* --------- scroll the window. d: 1 = up, 0 = dn ---------- */
void scroll_window(WINDOW wnd, RECT rc, int d)
{
    if (RectTop(rc) != RectBottom(rc))	{
        union REGS regs;
        regs.h.cl = RectLeft(rc);
        regs.h.ch = RectTop(rc);
        regs.h.dl = RectRight(rc);
        regs.h.dh = RectBottom(rc);
        regs.h.bh = clr(WndForeground(wnd),WndBackground(wnd));
        regs.h.ah = 7 - d;
        regs.h.al = 1;
        hide_mousecursor();
        int86(VIDEO, &regs, &regs);
        show_mousecursor();
    }
}


static void near waitforretrace(void)
{
#ifdef __SMALLER_C__
#else
#ifndef WATCOM
asm		mov		dx,3dah
loop1:
asm		mov		cx,6
loop2:
asm		in		al,dx
asm		test	al,8
asm		jnz		loop2
asm		test	al,1
asm		jz		loop2
asm		cli
loop3:
asm		in		al,dx
asm		test	al,1
asm		loopnz	loop3
asm		sti
asm		jz		loop1
#endif
#endif
}

#if TOPVIEW
void near tvredraw(unsigned offset, int len)
{
    union REGS regs;
    struct SREGS sregs;

    regs.h.ah = 0xff;
    sregs.es = FP_SEG(tv_address);
    regs.x.di = FP_OFF(tv_address) + offset;
    regs.x.cx = len >> 1;
    if (regs.x.cx) int86x(VIDEO, &regs, &regs, &sregs);
}

void near movetotvscreen(void *bf, unsigned offset, int len)
{
    if (snowy)
        waitforretrace();
    movedata(FP_SEG(bf), FP_OFF(bf), FP_SEG(tv_address), FP_OFF(tv_address) + offset, len);
    if (topview)
        tvredraw(offset, len);
}

void near movefromtvscreen(void *bf, unsigned offset, int len)
{
    if (snowy)
        waitforretrace();
    movedata(FP_SEG(tv_address), FP_OFF(tv_address) + offset, FP_SEG(bf), FP_OFF(bf), len);
    if (topview)
        tvredraw(offset, len);
}

unsigned short near tvpeek(unsigned vadr)
{
    if (snowy)
        waitforretrace();
    return *(unsigned short far *)(tv_address + vadr);
}

void near tvpoke(unsigned vadr, unsigned short c)
{
    if (snowy)
        waitforretrace();
    *(unsigned short far *)(tv_address + vadr) = c;
    if (topview)
    tvredraw(vadr, 2);
}

#else
void movetoscreen(void *bf, unsigned offset, int len)
{
    if (snowy)
        waitforretrace();
    movedata(FP_SEG(bf), FP_OFF(bf), video_address, offset, len);
}

void movefromscreen(void *bf, unsigned offset, int len)
{
    if (snowy)
        waitforretrace();
    movedata(video_address, offset,	FP_SEG(bf), FP_OFF(bf),	len);
}


static unsigned short near vpeek(unsigned short far *vp)
{
    unsigned short c;
    waitforretrace();
    c = *vp;
    return c;
}

static void near vpoke(unsigned short far *vp, unsigned short c)
{
    waitforretrace();
    *vp = c;
}

#endif
