//========================================================================
//
// UnicodeMapTables.h
//
// Copyright 2001-2003 Glyph & Cog, LLC
//
//========================================================================

static UnicodeMapRange latin1UnicodeMapRanges[] = {
    { 0x000a, 0x000a, 0x0a, 1 },
    { 0x000c, 0x000d, 0x0c, 1 },
    { 0x0020, 0x007e, 0x20, 1 },
    { 0x00a0, 0x00a0, 0x20, 1 },
    { 0x00a1, 0x00ac, 0xa1, 1 },
    { 0x00ae, 0x00ff, 0xae, 1 },
    { 0x010c, 0x010c, 0x43, 1 },
    { 0x010d, 0x010d, 0x63, 1 },
    { 0x0131, 0x0131, 0x69, 1 },
    { 0x0141, 0x0141, 0x4c, 1 },
    { 0x0142, 0x0142, 0x6c, 1 },
    { 0x0152, 0x0152, 0x4f45, 2 },
    { 0x0153, 0x0153, 0x6f65, 2 },
    { 0x0160, 0x0160, 0x53, 1 },
    { 0x0161, 0x0161, 0x73, 1 },
    { 0x0178, 0x0178, 0x59, 1 },
    { 0x017d, 0x017d, 0x5a, 1 },
    { 0x017e, 0x017e, 0x7a, 1 },
    { 0x02c6, 0x02c6, 0x5e, 1 },
    { 0x02da, 0x02da, 0xb0, 1 },
    { 0x02dc, 0x02dc, 0x7e, 1 },
    { 0x2013, 0x2013, 0xad, 1 },
    { 0x2014, 0x2014, 0x2d2d, 2 },
    { 0x2018, 0x2018, 0x60, 1 },
    { 0x2019, 0x2019, 0x27, 1 },
    { 0x201a, 0x201a, 0x2c, 1 },
    { 0x201c, 0x201c, 0x22, 1 },
    { 0x201d, 0x201d, 0x22, 1 },
    { 0x201e, 0x201e, 0x2c2c, 2 },
    { 0x2022, 0x2022, 0xb7, 1 },
    { 0x2026, 0x2026, 0x2e2e2e, 3 },
    { 0x2039, 0x2039, 0x3c, 1 },
    { 0x203a, 0x203a, 0x3e, 1 },
    { 0x2044, 0x2044, 0x2f, 1 },
    { 0x2122, 0x2122, 0x544d, 2 },
    { 0x2212, 0x2212, 0x2d, 1 },
    { 0xf6f9, 0xf6f9, 0x4c, 1 },
    { 0xf6fa, 0xf6fa, 0x4f45, 2 },
    { 0xf6fc, 0xf6fc, 0xb0, 1 },
    { 0xf6fd, 0xf6fd, 0x53, 1 },
    { 0xf6fe, 0xf6fe, 0x7e, 1 },
    { 0xf6ff, 0xf6ff, 0x5a, 1 },
    { 0xf721, 0xf721, 0x21, 1 },
    { 0xf724, 0xf724, 0x24, 1 },
    { 0xf726, 0xf726, 0x26, 1 },
    { 0xf730, 0xf739, 0x30, 1 },
    { 0xf73f, 0xf73f, 0x3f, 1 },
    { 0xf761, 0xf77a, 0x41, 1 },
    { 0xf7a1, 0xf7a2, 0xa1, 1 },
    { 0xf7bf, 0xf7bf, 0xbf, 1 },
    { 0xf7e0, 0xf7f6, 0xc0, 1 },
    { 0xf7f8, 0xf7fe, 0xd8, 1 },
    { 0xf7ff, 0xf7ff, 0x59, 1 },
    { 0xfb00, 0xfb00, 0x6666, 2 },
    { 0xfb01, 0xfb01, 0x6669, 2 },
    { 0xfb02, 0xfb02, 0x666c, 2 },
    { 0xfb03, 0xfb03, 0x666669, 3 },
    { 0xfb04, 0xfb04, 0x66666c, 3 }
};
#define latin1UnicodeMapLen (sizeof(latin1UnicodeMapRanges) / sizeof(UnicodeMapRange))

