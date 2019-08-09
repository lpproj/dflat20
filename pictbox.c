/* -------------- pictbox.c -------------- */

#include "dflat.h"

typedef struct    {
    enum VectTypes vt;
    RECT rc;
} VECT;

#if defined IBMPC
unsigned char CharInWnd[] = "\xc4\xb3\xda\xbf\xd9\xc0\xc5\xc3\xb4\xc1\xc2";
#else
/*                                0h  1v  2dr 3dl 4ul 5ur 6vh 7vr 8vl 9uh 10dh 11initflag */
unsigned char CharInWndLocal[] = "\xc4\xb3\xda\xbf\xd9\xc0\xc5\xc3\xb4\xc1\xc2\xff";
unsigned char CharInWnd[] =      "\xc4\xb3\xda\xbf\xd9\xc0\xc5\xc3\xb4\xc1\xc2";

static void SetCharInWndLocal(void)
{
    if (CharInWndLocal[11] != '\0') {
        CharInWndLocal[0] = dfc_h;
        CharInWndLocal[1] = dfc_v;
        CharInWndLocal[2] = dfc_dr;
        CharInWndLocal[3] = dfc_dl;
        CharInWndLocal[4] = dfc_ul;
        CharInWndLocal[5] = dfc_ur;
        CharInWndLocal[6] = dfc_vh;
        CharInWndLocal[7] = dfc_vr;
        CharInWndLocal[8] = dfc_vl;
        CharInWndLocal[9] = dfc_uh;
        CharInWndLocal[10] = dfc_dh;
        CharInWndLocal[11] = '\0';
    }
}
static unsigned char ConvCharInWndToLocal(unsigned char ch)
{
    unsigned i;
    for(i=0; i<sizeof(CharInWnd) - 1; ++i) {
        if (ch == CharInWnd[i]) {
            return CharInWndLocal[i];
        }
    }
    return ch;
}
static unsigned char ConvCharInWndFromLocal(unsigned char ch)
{
    unsigned i;
    for(i=0; i<sizeof(CharInWndLocal) - 1; ++i) {
        if (ch == CharInWndLocal[i]) {
            return CharInWnd[i];
        }
    }
    return ch;
}
#endif

unsigned char VectCvt[3][11][2][4] = {
    {   /* --- first character in collision vector --- */
        /* ( drawing \xc4 ) ( drawing \xb3 ) */
             {{"\xc4\xc4\xc4"},     {"\xda\xc3\xc0"}},
             {{"\xda\xc2\xbf"},     {"\xb3\xb3\xb3"}},
             {{"\xda\xc2\xc2"},     {"\xda\xc3\xc3"}},
             {{"\xbf\xbf\xbf"},     {"\xbf\xbf\xbf"}},
             {{"\xd9\xd9\xd9"},     {"\xd9\xd9\xd9"}},
             {{"\xc0\xc1\xc1"},     {"\xc3\xc3\xc0"}},
             {{"\xc5\xc5\xc5"},     {"\xc5\xc5\xc5"}},
             {{"\xc3\xc5\xc5"},     {"\xc3\xc3\xc3"}},
             {{"\xb4\xb4\xb4"},     {"\xb4\xb4\xb4"}},
             {{"\xc1\xc1\xc1"},     {"\xc1\xc1\xc1"}},
             {{"\xc2\xc2\xc2"},     {"\xc2\xc5\xc5"}}    },
    {   /* --- middle character in collision vector --- */
        /* ( drawing \xc4 ) ( drawing \xb3 ) */
             {{"\xc4\xc4\xc4"},     {"\xc2\xc5\xc1"}},
             {{"\xc3\xc5\xb4"},     {"\xb3\xb3\xb3"}},
             {{"\xda\xda\xda"},     {"\xda\xda\xda"}},
             {{"\xbf\xbf\xbf"},     {"\xbf\xbf\xbf"}},
             {{"\xd9\xd9\xd9"},     {"\xd9\xd9\xd9"}},
             {{"\xc0\xc0\xc0"},     {"\xc0\xc0\xc0"}},
             {{"\xc5\xc5\xc5"},     {"\xc5\xc5\xc5"}},
             {{"\xc3\xc3\xc3"},     {"\xc3\xc3\xc3"}},
             {{"\xc5\xc5\xb4"},     {"\xb4\xb4\xb4"}},
             {{"\xc1\xc1\xc1"},     {"\xc5\xc5\xc1"}},
             {{"\xc2\xc2\xc2"},     {"\xc2\xc2\xc2"}}    },
    {   /* --- last character in collision vector --- */
        /* ( drawing \xc4 ) ( drawing \xb3 ) */
             {{"\xc4\xc4\xc4"},     {"\xbf\xb4\xd9"}},
             {{"\xc0\xc1\xd9"},     {"\xb3\xb3\xb3"}},
             {{"\xda\xda\xda"},     {"\xda\xda\xda"}},
             {{"\xc2\xc2\xbf"},     {"\xbf\xb4\xb4"}},
             {{"\xc1\xc1\xd9"},     {"\xb4\xb4\xd9"}},
             {{"\xc0\xc0\xc0"},     {"\xc0\xc0\xc0"}},
             {{"\xc5\xc5\xc5"},     {"\xc5\xc5\xc5"}},
             {{"\xc3\xc3\xc3"},     {"\xc3\xc3\xc3"}},
             {{"\xc5\xc5\xb4"},     {"\xb4\xb4\xb4"}},
             {{"\xc1\xc1\xc1"},     {"\xc5\xc5\xc1"}},
             {{"\xc2\xc2\xc2"},     {"\xc2\xc2\xc2"}}    }
};


