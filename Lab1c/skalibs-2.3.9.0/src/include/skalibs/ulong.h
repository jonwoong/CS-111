/* ISC license. */

#ifndef ULONG_H
#define ULONG_H

#include <skalibs/uint64.h>

#define ULONG_PACK 8
#define ulong_pack uint64_pack
#define ulong_pack_big uint64_pack_big
#define ulong_unpack(s, u) uint64_unpack(s, (uint64 *)(char *)(u))
#define ulong_unpack_big(s, u) uint64_unpack_big(s, (uint64 *)(char *)(u))

#define ulong_reverse uint64_reverse
#define ulong_big_endian uint64_big_endian
#define ulong_little_endian uint64_little_endian

#define ULONG_FMT UINT64_FMT
#define ULONG_OFMT UINT64_OFMT
#define ULONG_XFMT UINT64_XFMT
#define ULONG_BFMT UINT64_BFMT

#define ulong_fmt uint64_fmt
#define ulong0_fmt uint640_fmt
#define ulong_ofmt uint64_ofmt
#define ulong0_ofmt uint640_ofmt
#define ulong_xfmt uint64_xfmt
#define ulong0_xfmt uint640_xfmt
#define ulong_bfmt uint64_bfmt
#define ulong0_bfmt uint640_bfmt

#define ulong_fmtlist(s, tab, n) uint64_fmtlist(s, tab, n)

#define ulong_scan_base(s, u, b) uint64_scan_base(s, (uint64 *)(char *)(u), b)
#define ulong0_scan_base(s, u, b) uint640_scan_base(s, (uint64 *)(char *)(u), b)

#define ulong_scanlist(tab, max, s, num) uint64_scanlist(tab, max, s, num)
#define ulong_scan(s, u) ulong_scan_base(s, (u), 10)
#define ulong0_scan(s, u) ulong0_scan_base(s, (u), 10)
#define ulong_oscan(s, u) ulong_scan_base(s, (u), 8)
#define ulong0_oscan(s, u) ulong0_scan_base(s, (u), 8)
#define ulong_xscan(s, u) ulong_scan_base(s, (u), 16)
#define ulong0_xscan(s, u) ulong0_scan_base(s, (u), 16)
#define ulong_bscan(s, u) ulong_scan_base(s, (u), 2)
#define ulong0_bscan(s, u) ulong0_scan_base(s, (u), 2)

#endif
