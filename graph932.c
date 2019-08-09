#include "graphchr.h"

#define SC(n,c) *(unsigned char *)&(n) = (c)

void set_graphchr_cp932(void)
{
    /* single line */
    SC(dfc_dr, '\x1');   /* down-right */
    SC(dfc_h, '\x6');   /* horizontal */
    SC(dfc_dh, '\x16');   /* down-horizontal */
    SC(dfc_dl, '\x2');   /* down-left */
    SC(dfc_v, '\x5');   /* vertical */
    SC(dfc_vr, '\x19');   /* vertical-right */
    SC(dfc_vh, '\x10');   /* vertical-horizontal */
    SC(dfc_vl, '\x17');   /* vertical-left */
    SC(dfc_ur, '\x3');   /* up-right */
    SC(dfc_uh, '\x15');   /* up-horizontal */
    SC(dfc_ul, '\x4');   /* up-left */

    /* double line */
    SC(dfc_dbl_dr, '\x1');   /* down-right */
    SC(dfc_dbl_h, '\x6');   /* horizontal */
    SC(dfc_dbl_dh, '\x16');   /* down-horizontal */
    SC(dfc_dbl_dl, '\x2');   /* down-left */
    SC(dfc_dbl_v, '\x5');   /* vertical */
    SC(dfc_dbl_vr, '\x19');   /* vertical-right */
    SC(dfc_dbl_vh, '\x10');   /* vertical-horizontal */
    SC(dfc_dbl_vl, '\x17');   /* vertical-left */
    SC(dfc_dbl_ur, '\x3');   /* up-right */
    SC(dfc_dbl_uh, '\x15');   /* up-horizontal */
    SC(dfc_dbl_ul, '\x4');   /* up-left */

    /* arrow chars */
    SC(dfc_uparrow, '\x1c');
    SC(dfc_downarrow, '\x7');
    SC(dfc_rightarrow, '\x1e');
    SC(dfc_leftarrow, '\x1f');
    SC(dfc_updownarrow, '\x12');
    
    /* triangle chars */
    SC(dfc_uptriangle, '\x1c');
    SC(dfc_downtriangle, '\x7');
    SC(dfc_righttriangle, '\x1e');
    SC(dfc_lefttriangle, '\x1f');

    /* block(bar) and shadow chars */
    SC(dfc_solidbar, '\x14');
    SC(dfc_heavybar, '\x1a');
    SC(dfc_crossbar, '\xb');
    SC(dfc_lightbar, '\xe');
    SC(dfc_buttonshadow0, '\x1a');
    SC(dfc_buttonshadow1, '~');

    /* parts of window */
    SC(dfc_scrollbar, '\x1a'); /* light shade */
    SC(dfc_scrollpos, '\x14'); /* dark shade */
    SC(dfc_menuchecked, '*'); /* square root */
    SC(dfc_cascade, '\x1e'); /* right-pointing pointer (triangle) */
    SC(dfc_appsbg, ' '); /* light shade */
    SC(dfc_sizetoken, '/'); /* diamond */
    SC(dfc_controlbox, '='); /* identical to */
    SC(dfc_max, '\x1c'); /* uparrow */
    SC(dfc_min, '\x7'); /* downarrow */
    SC(dfc_restore, '\x1b'); /* updownarrow */
    SC(dfc_listselector, '\x1e'); /* diamond */
    SC(dfc_radiobutton, '\xe'); /* bullet */
    SC(dfc_tickhand0, '\x1c');
    SC(dfc_tickhand1, '\x1e');
    SC(dfc_tickhand2, '\x7');
    SC(dfc_tickhand3, '\x1f');

    /* special escape charcodes */
    SC(dfc_setcolor, '\xc');
    SC(dfc_resetcolor, '\x11');
    SC(dfc_ptab, '\x13');
    SC(dfc_stab, '\x18');
}