static UnicodeMapRange ascii7UnicodeMapRanges[] = {
    { 0x000a, 0x000a, 0x0a, 1 },
    { 0x000c, 0x000d, 0x0c, 1 },
    { 0x0020, 0x005f, 0x20, 1 },
    { 0x0061, 0x007e, 0x61, 1 },
    { 0x00a6, 0x00a6, 0x7c, 1 },
    { 0x00a9, 0x00a9, 0x286329, 3 },
    { 0x00ae, 0x00ae, 0x285229, 3 },
    { 0x00b7, 0x00b7, 0x2a, 1 },
    { 0x00bc, 0x00bc, 0x312f34, 3 },
    { 0x00bd, 0x00bd, 0x312f32, 3 },
    { 0x00be, 0x00be, 0x332f34, 3 },
    { 0x00c0, 0x00c0, 0x41, 1 },
    { 0x00c1, 0x00c1, 0x41, 1 },
    { 0x00c2, 0x00c2, 0x41, 1 },
    { 0x00c3, 0x00c3, 0x41, 1 },
    { 0x00c4, 0x00c4, 0x41, 1 },
    { 0x00c5, 0x00c5, 0x41, 1 },
    { 0x00c6, 0x00c6, 0x4145, 2 },
    { 0x00c7, 0x00c7, 0x43, 1 },
    { 0x00c8, 0x00c8, 0x45, 1 },
    { 0x00c9, 0x00c9, 0x45, 1 },
    { 0x00ca, 0x00ca, 0x45, 1 },
    { 0x00cb, 0x00cb, 0x45, 1 },
    { 0x00cc, 0x00cc, 0x49, 1 },
    { 0x00cd, 0x00cd, 0x49, 1 },
    { 0x00ce, 0x00ce, 0x49, 1 },
    { 0x00cf, 0x00cf, 0x49, 1 },
    { 0x00d1, 0x00d2, 0x4e, 1 },
    { 0x00d3, 0x00d3, 0x4f, 1 },
    { 0x00d4, 0x00d4, 0x4f, 1 },
    { 0x00d5, 0x00d5, 0x4f, 1 },
    { 0x00d6, 0x00d6, 0x4f, 1 },
    { 0x00d7, 0x00d7, 0x78, 1 },
    { 0x00d8, 0x00d8, 0x4f, 1 },
    { 0x00d9, 0x00d9, 0x55, 1 },
    { 0x00da, 0x00da, 0x55, 1 },
    { 0x00db, 0x00db, 0x55, 1 },
    { 0x00dc, 0x00dc, 0x55, 1 },
    { 0x00dd, 0x00dd, 0x59, 1 },
    { 0x00e0, 0x00e0, 0x61, 1 },
    { 0x00e1, 0x00e1, 0x61, 1 },
    { 0x00e2, 0x00e2, 0x61, 1 },
    { 0x00e3, 0x00e3, 0x61, 1 },
    { 0x00e4, 0x00e4, 0x61, 1 },
    { 0x00e5, 0x00e5, 0x61, 1 },
    { 0x00e6, 0x00e6, 0x6165, 2 },
    { 0x00e7, 0x00e7, 0x63, 1 },
    { 0x00e8, 0x00e8, 0x65, 1 },
    { 0x00e9, 0x00e9, 0x65, 1 },
    { 0x00ea, 0x00ea, 0x65, 1 },
    { 0x00eb, 0x00eb, 0x65, 1 },
    { 0x00ec, 0x00ec, 0x69, 1 },
    { 0x00ed, 0x00ed, 0x69, 1 },
    { 0x00ee, 0x00ee, 0x69, 1 },
    { 0x00ef, 0x00ef, 0x69, 1 },
    { 0x00f1, 0x00f2, 0x6e, 1 },
    { 0x00f3, 0x00f3, 0x6f, 1 },
    { 0x00f4, 0x00f4, 0x6f, 1 },
    { 0x00f5, 0x00f5, 0x6f, 1 },
    { 0x00f6, 0x00f6, 0x6f, 1 },
    { 0x00f7, 0x00f7, 0x2f, 1 },
    { 0x00f8, 0x00f8, 0x6f, 1 },
    { 0x00f9, 0x00f9, 0x75, 1 },
    { 0x00fa, 0x00fa, 0x75, 1 },
    { 0x00fb, 0x00fb, 0x75, 1 },
    { 0x00fc, 0x00fc, 0x75, 1 },
    { 0x00fd, 0x00fd, 0x79, 1 },
    { 0x00ff, 0x00ff, 0x79, 1 },
    { 0x0131, 0x0131, 0x69, 1 },
    { 0x0141, 0x0141, 0x4c, 1 },
    { 0x0152, 0x0152, 0x4f45, 2 },
    { 0x0153, 0x0153, 0x6f65, 2 },
    { 0x0160, 0x0160, 0x53, 1 },
    { 0x0178, 0x0178, 0x59, 1 },
    { 0x017d, 0x017d, 0x5a, 1 },
    { 0x2013, 0x2013, 0x2d, 1 },
    { 0x2014, 0x2014, 0x2d2d, 2 },
    { 0x2018, 0x2018, 0x60, 1 },
    { 0x2019, 0x2019, 0x27, 1 },
    { 0x201c, 0x201c, 0x22, 1 },
    { 0x201d, 0x201d, 0x22, 1 },
    { 0x2022, 0x2022, 0x2a, 1 },
    { 0x2026, 0x2026, 0x2e2e2e, 3 },
    { 0x2122, 0x2122, 0x544d, 2 },
    { 0x2212, 0x2212, 0x2d, 1 },
    { 0xf6f9, 0xf6f9, 0x4c, 1 },
    { 0xf6fa, 0xf6fa, 0x4f45, 2 },
    { 0xf6fd, 0xf6fd, 0x53, 1 },
    { 0xf6fe, 0xf6fe, 0x7e, 1 },
    { 0xf6ff, 0xf6ff, 0x5a, 1 },
    { 0xf721, 0xf721, 0x21, 1 },
    { 0xf724, 0xf724, 0x24, 1 },
    { 0xf726, 0xf726, 0x26, 1 },
    { 0xf730, 0xf739, 0x30, 1 },
    { 0xf73f, 0xf73f, 0x3f, 1 },
    { 0xf761, 0xf77a, 0x41, 1 },
    { 0xf7e0, 0xf7e0, 0x41, 1 },
    { 0xf7e1, 0xf7e1, 0x41, 1 },
    { 0xf7e2, 0xf7e2, 0x41, 1 },
    { 0xf7e3, 0xf7e3, 0x41, 1 },
    { 0xf7e4, 0xf7e4, 0x41, 1 },
    { 0xf7e5, 0xf7e5, 0x41, 1 },
    { 0xf7e6, 0xf7e6, 0x4145, 2 },
    { 0xf7e7, 0xf7e7, 0x43, 1 },
    { 0xf7e8, 0xf7e8, 0x45, 1 },
    { 0xf7e9, 0xf7e9, 0x45, 1 },
    { 0xf7ea, 0xf7ea, 0x45, 1 },
    { 0xf7eb, 0xf7eb, 0x45, 1 },
    { 0xf7ec, 0xf7ec, 0x49, 1 },
    { 0xf7ed, 0xf7ed, 0x49, 1 },
    { 0xf7ee, 0xf7ee, 0x49, 1 },
    { 0xf7ef, 0xf7ef, 0x49, 1 },
    { 0xf7f1, 0xf7f2, 0x4e, 1 },
    { 0xf7f3, 0xf7f3, 0x4f, 1 },
    { 0xf7f4, 0xf7f4, 0x4f, 1 },
    { 0xf7f5, 0xf7f5, 0x4f, 1 },
    { 0xf7f6, 0xf7f6, 0x4f, 1 },
    { 0xf7f8, 0xf7f8, 0x4f, 1 },
    { 0xf7f9, 0xf7f9, 0x55, 1 },
    { 0xf7fa, 0xf7fa, 0x55, 1 },
    { 0xf7fb, 0xf7fb, 0x55, 1 },
    { 0xf7fc, 0xf7fc, 0x55, 1 },
    { 0xf7fd, 0xf7fd, 0x59, 1 },
    { 0xf7ff, 0xf7ff, 0x59, 1 },
    { 0xfb00, 0xfb00, 0x6666, 2 },
    { 0xfb01, 0xfb01, 0x6669, 2 },
    { 0xfb02, 0xfb02, 0x666c, 2 },
    { 0xfb03, 0xfb03, 0x666669, 3 },
    { 0xfb04, 0xfb04, 0x66666c, 3 }
};
#define ascii7UnicodeMapLen (sizeof(ascii7UnicodeMapRanges) / sizeof(UnicodeMapRange))

