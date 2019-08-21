#include <limits.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbstr.h"

static char mbstr_prepared = 0;
static const unsigned char far *dbcslead;

#define setuplead() if (!mbstr_prepared) getdbcslead(); else;

static const unsigned char dbcslead437[] = { 0, 0 };
static const unsigned char dbcslead932[] = { 0x81, 0x9f, 0xe0, 0xfc, 0, 0 };

static void getdbcslead(void)
{
    union REGS r;
    struct SREGS sr;

    r.x.si = sr.ds = 0;
    r.x.ax = 0x6300;
    intdosx(&r, &r, &sr);
    if (r.x.si && sr.ds) {
        unsigned char far *p = MK_FP(sr.ds, r.x.si);
        if (p[0] > 0 && p[1] == 0) p += 2;  /* workaround for buggy api on some DOS-clone */
        dbcslead = p;
    }
    else {
        dbcslead = &dbcslead437;
    }
    mbstr_prepared = !0;
}


int  is_dbcslead(unsigned char c)
{
    const unsigned char far *d = dbcslead;

    setuplead();
    while(1) {
        if (d[1] == 0) break;
        if (d[0] <= c && c <= d[1]) return 1;
        d += 2;
    }
    return 0;
}


int  mblen_loose(const void *p)
{
    const unsigned char *s = p;
    int n = is_dbcslead(*s);
    if (n > 0 && s[1] < 0x20) n = 0;
    return n + 1;
}

char *  char_next(const char *str_current)
{
    return (char *)(str_current + mblen_loose(str_current));
}

char *  char_prev(const char *str_base, const char *str_current)
{
    const char *s = str_base;

    while(str_base < str_current) {
        s = str_base;
        str_base += mblen_loose(s);
    }
    return (char *)s;
}


