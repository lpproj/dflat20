/* ----------- graphchr.h ---------- */
#ifndef GRAPHCHR_H
#define GRAPHCHR_H

#define GRAPHCHR_FORCE_STRICT 1

#ifdef GRAPHCHR_FORCE_STRICT
# define DF_DECLARE_CONST  const
#else
# define DF_DECLARE_CONST  
#endif

#ifdef BUILD_GRAPHCHR
# define DF_DECLARE_GRAPHCHR  DF_DECLARE_CONST
#else
# define DF_DECLARE_GRAPHCHR  extern DF_DECLARE_CONST
#endif


void set_graphchr_cp437(void);
void set_graphchr_cp932(void);
void set_graphchr_ascii(void);


/* box characters */

/*

   DR H DH H DL  +--+--+
   V    V    V   |  |  |
   VR H VH H VL  +--+--+
   V    V    V   |  |  |
   UR H DH H UL  +--+--+

*/

/* single line */

DF_DECLARE_GRAPHCHR unsigned char dfc_dr;   /* down-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_h;   /* horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dh;   /* down-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dl;   /* down-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_v;   /* vertical */
DF_DECLARE_GRAPHCHR unsigned char dfc_vr;   /* vertical-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_vh;   /* vertical-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_vl;   /* vertical-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_ur;   /* up-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_uh;   /* up-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_ul;   /* up-left */

/* double line */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dr;   /* down-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_h;   /* horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dh;   /* down-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_dl;   /* down-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_v;   /* vertical */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vr;   /* vertical-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vh;   /* vertical-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_vl;   /* vertical-left */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_ur;   /* up-right */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_uh;   /* up-horizontal */
DF_DECLARE_GRAPHCHR unsigned char dfc_dbl_ul;   /* up-left */

/* arrow chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_uparrow; 
DF_DECLARE_GRAPHCHR unsigned char dfc_downarrow;
DF_DECLARE_GRAPHCHR unsigned char dfc_rightarrow;
DF_DECLARE_GRAPHCHR unsigned char dfc_leftarrow;
DF_DECLARE_GRAPHCHR unsigned char dfc_updownarrow;

/* triangle chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_uptriangle;
DF_DECLARE_GRAPHCHR unsigned char dfc_downtriangle;
DF_DECLARE_GRAPHCHR unsigned char dfc_righttriangle;
DF_DECLARE_GRAPHCHR unsigned char dfc_lefttriangle;

/* block(bar) and shadow chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_solidbar;
DF_DECLARE_GRAPHCHR unsigned char dfc_heavybar;
DF_DECLARE_GRAPHCHR unsigned char dfc_crossbar;
DF_DECLARE_GRAPHCHR unsigned char dfc_lightbar;
DF_DECLARE_GRAPHCHR unsigned char dfc_buttonshadow0;
DF_DECLARE_GRAPHCHR unsigned char dfc_buttonshadow1;

/* parts of window */
DF_DECLARE_GRAPHCHR unsigned char dfc_scrollbar;
DF_DECLARE_GRAPHCHR unsigned char dfc_scrollpos;
DF_DECLARE_GRAPHCHR unsigned char dfc_menuchecked;
DF_DECLARE_GRAPHCHR unsigned char dfc_cascade;
DF_DECLARE_GRAPHCHR unsigned char dfc_appsbg;
DF_DECLARE_GRAPHCHR unsigned char dfc_sizetoken;
DF_DECLARE_GRAPHCHR unsigned char dfc_controlbox;
DF_DECLARE_GRAPHCHR unsigned char dfc_max;
DF_DECLARE_GRAPHCHR unsigned char dfc_min;
DF_DECLARE_GRAPHCHR unsigned char dfc_restore;
DF_DECLARE_GRAPHCHR unsigned char dfc_listselector;
DF_DECLARE_GRAPHCHR unsigned char dfc_radiobutton;
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand0;
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand1;
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand2;
DF_DECLARE_GRAPHCHR unsigned char dfc_tickhand3;

/* special escape chars */
DF_DECLARE_GRAPHCHR unsigned char dfc_setcolor;
DF_DECLARE_GRAPHCHR unsigned char dfc_resetcolor;
DF_DECLARE_GRAPHCHR unsigned char dfc_ptab;
DF_DECLARE_GRAPHCHR unsigned char dfc_stab;


#endif