/* -- compute whether character is first, middle, or last -- */
static int FindVector(WINDOW wnd, RECT rc, int x, int y)
{
    RECT rcc;
    VECT *vc = wnd->VectorList;
    int i, coll = -1;
    for (i = 0; i < wnd->VectorCount; i++)    {
        if ((vc+i)->vt == VECTOR)    {
            rcc = (vc+i)->rc;
            /* --- skip the colliding vector --- */
            if (rcc.lf == rc.lf && rcc.rt == rc.rt &&
                    rcc.tp == rc.tp && rc.bt == rcc.bt)
                continue;
            if (rcc.tp == rcc.bt)    {
                /* ---- horizontal vector,
                    see if character is in it --- */
                if (rc.lf+x >= rcc.lf && rc.lf+x <= rcc.rt &&
                        rc.tp+y == rcc.tp)    {
                    /* --- it is --- */
                    if (rc.lf+x == rcc.lf)
                        coll = 0;
                    else if (rc.lf+x == rcc.rt)
                        coll = 2;
                    else 
                        coll = 1;
                }
            }
            else     {
                /* ---- vertical vector,
                    see if character is in it --- */
                if (rc.tp+y >= rcc.tp && rc.tp+y <= rcc.bt &&
                        rc.lf+x == rcc.lf)    {
                    /* --- it is --- */
                    if (rc.tp+y == rcc.tp)
                        coll = 0;
                    else if (rc.tp+y == rcc.bt)
                        coll = 2;
                    else 
                        coll = 1;
                }
            }
        }
    }
    return coll;
}

static void PaintVector(WINDOW wnd, RECT rc)
{
	int i, xi, yi, len;
    unsigned int ch, nc;
    unsigned int newch;
    static int cw, fml, vertvect, coll;

#if !defined IBMPC
    SetCharInWndLocal();
#endif
    if (rc.rt == rc.lf)    {
        /* ------ vertical vector ------- */
        nc = '\xb3';
        vertvect = 1;
        len = rc.bt-rc.tp+1;
    }
    else     {
        /* ------ horizontal vector ------- */
        nc = '\xc4';
        vertvect = 0;
        len = rc.rt-rc.lf+1;
    }

    for (i = 0; i < len; i++)    {
        newch = nc;
        xi = yi = 0;
        if (vertvect)
            yi = i;
        else
            xi = i;
        ch = videochar(GetClientLeft(wnd)+rc.lf+xi,
                    GetClientTop(wnd)+rc.tp+yi);
#if !defined IBMPC
        ch = ConvCharInWndFromLocal(ch);
#endif
        for (cw = 0; cw < sizeof(CharInWnd); cw++)    {
            if (ch == CharInWnd[cw])    {
                /* ---- hit another vector character ---- */
                if ((coll=FindVector(wnd, rc, xi, yi)) != -1) {
                    /* compute first/middle/last subscript */
                    if (i == len-1)
                        fml = 2;
                    else if (i == 0)
                        fml = 0;
                    else
                        fml = 1;
                    newch = VectCvt[coll][cw][vertvect][fml];
                }
            }
        }
#if defined IBMPC
		PutWindowChar(wnd, newch, rc.lf+xi, rc.tp+yi);
#else
        PutWindowChar(wnd, ConvCharInWndToLocal(newch), rc.lf+xi, rc.tp+yi);
#endif
    }
}

