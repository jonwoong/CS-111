/* ISC license. */

#ifndef EXECLINE_H
#define EXECLINE_H

#include <sys/types.h>
#include <skalibs/gccattributes.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>

#define EXECLINE_BLOCK_QUOTE_STRING " "
#define EXECLINE_BLOCK_QUOTE_CHAR ' '
#define EXECLINE_BLOCK_END_STRING ""
#define EXECLINE_BLOCK_END_CHAR '\0'


/* Parsing */

typedef int el_chargen_func_t (unsigned char *, void *) ;
typedef el_chargen_func_t *el_chargen_func_t_ref ;

extern int el_parse (stralloc *, el_chargen_func_t_ref, void *) ;
extern int el_parse_from_string (stralloc *, char const *) ;
extern int el_parse_from_buffer (stralloc *, buffer *) ;


/* Basics */

extern int el_vardupl (char const *, char const *, unsigned int) gccattr_pure ;
extern unsigned int el_getstrict (void) gccattr_const ;


/* Environment shifting */

extern int el_pushenv (stralloc *, char const *const *, unsigned int, char const *const *, unsigned int) ;
extern int el_popenv  (stralloc *, char const *const *, unsigned int, char const *const *, unsigned int) ;


/* Sequence */

extern pid_t el_spawn0 (char const *, char const *const *, char const *const *) ;
extern pid_t el_spawn1 (char const *, char const *const *, char const *const *, int *, int) ;
extern void el_execsequence (char const *const *, char const *const *, char const *const *) gccattr_noreturn ;


/* Block unquoting */

extern int el_semicolon (char const **) ;


/* Value transformation */

typedef struct eltransforminfo_s eltransforminfo_t, *eltransforminfo_t_ref ;
struct eltransforminfo_s
{
  char const *delim ;
  unsigned int crunch : 1 ;
  unsigned int chomp : 1 ;
  unsigned int split : 1 ;
} ;

#define ELTRANSFORMINFO_ZERO { .delim = " \n\r\t", .crunch = 0, .chomp = 0, .split = 0 }

extern int el_transform (stralloc *, unsigned int, eltransforminfo_t const *) ;


/* Substitution */

typedef struct elsubst_s elsubst_t, *elsubst_t_ref ;
struct elsubst_s
{
  unsigned int var ;
  unsigned int value ;
  unsigned int n ;
} ;

extern int el_substitute (stralloc *, char const *, unsigned int, char const *, char const *, elsubst_t const *, unsigned int) ;

#endif