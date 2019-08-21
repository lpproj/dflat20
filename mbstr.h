#ifndef MBSTR_H
#define MBSTR_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined DBCS
int mblen_loose(const void *);
int is_dbcslead(unsigned char);
char *  char_next(const char *);
char *  char_prev(const char *, const char *);
#else
# define mblen_loose(p)  (1)
# define is_dbcslead(c)  (0)
# define char_next(p)    ((char *)(p) + 1)
# define char_prev(b,p)    ((char *)(p) - 1)
#endif /* DBCS */

#ifdef __cplusplus
}
#endif


#if !defined WIN32 && !defined WIN64
# define CharNext  char_next
# define CharPrev  char_prev
# define IsDBCSLeadByte  is_dbcslead
#endif


#endif
