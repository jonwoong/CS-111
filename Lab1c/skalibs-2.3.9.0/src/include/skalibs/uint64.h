/* ISC license. */

#ifndef UINT64_H
#define UINT64_H

#include <stdint.h>

typedef uint64_t uint64 ;
#define uint64_little_endian(s, n)
#define uint64_big_endian(s, n) uint64_reverse((s), (n))

extern void uint64_pack (char *, uint64) ;
extern void uint64_pack_big (char *, uint64) ;
extern void uint64_unpack (char const *, uint64 *) ;
extern void uint64_unpack_big (char const *, uint64 *) ;
extern void uint64_reverse (char *, unsigned int) ;

#define UINT64_FMT 21
#define UINT64_OFMT 25
#define UINT64_XFMT 17
#define UINT64_BFMT 65

extern unsigned int uint64_fmt_base (char *, uint64, unsigned char) ;
extern unsigned int uint640_fmt_base (char *, uint64, unsigned int, unsigned char) ;

#define uint64_fmt(s, u) uint64_fmt_base(s, (u), 10)
#define uint640_fmt(s, u, n) uint640_fmt_base(s, u, (n), 10)
#define uint64_ofmt(s, u) uint64_fmt_base(s, (u), 8)
#define uint640_ofmt(s, u, n) uint640_fmt_base(s, u, (n), 8)
#define uint64_xfmt(s, u) uint64_fmt_base(s, (u), 16)
#define uint640_xfmt(s, u, n) uint640_fmt_base(s, u, (n), 16)
#define uint64_bfmt(s, u) uint64_fmt_base(s, (u), 2)
#define uint640_bfmt(s, u, n) uint640_fmt_base(s, u, (n), 2)

extern unsigned int uint64_fmtlist (char *, uint64 const *, unsigned int) ;

extern unsigned int uint64_scan_base (char const *, uint64 *, unsigned char) ;
extern unsigned int uint640_scan_base (char const *, uint64 *, unsigned char) ;
#define uint64_scan(s, u) uint64_scan_base(s, (u), 10)
#define uint640_scan(s, u) uint640_scan_base(s, (u), 10)
#define uint64_oscan(s, u) uint64_scan_base(s, (u), 8)
#define uint640_oscan(s, u) uint640_scan_base(s, (u), 8)
#define uint64_xscan(s, u) uint64_scan_base(s, (u), 16)
#define uint640_xscan(s, u) uint640_scan_base(s, (u), 16)
#define uint64_bscan(s, u) uint64_scan_base(s, (u), 2)
#define uint640_bscan(s, u) uint640_scan_base(s, (u), 2)

extern unsigned int uint64_scanlist (uint64 *, unsigned int, char const *, unsigned int *) ;

#endif
