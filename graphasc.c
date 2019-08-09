#include "graphchr.h"

#define SC(n,c) *(unsigned char *)&(n) = (c)

void set_graphchr_ascii(void)
{
    /* single line */
    SC(dfc_dr, '+');   /* down-right */
    SC(dfc_h, '-');   /* horizontal */
    SC(dfc_dh, '+');   /* down-horizontal */
    SC(dfc_dl, '+');   /* down-left */
    SC(dfc_v, '|');   /* vertical */
    SC(dfc_vr, '+');   /* vertical-right */
    SC(dfc_vh, '+');   /* vertical-horizontal */
    SC(dfc_vl, '+');   /* vertical-left */
    SC(dfc_ur, '+');   /* up-right */
    SC(dfc_uh, '+');   /* up-horizontal */
    SC(dfc_ul, '+');   /* up-left */

    /* double line */
    SC(dfc_dbl_dr, '+');   /* down-right */
    SC(dfc_dbl_h, '-');   /* horizontal */
    SC(dfc_dbl_dh, '+');   /* down-horizontal */
    SC(dfc_dbl_dl, '+');   /* down-left */
    SC(dfc_dbl_v, '|');   /* vertical */
    SC(dfc_dbl_vr, '+');   /* vertical-right */
    SC(dfc_dbl_vh, '+');   /* vertical-horizontal */
    SC(dfc_dbl_vl, '+');   /* vertical-left */
    SC(dfc_dbl_ur, '+');   /* up-right */
    SC(dfc_dbl_uh, '+');   /* up-horizontal */
    SC(dfc_dbl_ul, '+');   /* up-left */

    /* arrow chars */
    SC(dfc_uparrow, '^'); 
    SC(dfc_downarrow, 'v'); 
    SC(dfc_rightarrow, '>'); 
    SC(dfc_leftarrow, '<'); 
    SC(dfc_updownarrow, ':'); 
    
    /* triangle chars */
    SC(dfc_uptriangle, '^'); 
    SC(dfc_downtriangle, 'v'); 
    SC(dfc_righttriangle, '>'); 
    SC(dfc_lefttriangle, '<'); 

    /* block(bar) and shadow chars */
    SC(dfc_solidbar, '#');
    SC(dfc_heavybar, '*');
    SC(dfc_crossbar, '+');
    SC(dfc_lightbar, ':');
    SC(dfc_buttonshadow0, 'l');
    SC(dfc_buttonshadow1, '~');

    /* parts of window */
    SC(dfc_scrollbar, ':'); /* light shade */
    SC(dfc_scrollpos, 'O'); /* dark shade */
    SC(dfc_menuchecked, '*'); /* square root */
    SC(dfc_cascade, '>'); /* right-pointing pointer (triangle) */
    SC(dfc_appsbg, ' '); /* light shade */
    SC(dfc_sizetoken, '/'); /* diamond */
    SC(dfc_controlbox, '='); /* identical to */
    SC(dfc_max, 'O'); /* uparrow */
    SC(dfc_min, '_'); /* downarrow */
    SC(dfc_restore, 'o'); /* updownarrow */
    SC(dfc_listselector, '>'); /* diamond */
    SC(dfc_radiobutton, '*'); /* radio button */
    SC(dfc_tickhand0, '^');
    SC(dfc_tickhand1, '>');
    SC(dfc_tickhand2, 'v');
    SC(dfc_tickhand3, '<');

    /* special escape charcodes */
    SC(dfc_setcolor, '\x11');
    SC(dfc_resetcolor, '\x12');
    SC(dfc_ptab, '\x13');
    SC(dfc_stab, '\x14');
}