static UnicodeMapRange symbolUnicodeMapRanges[] = {
    { 0x0020, 0x0021, 0x20, 1 },
    { 0x0023, 0x0023, 0x23, 1 },
    { 0x0025, 0x0026, 0x25, 1 },
    { 0x0028, 0x0029, 0x28, 1 },
    { 0x002b, 0x002c, 0x2b, 1 },
    { 0x002e, 0x003f, 0x2e, 1 },
    { 0x005b, 0x005b, 0x5b, 1 },
    { 0x005d, 0x005d, 0x5d, 1 },
    { 0x005f, 0x005f, 0x5f, 1 },
    { 0x007b, 0x007d, 0x7b, 1 },
    { 0x00ac, 0x00ac, 0xd8, 1 },
    { 0x00b0, 0x00b1, 0xb0, 1 },
    { 0x00b5, 0x00b5, 0x6d, 1 },
    { 0x00d7, 0x00d7, 0xb4, 1 },
    { 0x00f7, 0x00f7, 0xb8, 1 },
    { 0x0192, 0x0192, 0xa6, 1 },
    { 0x0391, 0x0392, 0x41, 1 },
    { 0x0393, 0x0393, 0x47, 1 },
    { 0x0395, 0x0395, 0x45, 1 },
    { 0x0396, 0x0396, 0x5a, 1 },
    { 0x0397, 0x0397, 0x48, 1 },
    { 0x0398, 0x0398, 0x51, 1 },
    { 0x0399, 0x0399, 0x49, 1 },
    { 0x039a, 0x039d, 0x4b, 1 },
    { 0x039e, 0x039e, 0x58, 1 },
    { 0x039f, 0x03a0, 0x4f, 1 },
    { 0x03a1, 0x03a1, 0x52, 1 },
    { 0x03a3, 0x03a5, 0x53, 1 },
    { 0x03a6, 0x03a6, 0x46, 1 },
    { 0x03a7, 0x03a7, 0x43, 1 },
    { 0x03a8, 0x03a8, 0x59, 1 },
    { 0x03b1, 0x03b2, 0x61, 1 },
    { 0x03b3, 0x03b3, 0x67, 1 },
    { 0x03b4, 0x03b5, 0x64, 1 },
    { 0x03b6, 0x03b6, 0x7a, 1 },
    { 0x03b7, 0x03b7, 0x68, 1 },
    { 0x03b8, 0x03b8, 0x71, 1 },
    { 0x03b9, 0x03b9, 0x69, 1 },
    { 0x03ba, 0x03bb, 0x6b, 1 },
    { 0x03bd, 0x03bd, 0x6e, 1 },
    { 0x03be, 0x03be, 0x78, 1 },
    { 0x03bf, 0x03c0, 0x6f, 1 },
    { 0x03c1, 0x03c1, 0x72, 1 },
    { 0x03c2, 0x03c2, 0x56, 1 },
    { 0x03c3, 0x03c5, 0x73, 1 },
    { 0x03c6, 0x03c6, 0x66, 1 },
    { 0x03c7, 0x03c7, 0x63, 1 },
    { 0x03c8, 0x03c8, 0x79, 1 },
    { 0x03c9, 0x03c9, 0x77, 1 },
    { 0x03d1, 0x03d1, 0x4a, 1 },
    { 0x03d2, 0x03d2, 0xa1, 1 },
    { 0x03d5, 0x03d5, 0x6a, 1 },
    { 0x03d6, 0x03d6, 0x76, 1 },
    { 0x2022, 0x2022, 0xb7, 1 },
    { 0x2026, 0x2026, 0xbc, 1 },
    { 0x2032, 0x2032, 0xa2, 1 },
    { 0x2033, 0x2033, 0xb2, 1 },
    { 0x2044, 0x2044, 0xa4, 1 },
    { 0x2111, 0x2111, 0xc1, 1 },
    { 0x2118, 0x2118, 0xc3, 1 },
    { 0x211c, 0x211c, 0xc2, 1 },
    { 0x2126, 0x2126, 0x57, 1 },
    { 0x2135, 0x2135, 0xc0, 1 },
    { 0x2190, 0x2193, 0xac, 1 },
    { 0x2194, 0x2194, 0xab, 1 },
    { 0x21b5, 0x21b5, 0xbf, 1 },
    { 0x21d0, 0x21d3, 0xdc, 1 },
    { 0x21d4, 0x21d4, 0xdb, 1 },
    { 0x2200, 0x2200, 0x22, 1 },
    { 0x2202, 0x2202, 0xb6, 1 },
    { 0x2203, 0x2203, 0x24, 1 },
    { 0x2205, 0x2205, 0xc6, 1 },
    { 0x2206, 0x2206, 0x44, 1 },
    { 0x2207, 0x2207, 0xd1, 1 },
    { 0x2208, 0x2209, 0xce, 1 },
    { 0x220b, 0x220b, 0x27, 1 },
    { 0x220f, 0x220f, 0xd5, 1 },
    { 0x2211, 0x2211, 0xe5, 1 },
    { 0x2212, 0x2212, 0x2d, 1 },
    { 0x2217, 0x2217, 0x2a, 1 },
    { 0x221a, 0x221a, 0xd6, 1 },
    { 0x221d, 0x221d, 0xb5, 1 },
    { 0x221e, 0x221e, 0xa5, 1 },
    { 0x2220, 0x2220, 0xd0, 1 },
    { 0x2227, 0x2228, 0xd9, 1 },
    { 0x2229, 0x222a, 0xc7, 1 },
    { 0x222b, 0x222b, 0xf2, 1 },
    { 0x2234, 0x2234, 0x5c, 1 },
    { 0x223c, 0x223c, 0x7e, 1 },
    { 0x2245, 0x2245, 0x40, 1 },
    { 0x2248, 0x2248, 0xbb, 1 },
    { 0x2260, 0x2261, 0xb9, 1 },
    { 0x2264, 0x2264, 0xa3, 1 },
    { 0x2265, 0x2265, 0xb3, 1 },
    { 0x2282, 0x2282, 0xcc, 1 },
    { 0x2283, 0x2283, 0xc9, 1 },
    { 0x2284, 0x2284, 0xcb, 1 },
    { 0x2286, 0x2286, 0xcd, 1 },
    { 0x2287, 0x2287, 0xca, 1 },
    { 0x2295, 0x2295, 0xc5, 1 },
    { 0x2297, 0x2297, 0xc4, 1 },
    { 0x22a5, 0x22a5, 0x5e, 1 },
    { 0x22c5, 0x22c5, 0xd7, 1 },
    { 0x2320, 0x2320, 0xf3, 1 },
    { 0x2321, 0x2321, 0xf5, 1 },
    { 0x2329, 0x2329, 0xe1, 1 },
    { 0x232a, 0x232a, 0xf1, 1 },
    { 0x25ca, 0x25ca, 0xe0, 1 },
    { 0x2660, 0x2660, 0xaa, 1 },
    { 0x2663, 0x2663, 0xa7, 1 },
    { 0x2665, 0x2665, 0xa9, 1 },
    { 0x2666, 0x2666, 0xa8, 1 },
    { 0xf6d9, 0xf6d9, 0xd3, 1 },
    { 0xf6da, 0xf6da, 0xd2, 1 },
    { 0xf6db, 0xf6db, 0xd4, 1 },
    { 0xf8e5, 0xf8e5, 0x60, 1 },
    { 0xf8e6, 0xf8e7, 0xbd, 1 },
    { 0xf8e8, 0xf8ea, 0xe2, 1 },
    { 0xf8eb, 0xf8f4, 0xe6, 1 },
    { 0xf8f5, 0xf8f5, 0xf4, 1 },
    { 0xf8f6, 0xf8fe, 0xf6, 1 }
};
#define symbolUnicodeMapLen (sizeof(symbolUnicodeMapRanges) / sizeof(UnicodeMapRange))