static void PaintBar(WINDOW wnd, RECT rc, enum VectTypes vt)
{
    int i, vertbar, len;
#if defined IBMPC
    unsigned int tys[] = {219, 178, 177, 176};
/*    unsigned int tys[] = {'\xdb', '\xb2', '\xb1', '\xb0'};
*/
    unsigned int nc = tys[vt-1];
#else
    unsigned char nc = ' ';

    switch(vt) {
        case SOLIDBAR: nc = dfc_solidbar; break;
        case HEAVYBAR: nc = dfc_heavybar; break;
        case CROSSBAR: nc = dfc_crossbar; break;
        case LIGHTBAR: nc = dfc_lightbar; break;
        default:
            return;
    }
#endif

    if (rc.rt == rc.lf)    {
        /* ------ vertical bar ------- */
        vertbar = 1;
        len = rc.bt-rc.tp+1;
    }
    else     {
        /* ------ horizontal bar ------- */
        vertbar = 0;
        len = rc.rt-rc.lf+1;
    }

    for (i = 0; i < len; i++)    {
        int xi = 0, yi = 0;
        if (vertbar)
            yi = i;
        else
            xi = i;
        PutWindowChar(wnd, nc, rc.lf+xi, rc.tp+yi);
    }
}

static void PaintMsg(WINDOW wnd)
{
    int i;
    VECT *vc = wnd->VectorList;
    for (i = 0; i < wnd->VectorCount; i++)    {
        if (vc->vt == VECTOR)
            PaintVector(wnd, vc->rc);
        else
            PaintBar(wnd, vc->rc, vc->vt);
        vc++;
    }
}

static void DrawVectorMsg(WINDOW wnd,PARAM p1,enum VectTypes vt)
{
    if (p1)    {
        VECT vc;
        wnd->VectorList = DFrealloc(wnd->VectorList,
                sizeof(VECT) * (wnd->VectorCount + 1));
        vc.vt = vt;
        vc.rc = *(RECT *)p1;
        *(((VECT *)(wnd->VectorList))+wnd->VectorCount)=vc;
        wnd->VectorCount++;
    }
}

static void DrawBoxMsg(WINDOW wnd, PARAM p1)
{
    if (p1)    {
        RECT rc = *(RECT *)p1;
        rc.bt = rc.tp;
        SendMessage(wnd, DRAWVECTOR, (PARAM) &rc, TRUE);
        rc = *(RECT *)p1;
        rc.lf = rc.rt;
        SendMessage(wnd, DRAWVECTOR, (PARAM) &rc, FALSE);
        rc = *(RECT *)p1;
        rc.tp = rc.bt;
        SendMessage(wnd, DRAWVECTOR, (PARAM) &rc, TRUE);
        rc = *(RECT *)p1;
        rc.rt = rc.lf;
        SendMessage(wnd, DRAWVECTOR, (PARAM) &rc, FALSE);
    }
}

int PictureProc(WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2)
{
    switch (msg)    {
        case PAINT:
            BaseWndProc(PICTUREBOX, wnd, msg, p1, p2);
            PaintMsg(wnd);
            return TRUE;
        case DRAWVECTOR:
            DrawVectorMsg(wnd, p1, VECTOR);
            return TRUE;
        case DRAWBOX:
            DrawBoxMsg(wnd, p1);
            return TRUE;
        case DRAWBAR:
            DrawVectorMsg(wnd, p1, (enum VectTypes)p2);
            return TRUE;
        case CLOSE_WINDOW:
            if (wnd->VectorList != NULL)
                free(wnd->VectorList);
            break;
        default:
            break;
    }
    return BaseWndProc(PICTUREBOX, wnd, msg, p1, p2);
}

static RECT PictureRect(int x, int y, int len, int hv)
{
    RECT rc;
    rc.lf = rc.rt = x;
    rc.tp = rc.bt = y;
    if (hv)
        /* ---- horizontal vector ---- */
        rc.rt += len-1;
    else
        /* ---- vertical vector ---- */
        rc.bt += len-1;
    return rc;
}

void DrawVector(WINDOW wnd, int x, int y, int len, int hv)
{
    RECT rc = PictureRect(x,y,len,hv);
    SendMessage(wnd, DRAWVECTOR, (PARAM) &rc, 0);
}

void DrawBox(WINDOW wnd, int x, int y, int ht, int wd)
{
    RECT rc;
    rc.lf = x;
    rc.tp = y;
    rc.rt = x+wd-1;
    rc.bt = y+ht-1;
    SendMessage(wnd, DRAWBOX, (PARAM) &rc, 0);
}

void DrawBar(WINDOW wnd,enum VectTypes vt,
                        int x,int y,int len,int hv)
{
    RECT rc = PictureRect(x,y,len,hv);
    SendMessage(wnd, DRAWBAR, (PARAM) &rc, (PARAM) vt);
}
