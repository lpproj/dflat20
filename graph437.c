#include "graphchr.h"

#define SC(n,c) *(unsigned char *)&(n) = (c)

void set_graphchr_cp437(void)
{
    /* single line */
    SC(dfc_dr, '\xda');   /* down-right */
    SC(dfc_h, '\xc4');   /* horizontal */
    SC(dfc_dh, '\xc2');   /* down-horizontal */
    SC(dfc_dl, '\xbf');   /* down-left */
    SC(dfc_v, '\xb3');   /* vertical */
    SC(dfc_vr, '\xc3');   /* vertical-right */
    SC(dfc_vh, '\xc5');   /* vertical-horizontal */
    SC(dfc_vl, '\xb4');   /* vertical-left */
    SC(dfc_ur, '\xc0');   /* up-right */
    SC(dfc_uh, '\xc1');   /* up-horizontal */
    SC(dfc_ul, '\xd9');   /* up-left */

    /* double line */
    SC(dfc_dbl_dr, '\xc9');   /* down-right */
    SC(dfc_dbl_h, '\xcd');   /* horizontal */
    SC(dfc_dbl_dh, '\xcb');   /* down-horizontal */
    SC(dfc_dbl_dl, '\xbb');   /* down-left */
    SC(dfc_dbl_v, '\xba');   /* vertical */
    SC(dfc_dbl_vr, '\xcc');   /* vertical-right */
    SC(dfc_dbl_vh, '\xce');   /* vertical-horizontal */
    SC(dfc_dbl_vl, '\xb9');   /* vertical-left */
    SC(dfc_dbl_ur, '\xc8');   /* up-right */
    SC(dfc_dbl_uh, '\xca');   /* up-horizontal */
    SC(dfc_dbl_ul, '\xbc');   /* up-left */

    /* arrow chars */
    SC(dfc_uparrow, '\x18'); 
    SC(dfc_downarrow, '\x19'); 
    SC(dfc_rightarrow, '\x1a'); 
    SC(dfc_leftarrow, '\x1b'); 
    SC(dfc_updownarrow, '\x12'); 
    
    /* triangle chars */
    SC(dfc_uptriangle, '\x1e'); 
    SC(dfc_downtriangle, '\x1f'); 
    SC(dfc_righttriangle, '\x10'); 
    SC(dfc_lefttriangle, '\x11'); 

    /* block(bar) and shadow chars */
    SC(dfc_solidbar, '\xdb');
    SC(dfc_heavybar, '\xb2');
    SC(dfc_crossbar, '\xb1');
    SC(dfc_lightbar, '\xb0');
    SC(dfc_buttonshadow0, '\xdc');
    SC(dfc_buttonshadow1, '\xdf');

    /* parts of window */
    SC(dfc_scrollbar, '\xb0'); /* light shade */
    SC(dfc_scrollpos, '\xb2'); /* dark shade */
    SC(dfc_menuchecked, '\xfb'); /* square root */
    SC(dfc_cascade, '\x10'); /* right-pointing pointer (triangle) */
    SC(dfc_appsbg, '\xb0'); /* light shade */
    SC(dfc_sizetoken, '\x4'); /* diamond */
    SC(dfc_controlbox, '\xf0'); /* identical to */
    SC(dfc_max, '\x18'); /* uparrow */
    SC(dfc_min, '\x19'); /* downarrow */
    SC(dfc_restore, '\x12'); /* updownarrow */
    SC(dfc_listselector, '\x4'); /* diamond */
    SC(dfc_radiobutton, '\x7'); /* bullet */
    SC(dfc_tickhand0, '\xc0');
    SC(dfc_tickhand1, '\xda');
    SC(dfc_tickhand2, '\xbf');
    SC(dfc_tickhand3, '\xd9');

    /* special escape charcodes */
    SC(dfc_setcolor, '\xae');
    SC(dfc_resetcolor, '\xaf');
    SC(dfc_ptab, '\x89');
    SC(dfc_stab, '\x8c');
}