static UnicodeMapRange zapfDingbatsUnicodeMapRanges[] = {
    { 0x0020, 0x0020, 0x20, 1 },
    { 0x2192, 0x2192, 0xd5, 1 },
    { 0x2194, 0x2195, 0xd6, 1 },
    { 0x2460, 0x2469, 0xac, 1 },
    { 0x25a0, 0x25a0, 0x6e, 1 },
    { 0x25b2, 0x25b2, 0x73, 1 },
    { 0x25bc, 0x25bc, 0x74, 1 },
    { 0x25c6, 0x25c6, 0x75, 1 },
    { 0x25cf, 0x25cf, 0x6c, 1 },
    { 0x25d7, 0x25d7, 0x77, 1 },
    { 0x2605, 0x2605, 0x48, 1 },
    { 0x260e, 0x260e, 0x25, 1 },
    { 0x261b, 0x261b, 0x2a, 1 },
    { 0x261e, 0x261e, 0x2b, 1 },
    { 0x2660, 0x2660, 0xab, 1 },
    { 0x2663, 0x2663, 0xa8, 1 },
    { 0x2665, 0x2665, 0xaa, 1 },
    { 0x2666, 0x2666, 0xa9, 1 },
    { 0x2701, 0x2704, 0x21, 1 },
    { 0x2706, 0x2709, 0x26, 1 },
    { 0x270c, 0x2727, 0x2c, 1 },
    { 0x2729, 0x274b, 0x49, 1 },
    { 0x274d, 0x274d, 0x6d, 1 },
    { 0x274f, 0x2752, 0x6f, 1 },
    { 0x2756, 0x2756, 0x76, 1 },
    { 0x2758, 0x275e, 0x78, 1 },
    { 0x2761, 0x2767, 0xa1, 1 },
    { 0x2776, 0x2794, 0xb6, 1 },
    { 0x2798, 0x27af, 0xd8, 1 },
    { 0x27b1, 0x27be, 0xf1, 1 }
};
#define zapfDingbatsUnicodeMapLen (sizeof(zapfDingbatsUnicodeMapRanges) / sizeof(UnicodeMapRange))
