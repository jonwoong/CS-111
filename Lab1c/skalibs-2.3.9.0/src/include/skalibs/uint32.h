/* ISC license. */

#ifndef UINT32_H
#define UINT32_H

#include <stdint.h>
#include <skalibs/uint64.h>

typedef uint32_t uint32 ;
#define uint32_little_endian(s, n)
#define uint32_big_endian(s, n) uint32_reverse((s), (n))

extern void uint32_pack (char *, uint32) ;
extern void uint32_pack_big (char *, uint32) ;
extern void uint32_unpack (char const *, uint32 *) ;
extern void uint32_unpack_big (char const *, uint32 *) ;
extern void uint32_reverse (char *, unsigned int) ;

#define UINT32_FMT 11
#define UINT32_OFMT 13
#define UINT32_XFMT 9
#define UINT32_BFMT 33

#define uint32_fmt_base(s, u, b) uint64_fmt_base(s, (uint64)(uint32)(u), b)
#define uint320_fmt_base(s, u, n, b) uint640_fmt_base(s, (uint64)(uint32)(u), n, b)

#define uint32_fmt(s, u) uint64_fmt(s, (uint64)(uint32)(u))
#define uint320_fmt(s, u, n) uint640_fmt(s, (uint64)(uint32)(u), n)
#define uint32_ofmt(s, o) uint64_ofmt(s, (uint64)(uint32)(o))
#define uint320_ofmt(s, o, n) uint640_ofmt(s, (uint64)(uint32)(o), n)
#define uint32_xfmt(s, x) uint64_xfmt(s, (uint64)(uint32)(x))
#define uint320_xfmt(s, x, n) uint640_xfmt(s, (uint64)(uint32)(x), n)
#define uint32_bfmt(s, b) uint64_bfmt(s, (uint64)(uint32)(b))
#define uint320_bfmt(s, b, n) uint640_bfmt(s, (uint64)(uint32)(b), n)

extern unsigned int uint32_fmtlist (char *, uint32 const *, unsigned int) ;

extern unsigned int uint32_scan_base (char const *, uint32 *, unsigned char) ;
extern unsigned int uint320_scan_base (char const *, uint32 *, unsigned char) ;
#define uint32_scan(s, u) uint32_scan_base(s, (u), 10)
#define uint320_scan(s, u) uint320_scan_base(s, (u), 10)
#define uint32_oscan(s, u) uint32_scan_base(s, (u), 8)
#define uint320_oscan(s, u) uint320_scan_base(s, (u), 8)
#define uint32_xscan(s, u) uint32_scan_base(s, (u), 16)
#define uint320_xscan(s, u) uint320_scan_base(s, (u), 16)
#define uint32_bscan(s, u) uint32_scan_base(s, (u), 2)
#define uint320_bscan(s, u) uint320_scan_base(s, (u), 2)

extern unsigned int uint32_scanlist (uint32 *, unsigned int, char const *, unsigned int *) ;

#endif
