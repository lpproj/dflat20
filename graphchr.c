#define BUILD_GRAPHCHR
#include "graphchr.h"


/* box characters */

/*

   DR H DH H DL  +--+--+
   V    V    V   |  |  |
   VR H VH H VL  +--+--+
   V    V    V   |  |  |
   UR H DH H UL  +--+--+

*/

/* single line */

DF_DECLARE_GRAPHCHR unsigned char dfc_dr = '\xda';   /* down-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_h  = '\xc4';   /* horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dh = '\xc2';   /* down-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dl = '\xbf';   /* down-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_v  = '\xb3';   /* vertical */
DF_DECLARE_GRAPHCHR unsigned char dfc_vr = '\xc3';   /* vertical-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_vh = '\xc5';   /* vertical-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_vl = '\xb4';   /* vertical-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_ur = '\xc0';   /* up-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_uh = '\xc1';   /* up-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_ul = '\xd9';   /* up-left */

/* double line */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dr = '\xc9';   /* down-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_h  = '\xcd';   /* horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dh = '\xcb';   /* down-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dl = '\xbb';   /* down-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_v  = '\xba';   /* vertical */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vr = '\xcc';   /* vertical-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vh = '\xce';   /* vertical-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vl = '\xb9';   /* vertical-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_ur = '\xc8';   /* up-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_uh = '\xca';   /* up-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_ul = '\xbc';   /* up-left */

/* arrow chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_uparrow = '\x18'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_downarrow = '\x19'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_rightarrow = '\x1a'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_leftarrow = '\x1b'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_updownarrow = '\x12'; 

/* triangle chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_uptriangle = '\x1e'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_downtriangle = '\x1f'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_righttriangle = '\x10'; 
DF_DECLARE_GRAPHCHR unsigned char dfc_lefttriangle = '\x11'; 

/* block(bar) and shadow chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_solidbar = '\xdb';   /* full block */
DF_DECLARE_GRAPHCHR unsigned char dfc_heavybar = '\xb2';     /* dark shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_crossbar = '\xb1';   /* medium shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_lightbar = '\xb0';    /* light shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_buttonshadow0 = '\xdc';   /* lower half block */
DF_DECLARE_GRAPHCHR unsigned char dfc_buttonshadow1 = '\xdf';   /* upper half block */

/* parts of window */

DF_DECLARE_GRAPHCHR unsigned char dfc_scrollbar = '\xb0'; /* light shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_scrollpos = '\xb2'; /* dark shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_menuchecked = '\xfb'; /* square root */
DF_DECLARE_GRAPHCHR unsigned char dfc_cascade = '\x10'; /* right-pointing pointer (triangle) */
DF_DECLARE_GRAPHCHR unsigned char dfc_appsbg = '\xb0'; /* light shade */
DF_DECLARE_GRAPHCHR unsigned char dfc_sizetoken = '\x4'; /* diamond */
DF_DECLARE_GRAPHCHR unsigned char dfc_controlbox = '\xf0'; /* identical to */
DF_DECLARE_GRAPHCHR unsigned char dfc_max = '\x18'; /* uparrow */
DF_DECLARE_GRAPHCHR unsigned char dfc_min = '\x19'; /* downarrow */
DF_DECLARE_GRAPHCHR unsigned char dfc_restore = '\x12'; /* updownarrow */
DF_DECLARE_GRAPHCHR unsigned char dfc_listselector = '\x4'; /* diamond */
DF_DECLARE_GRAPHCHR unsigned char dfc_radiobutton = '\x7'; /* radio button */
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand0 = '\xc0';
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand1 = '\xda';
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand2 = '\xbf';
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand3 = '\xd9';

/* special escape charcodes */
DF_DECLARE_GRAPHCHR unsigned char dfc_setcolor = '\xae';
DF_DECLARE_GRAPHCHR unsigned char dfc_resetcolor = '\xaf';
DF_DECLARE_GRAPHCHR unsigned char dfc_ptab = '\x89';
DF_DECLARE_GRAPHCHR unsigned char dfc_stab = '\x8c';

