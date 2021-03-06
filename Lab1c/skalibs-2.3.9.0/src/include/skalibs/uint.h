/* ISC license. */

#ifndef UINT_H
#define UINT_H

#include <skalibs/uint32.h>

#define UINT_PACK 4
#define uint_pack uint32_pack
#define uint_pack_big uint32_pack_big
#define uint_unpack(s, u) uint32_unpack(s, (uint32 *)(char *)(u))
#define uint_unpack_big(s, u) uint32_unpack_big(s, (uint32 *)(char *)(u))

#define uint_reverse uint32_reverse
#define uint_big_endian uint32_big_endian
#define uint_little_endian uint32_little_endian

#define UINT_FMT UINT32_FMT
#define UINT_OFMT UINT32_OFMT
#define UINT_XFMT UINT32_XFMT
#define UINT_BFMT UINT32_BFMT

#define uint_fmt_base uint32_fmt_base
#define uint0_fmt_base uint320_fmt_base
#define uint_fmt uint32_fmt
#define uint0_fmt uint320_fmt
#define uint_ofmt uint32_ofmt
#define uint0_ofmt uint320_ofmt
#define uint_xfmt uint32_xfmt
#define uint0_xfmt uint320_xfmt
#define uint_bfmt uint32_bfmt
#define uint0_bfmt uint320_bfmt

#define uint_fmtlist(s, tab, n) uint32_fmtlist(s, tab, n)

#define uint_scan_base(s, u, b) uint32_scan_base(s, (uint32 *)(char *)(u), b)
#define uint0_scan_base(s, u, b) uint320_scan_base(s, (uint32 *)(char *)(u), b)

#define uint_scanlist(tab, max, s, num) uint32_scanlist(tab, max, s, num)
#define uint_scan(s, u) uint_scan_base(s, (u), 10)
#define uint0_scan(s, u) uint0_scan_base(s, (u), 10)
#define uint_oscan(s, u) uint_scan_base(s, (u), 8)
#define uint0_oscan(s, u) uint0_scan_base(s, (u), 8)
#define uint_xscan(s, u) uint_scan_base(s, (u), 16)
#define uint0_xscan(s, u) uint0_scan_base(s, (u), 16)
#define uint_bscan(s, u) uint_scan_base(s, (u), 2)
#define uint0_bscan(s, u) uint0_scan_base(s, (u), 2)

#endif
