#include "lvgl.h"

/*******************************************************************************
 * Size: 72 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifndef DIN1451_M_COND_72
#define DIN1451_M_COND_72 1
#endif

#if DIN1451_M_COND_72

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */

    /* U+30 "0" */
    0x0, 0xf2, 0x46, 0x77, 0xf6, 0xd3, 0x0, 0x7f,
    0x8f, 0x2d, 0xcc, 0x40, 0x49, 0x67, 0x9c, 0x3,
    0xe6, 0xc3, 0x0, 0xfe, 0x18, 0xc1, 0x0, 0xcb,
    0x20, 0x1f, 0xfc, 0x13, 0xa0, 0x8, 0x68, 0x3,
    0xff, 0x86, 0x8e, 0x0, 0x90, 0xf, 0x14, 0x5d,
    0x28, 0x7, 0xa4, 0x0, 0xc0, 0x1c, 0xba, 0xe8,
    0xb5, 0x60, 0x1c, 0x2a, 0x62, 0x1, 0x8a, 0x80,
    0x39, 0x1c, 0x3, 0xb1, 0x40, 0x39, 0x40, 0x3e,
    0x90, 0xe, 0x41, 0x0, 0xed, 0x0, 0xf8, 0x44,
    0x1, 0x8f, 0xc0, 0x38, 0x40, 0x3f, 0x18, 0x6,
    0x10, 0xf, 0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3,
    0xff, 0xfe, 0x1, 0xff, 0xff, 0x0, 0xff, 0xff,
    0x80, 0x7f, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0x1f,
    0xff, 0xf0, 0xf, 0xff, 0x9, 0x80, 0x61, 0xe0,
    0xe, 0x20, 0xf, 0xc2, 0x1, 0x8c, 0xc0, 0x1d,
    0x80, 0x1f, 0x20, 0x7, 0x32, 0x0, 0x72, 0x98,
    0x7, 0xa0, 0x3, 0xb0, 0x4c, 0x3, 0xb5, 0x40,
    0x22, 0xb3, 0x0, 0xe4, 0x8, 0x0, 0xe1, 0xae,
    0xcd, 0xd2, 0x0, 0x72, 0x18, 0x22, 0x0, 0x3c,
    0x26, 0x40, 0x1f, 0x48, 0x5, 0x44, 0x1, 0xff,
    0xc2, 0xa2, 0x0, 0x87, 0x10, 0x3, 0xfe, 0x1b,
    0x50, 0xe, 0x1b, 0xb1, 0x80, 0x7c, 0x31, 0xe8,
    0x1, 0xf9, 0x33, 0xae, 0x62, 0x15, 0xbc, 0xe2,
    0x1, 0x80,

    /* U+31 "1" */
    0x0, 0xf9, 0x7f, 0xfc, 0x40, 0x1e, 0x8a, 0x0,
    0xff, 0xe0, 0x53, 0x80, 0x7f, 0xc3, 0xaa, 0x1,
    0xff, 0x1f, 0x90, 0x7, 0xfc, 0xd8, 0x20, 0x1f,
    0xf1, 0x48, 0x7, 0xff, 0x22, 0x10, 0x3, 0xff,
    0x81, 0x6e, 0x1, 0xff, 0x16, 0xa0, 0x7, 0xfc,
    0x9a, 0x40, 0x1f, 0xf3, 0xd8, 0x7, 0xff, 0x2,
    0xa0, 0x3, 0xff, 0x80, 0x4a, 0x1, 0xff, 0xff,
    0x0, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0x3f,
    0xff, 0xe0, 0x1f, 0xff, 0xf0, 0xf, 0xff, 0xf8,
    0x7, 0xff, 0xfc, 0x3, 0xff, 0xbe,

    /* U+32 "2" */
    0x0, 0xf1, 0x3d, 0xf7, 0xfb, 0xad, 0xc8, 0x3,
    0xfc, 0x35, 0xb0, 0x82, 0x0, 0x14, 0x8d, 0xa1,
    0x0, 0xf8, 0xfd, 0x40, 0x3f, 0xcb, 0xe4, 0x1,
    0xc5, 0x82, 0x1, 0xff, 0xc0, 0x1c, 0x10, 0xd,
    0xe0, 0x1f, 0xfc, 0x31, 0xa0, 0x9, 0x48, 0x3,
    0x85, 0xea, 0x8e, 0x1, 0xe4, 0x30, 0x7, 0x0,
    0x71, 0x7c, 0x2a, 0xa3, 0x44, 0x3, 0xa8, 0x0,
    0x80, 0x1d, 0xe2, 0x1, 0x8a, 0x80, 0x39, 0x0,
    0x80, 0x39, 0x8, 0x3, 0xc8, 0x20, 0x18, 0x81,
    0x80, 0x38, 0xc0, 0x3f, 0x28, 0x7, 0x8, 0x80,
    0x3f, 0xf8, 0x42, 0x1, 0xc6, 0x1, 0xff, 0xc3,
    0x10, 0xe, 0x30, 0xf, 0xfe, 0x1b, 0x80, 0x70,
    0xb2, 0x27, 0x68, 0x7, 0xe2, 0x0, 0xc2, 0x7,
    0x77, 0xca, 0x1, 0xf0, 0x88, 0x3, 0x28, 0x7,
    0xff, 0xd, 0x40, 0x38, 0xc0, 0x3f, 0xf8, 0x7a,
    0x1, 0xd8, 0x1, 0xff, 0xc3, 0x70, 0xc, 0x28,
    0x1, 0xff, 0xc2, 0x41, 0x0, 0xce, 0x1, 0xff,
    0xc3, 0xf0, 0xe, 0xa0, 0xf, 0xfe, 0x11, 0x20,
    0x6, 0x33, 0x0, 0x7f, 0xf0, 0xac, 0x3, 0xa8,
    0x3, 0xff, 0x84, 0x2c, 0x1, 0x85, 0x80, 0x3f,
    0xf8, 0x50, 0x1, 0xd2, 0x1, 0xff, 0xc2, 0x16,
    0x0, 0xc2, 0xe0, 0x1f, 0xfc, 0x29, 0x0, 0xe9,
    0x0, 0xff, 0xe1, 0xb, 0x80, 0x73, 0x80, 0x7f,
    0xf0, 0xa4, 0x3, 0x9c, 0x3, 0xff, 0x86, 0xc0,
    0x1d, 0x20, 0x1f, 0xfc, 0x27, 0x10, 0xc, 0xc2,
    0x1, 0xff, 0xc2, 0x90, 0xe, 0x80, 0xf, 0xfe,
    0x13, 0x88, 0x6, 0x61, 0x0, 0xff, 0xe1, 0x48,
    0x7, 0x58, 0x7, 0xff, 0x9, 0x84, 0x3, 0x29,
    0x0, 0x7f, 0xf0, 0xac, 0x3, 0xa0, 0x3, 0xff,
    0x84, 0xa4, 0x1, 0x90, 0x80, 0x3f, 0xf8, 0x50,
    0x1, 0xd0, 0x1, 0xff, 0xc2, 0x52, 0x0, 0xc8,
    0x60, 0x1f, 0xfc, 0x29, 0x0, 0xef, 0x0, 0xff,
    0xe1, 0x21, 0x80, 0x63, 0x40, 0xf, 0xfe, 0x14,
    0x0, 0x74, 0x0, 0x7f, 0xf0, 0x90, 0xc0, 0x31,
    0x20, 0x7, 0xff, 0xb, 0xc0, 0x3a, 0x0, 0x3f,
    0xf8, 0x46, 0x80, 0x18, 0x94, 0x3, 0xff, 0x85,
    0x0, 0x1d, 0x60, 0x1f, 0xfc, 0x23, 0x40, 0xe,
    0x24, 0x4f, 0xfe, 0x8, 0x20, 0x7, 0xae, 0xff,
    0xf8, 0x46, 0x1, 0xff, 0xff, 0x0, 0xff, 0xe0,
    0x80,

    /* U+33 "3" */
    0x0, 0xf2, 0x4e, 0xf7, 0xf6, 0xd3, 0x0, 0x7f,
    0xc9, 0xb6, 0xc4, 0x20, 0x24, 0xb3, 0xcc, 0x1,
    0xf9, 0xec, 0x80, 0x3f, 0x86, 0x64, 0x1, 0xe5,
    0x80, 0xf, 0xfe, 0xb, 0x38, 0x6, 0x1a, 0x0,
    0xff, 0xe1, 0xc0, 0x80, 0x52, 0x1, 0xe3, 0x9b,
    0x94, 0x0, 0xf4, 0x80, 0x4c, 0x1, 0xcd, 0x8c,
    0x8d, 0x6e, 0x1, 0xca, 0x0, 0x21, 0x0, 0xc3,
    0x20, 0x1d, 0x2, 0x1, 0x88, 0x41, 0x80, 0x39,
    0xc0, 0x3e, 0x40, 0xe, 0x50, 0x10, 0xe, 0xe0,
    0xf, 0xb4, 0x3, 0x88, 0xc, 0x3, 0xff, 0x82,
    0x40, 0x1d, 0xc0, 0x1f, 0xfc, 0x31, 0x0, 0xe1,
    0x0, 0xff, 0xe1, 0xb8, 0x7, 0xc9, 0x33, 0xca,
    0x1, 0xff, 0xc3, 0x26, 0x6e, 0x20, 0xf, 0x9c,
    0x3, 0x84, 0x3, 0xff, 0x86, 0x20, 0x1f, 0xfc,
    0x92, 0x0, 0xee, 0x0, 0xff, 0xe1, 0xf0, 0x7,
    0x10, 0x7, 0xff, 0xd, 0xc0, 0x39, 0x40, 0x3f,
    0xf8, 0x4a, 0x20, 0x18, 0x84, 0x3, 0xff, 0x80,
    0x2d, 0x40, 0x1d, 0x60, 0x1f, 0xc7, 0xff, 0x74,
    0x80, 0x72, 0x30, 0x7, 0xff, 0x1d, 0x28, 0x3,
    0xff, 0x8e, 0x76, 0x20, 0x1f, 0xfc, 0x73, 0xa0,
    0xf, 0xfe, 0x4a, 0xd0, 0x7, 0xf8, 0xfb, 0xad,
    0x70, 0xe, 0x57, 0x0, 0xff, 0x8, 0xc5, 0x16,
    0x1, 0xd2, 0x1, 0xff, 0xc3, 0x45, 0x0, 0xc2,
    0xa0, 0x1f, 0xfc, 0x3f, 0x0, 0xec, 0x0, 0xff,
    0xe1, 0xa0, 0x7, 0x28, 0x7, 0xff, 0xc, 0x40,
    0x38, 0x80, 0x3f, 0xf8, 0x82, 0x1, 0x84, 0x3,
    0xff, 0x88, 0x60, 0x1f, 0xfc, 0x91, 0x0, 0xff,
    0xf3, 0x2b, 0xbf, 0x0, 0x7f, 0xf1, 0x26, 0x23,
    0x84, 0x3, 0xf0, 0x80, 0x7f, 0xf2, 0x4c, 0x3,
    0xff, 0x92, 0x20, 0x18, 0x41, 0xc0, 0x3f, 0xf8,
    0x24, 0x1, 0xc6, 0x2, 0x1, 0xc4, 0x1, 0xf3,
    0x80, 0x73, 0x1, 0x0, 0x75, 0x80, 0x7d, 0xe0,
    0x1c, 0x41, 0x80, 0x1c, 0xc2, 0x1, 0xc4, 0xa0,
    0x1d, 0xe0, 0x82, 0x1, 0x87, 0x10, 0x2, 0x3c,
    0x0, 0xf3, 0x80, 0x24, 0x3, 0x8a, 0xfb, 0x3b,
    0x4, 0x3, 0x98, 0x40, 0xe, 0x40, 0x1e, 0x13,
    0x10, 0xf, 0xc, 0x0, 0x6c, 0x10, 0xf, 0xfe,
    0x16, 0x88, 0x6, 0x1f, 0x30, 0xf, 0xf8, 0xb4,
    0xc0, 0x3c, 0x39, 0x24, 0x1, 0xf1, 0x4e, 0x90,
    0x7, 0xf3, 0x6f, 0x54, 0xc4, 0xd7, 0x6b, 0x0,
    0x78,

    /* U+34 "4" */
    0x0, 0xff, 0xe0, 0xff, 0xf5, 0x0, 0x7f, 0xf1,
    0x54, 0x3, 0xb8, 0x3, 0xff, 0x8b, 0xc0, 0x18,
    0x50, 0x3, 0xff, 0x88, 0x28, 0x1, 0x9c, 0x3,
    0xff, 0x8a, 0xe0, 0x1d, 0xa0, 0x1f, 0xfc, 0x5a,
    0x0, 0xc2, 0x80, 0x1f, 0xfc, 0x41, 0x30, 0xc,
    0xe0, 0x1f, 0xfc, 0x56, 0x0, 0xea, 0x0, 0xff,
    0xe2, 0xd0, 0x6, 0x13, 0x0, 0xff, 0xe2, 0x11,
    0x0, 0x33, 0x0, 0x7f, 0xf1, 0x68, 0x3, 0xac,
    0x3, 0xff, 0x8a, 0xc0, 0x18, 0x8c, 0x3, 0xff,
    0x88, 0x62, 0x1, 0x94, 0x3, 0xff, 0x8b, 0x40,
    0x1d, 0x40, 0x1f, 0xfc, 0x57, 0x0, 0xc4, 0x40,
    0xf, 0xfe, 0x22, 0x8, 0x6, 0xa0, 0xf, 0xfe,
    0x2f, 0x0, 0x72, 0x80, 0x7f, 0xf1, 0x54, 0x3,
    0x19, 0x0, 0x7f, 0xf1, 0x14, 0x3, 0xa8, 0x3,
    0xff, 0x8b, 0xc0, 0x1c, 0xe0, 0x1f, 0xfc, 0x41,
    0x40, 0xc, 0x82, 0x1, 0xff, 0xc4, 0x70, 0xe,
    0xd0, 0xf, 0xfe, 0x2d, 0x0, 0x73, 0x80, 0x7f,
    0xf1, 0x8, 0xc0, 0x32, 0x8, 0x7, 0xff, 0x11,
    0x40, 0x3b, 0x80, 0x3f, 0xf8, 0xb4, 0x1, 0xca,
    0x1, 0x44, 0x73, 0x0, 0x7c, 0x64, 0x1, 0x94,
    0x3, 0x3b, 0xf5, 0x80, 0x7d, 0x60, 0x1d, 0xe0,
    0x1f, 0xfc, 0x56, 0x0, 0xe5, 0x0, 0xff, 0xe2,
    0x20, 0x80, 0x65, 0x0, 0xff, 0xe2, 0xe8, 0x7,
    0x70, 0x7, 0xff, 0x15, 0xc0, 0x30, 0xa0, 0x7,
    0xff, 0x11, 0x44, 0x3, 0x38, 0x7, 0xff, 0x17,
    0xc0, 0x3b, 0x40, 0x3f, 0xf8, 0xaa, 0x1, 0x85,
    0x0, 0x3f, 0xf8, 0x8c, 0x1, 0xce, 0x1, 0xff,
    0xc5, 0xd0, 0xe, 0xa0, 0xf, 0xfe, 0x2a, 0x80,
    0x76, 0x7f, 0xfc, 0x1, 0xc5, 0xff, 0x30, 0x7,
    0xff, 0xfc, 0x3, 0xff, 0x93, 0xb7, 0x7f, 0xfc,
    0x10, 0xe, 0x2b, 0xb9, 0xcd, 0x13, 0xff, 0x82,
    0x1, 0xe4, 0x48, 0x40, 0x3f, 0xff, 0xe0, 0x1f,
    0xff, 0xf0, 0xf, 0xfe, 0x30,

    /* U+35 "5" */
    0x5f, 0xff, 0xfe, 0x3c, 0x80, 0x7f, 0xff, 0xc0,
    0x3f, 0xf9, 0x15, 0x77, 0xff, 0xc2, 0x0, 0xf9,
    0x13, 0xff, 0x84, 0x40, 0x1f, 0xff, 0xf0, 0xf,
    0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3, 0x9f, 0x3f,
    0xdd, 0x6c, 0x1, 0xff, 0xc1, 0x3d, 0x83, 0x0,
    0xa, 0x4e, 0xa0, 0x7, 0xf9, 0x70, 0x80, 0x3e,
    0x2b, 0x40, 0xf, 0xea, 0x0, 0xff, 0xac, 0x80,
    0x3f, 0x8, 0x7, 0xff, 0x2, 0x0, 0x3f, 0xc5,
    0x39, 0x6a, 0x1, 0xe5, 0x10, 0xf, 0xcb, 0xac,
    0x69, 0x52, 0x1, 0xe7, 0x0, 0xf8, 0x68, 0x3,
    0x98, 0xc0, 0x3b, 0x0, 0x3e, 0x60, 0xf, 0xa8,
    0x3, 0x9c, 0x3, 0xec, 0x0, 0xf9, 0x0, 0x38,
    0x80, 0x3e, 0x70, 0xf, 0x88, 0x3, 0xff, 0x94,
    0x20, 0x1c, 0x29, 0x99, 0xc6, 0x1, 0xf8, 0x80,
    0x38, 0xc4, 0xcf, 0x80, 0x3f, 0x9c, 0x3, 0x84,
    0x3, 0xff, 0xb2, 0x20, 0x1f, 0xfc, 0xf7, 0x0,
    0xff, 0xef, 0xb8, 0x7, 0xff, 0x28, 0x4c, 0xf8,
    0x3, 0xff, 0x89, 0x19, 0x9c, 0x60, 0x1f, 0x84,
    0x3, 0x84, 0x3, 0xff, 0x86, 0xe0, 0x1c, 0x60,
    0x1f, 0xfc, 0x31, 0x0, 0xe1, 0x10, 0x7, 0x38,
    0x7, 0xe2, 0x0, 0xf7, 0x80, 0x71, 0x0, 0x7c,
    0x40, 0x1c, 0x60, 0x40, 0x1d, 0xa0, 0x1f, 0x28,
    0x7, 0x28, 0x20, 0x7, 0x21, 0x80, 0x70, 0xc8,
    0x7, 0x60, 0x9, 0x80, 0x76, 0x28, 0x4, 0x78,
    0x20, 0x18, 0x54, 0x1, 0x0, 0x1e, 0xaf, 0xcd,
    0xc2, 0x0, 0xe9, 0x0, 0x91, 0x0, 0x1f, 0x19,
    0x0, 0x78, 0xdc, 0x3, 0x59, 0x0, 0x7f, 0xf0,
    0x47, 0x40, 0x3d, 0x88, 0x1, 0xff, 0x17, 0x88,
    0x7, 0x86, 0xec, 0x60, 0x1f, 0x14, 0xe8, 0x80,
    0x7f, 0x26, 0x75, 0xcc, 0x42, 0xb7, 0x4c, 0x1,
    0xe0,

    /* U+36 "6" */
    0x0, 0xff, 0x1f, 0xff, 0x58, 0x7, 0xff, 0xe,
    0x80, 0x3b, 0x80, 0x3f, 0xf8, 0x6c, 0x1, 0x85,
    0x40, 0x3f, 0xf8, 0x4a, 0x1, 0xce, 0x1, 0xff,
    0xc3, 0xe0, 0xe, 0xb0, 0xf, 0xfe, 0x10, 0xa0,
    0x6, 0x32, 0x0, 0xff, 0xe1, 0x30, 0x7, 0x50,
    0x7, 0xff, 0xe, 0x80, 0x39, 0x80, 0x3f, 0xf8,
    0x46, 0x40, 0x19, 0x80, 0x3f, 0xf8, 0x74, 0x1,
    0xd4, 0x1, 0xff, 0xc3, 0x60, 0xc, 0x46, 0x1,
    0xff, 0xc2, 0x50, 0xe, 0xa0, 0xf, 0xfe, 0x1c,
    0x80, 0x73, 0x0, 0x7f, 0xf0, 0x88, 0xc0, 0x32,
    0x88, 0x7, 0xff, 0xa, 0x80, 0x3b, 0x80, 0x3f,
    0xf8, 0x6c, 0x1, 0x85, 0x0, 0x3f, 0xf8, 0x48,
    0x20, 0x19, 0x80, 0x3f, 0xf8, 0x7c, 0x1, 0xd2,
    0x1, 0xff, 0xc3, 0x50, 0xc, 0x82, 0x1, 0xff,
    0xc2, 0x60, 0xe, 0xe0, 0xf, 0xfe, 0x1d, 0x0,
    0x61, 0x15, 0xf7, 0xf5, 0xb0, 0x7, 0xe2, 0x30,
    0xc, 0x36, 0x82, 0x2, 0x93, 0xa6, 0x1, 0xea,
    0x0, 0xff, 0xe0, 0x96, 0x18, 0x7, 0x28, 0x7,
    0xff, 0xf, 0x40, 0x31, 0x90, 0x7, 0xc2, 0x1,
    0xf0, 0xc8, 0x5, 0x60, 0x1e, 0x8e, 0xe7, 0xe1,
    0x0, 0x73, 0x0, 0x48, 0x1, 0xd0, 0xe2, 0x0,
    0x3d, 0x10, 0xe, 0x50, 0x1, 0x80, 0x61, 0x70,
    0xf, 0x48, 0x7, 0x78, 0x10, 0x7, 0x20, 0x7,
    0xc8, 0x1, 0xce, 0xe, 0x1, 0xda, 0x1, 0xf1,
    0x80, 0x71, 0x81, 0x0, 0x71, 0x0, 0x7e, 0x10,
    0xc, 0x21, 0xc0, 0x1c, 0xc0, 0x1f, 0x88, 0x3,
    0x84, 0xc0, 0x38, 0x40, 0x3f, 0x38, 0x7, 0x18,
    0x80, 0x71, 0x80, 0x7e, 0x10, 0xf, 0xfe, 0x83,
    0x80, 0x7f, 0xf7, 0xdc, 0x3, 0xff, 0x9e, 0x60,
    0x1f, 0x84, 0x3, 0xc2, 0x1, 0xc2, 0x1, 0xf9,
    0xc0, 0x38, 0xcc, 0x1, 0xce, 0x1, 0xf8, 0x40,
    0x38, 0x44, 0x1, 0xc4, 0x1, 0xf8, 0x80, 0x3d,
    0xc0, 0x1d, 0xe0, 0x1f, 0x10, 0x7, 0x10, 0x28,
    0x7, 0x38, 0x7, 0xc8, 0x1, 0xce, 0x6, 0x20,
    0x18, 0x54, 0x3, 0xd6, 0x1, 0xde, 0x0, 0x70,
    0xe, 0xa5, 0x0, 0x8a, 0xc8, 0x3, 0x90, 0x1,
    0x60, 0x1e, 0xae, 0xcd, 0xd2, 0x0, 0x73, 0x8,
    0x0, 0x9c, 0x3, 0xc2, 0x64, 0x1, 0xe1, 0x80,
    0xd, 0x8, 0x1, 0xff, 0xc2, 0xa1, 0x0, 0xeb,
    0x50, 0xf, 0xf8, 0x6d, 0x0, 0x3e, 0xab, 0x30,
    0xf, 0x85, 0xfd, 0x0, 0x3f, 0x93, 0x3a, 0xe6,
    0x26, 0xb3, 0xa0, 0x40, 0x38,

    /* U+37 "7" */
    0x2f, 0xff, 0xfe, 0x4b, 0x0, 0x7f, 0xff, 0xc0,
    0x3f, 0xf9, 0x6b, 0x77, 0xfc, 0x80, 0x1c, 0xa0,
    0x1e, 0x34, 0x4f, 0xe6, 0x0, 0xc2, 0x60, 0x1f,
    0xfc, 0x32, 0x20, 0x6, 0x40, 0xf, 0xfe, 0x22,
    0x80, 0x77, 0x80, 0x7f, 0xf1, 0x2c, 0x3, 0x94,
    0x3, 0xff, 0x86, 0x26, 0x1, 0x90, 0x3, 0xff,
    0x88, 0x80, 0x1d, 0x80, 0x3, 0x3f, 0x70, 0x7,
    0xde, 0x1, 0xca, 0x0, 0x1c, 0xce, 0x70, 0xf,
    0x90, 0x3, 0x11, 0x0, 0x3f, 0xf8, 0x66, 0x20,
    0x19, 0x0, 0x3f, 0xf8, 0x96, 0x1, 0xda, 0x1,
    0xff, 0xc4, 0x50, 0xe, 0x40, 0xf, 0xfe, 0x18,
    0x90, 0x6, 0x40, 0xf, 0xfe, 0x23, 0x80, 0x76,
    0x80, 0x7f, 0xf1, 0x34, 0x3, 0x9c, 0x3, 0xff,
    0x88, 0x80, 0x18, 0x84, 0x3, 0xff, 0x86, 0x80,
    0x1c, 0xa0, 0x1f, 0xfc, 0x4d, 0x0, 0xeb, 0x0,
    0xff, 0xe2, 0x38, 0x6, 0x13, 0x0, 0xff, 0xe1,
    0x98, 0x80, 0x64, 0x0, 0xff, 0xe2, 0x20, 0x7,
    0x78, 0x7, 0xff, 0x12, 0xc0, 0x39, 0x0, 0x3f,
    0xf8, 0x62, 0x60, 0x18, 0xc4, 0x3, 0xff, 0x86,
    0xe0, 0x1d, 0x60, 0x1f, 0xfc, 0x4c, 0x0, 0xe5,
    0x0, 0xff, 0xe2, 0x28, 0x6, 0x12, 0x0, 0xff,
    0xe1, 0xa0, 0x7, 0x38, 0x7, 0xff, 0x13, 0x0,
    0x3b, 0x40, 0x3f, 0xf8, 0x8a, 0x1, 0xc8, 0x1,
    0xff, 0xc3, 0x22, 0x0, 0x64, 0x0, 0xff, 0xe2,
    0x28, 0x7, 0x68, 0x7, 0xff, 0x13, 0x0, 0x39,
    0xc0, 0x3f, 0xf8, 0x88, 0x1, 0x88, 0x40, 0x3f,
    0xf8, 0x6a, 0x1, 0xca, 0x1, 0xff, 0xc4, 0xf0,
    0xe, 0xb0, 0xf, 0xfe, 0x22, 0x0, 0x61, 0x30,
    0xf, 0xfe, 0x19, 0x88, 0x6, 0x40, 0xf, 0xfe,
    0x25, 0x80, 0x77, 0x80, 0x7f, 0xf1, 0x14, 0x3,
    0x90, 0x3, 0xff, 0x86, 0x24, 0x1, 0x8c, 0x40,
    0x3f, 0xf8, 0x6e, 0x1, 0xd6, 0x1, 0xff, 0xc4,
    0xd0, 0xe, 0x40, 0xf, 0xfe, 0x22, 0x0, 0x61,
    0x30, 0xf, 0xfe, 0x1a, 0x0, 0x73, 0x80, 0x7f,
    0xf1, 0x34, 0x3, 0xb0, 0x3, 0xff, 0x88, 0xe0,
    0x1c, 0xa0, 0x1f, 0xfc, 0x10,

    /* U+38 "8" */
    0x0, 0xf2, 0x4e, 0x77, 0xfb, 0x69, 0x80, 0x3f,
    0xe2, 0xcb, 0x63, 0x10, 0x1, 0x2c, 0xfb, 0x80,
    0x7e, 0x5d, 0x30, 0xf, 0xf4, 0x58, 0x7, 0x92,
    0x80, 0x3f, 0xf8, 0x29, 0x40, 0x1d, 0x40, 0x1f,
    0xfc, 0x35, 0x50, 0x4, 0xc2, 0x1, 0xc3, 0x15,
    0x28, 0x1, 0xe8, 0x0, 0xa8, 0x3, 0x8f, 0x9d,
    0x5a, 0xe4, 0x3, 0x88, 0x80, 0x3, 0x0, 0xef,
    0x0, 0xe6, 0x30, 0xe, 0x40, 0x20, 0xe, 0x13,
    0x0, 0xf5, 0x80, 0x77, 0x83, 0x0, 0x72, 0x80,
    0x7c, 0x60, 0x1c, 0x60, 0x20, 0x1c, 0x40, 0x1f,
    0x30, 0x7, 0x30, 0x18, 0x7, 0x70, 0x7, 0xc6,
    0x1, 0xff, 0xc9, 0x10, 0xe, 0x10, 0xf, 0xfe,
    0x48, 0x81, 0x80, 0x7f, 0xf2, 0x44, 0x3, 0xbc,
    0x3, 0xe1, 0x0, 0xe7, 0x6, 0x0, 0xe2, 0x0,
    0xf8, 0x80, 0x38, 0x80, 0x80, 0x39, 0x80, 0x3e,
    0x50, 0xe, 0xe0, 0x1, 0x80, 0x63, 0x10, 0xf,
    0x60, 0x7, 0x20, 0x2, 0xc0, 0x3a, 0x40, 0x38,
    0x94, 0x3, 0x9, 0x80, 0x18, 0x3, 0x9e, 0x48,
    0x5, 0x70, 0x3, 0xa4, 0x2, 0x1a, 0x0, 0xe6,
    0xdf, 0xea, 0x10, 0xc, 0x6e, 0x1, 0x96, 0x0,
    0x3f, 0xf8, 0x27, 0xa0, 0x1e, 0x78, 0x0, 0xff,
    0x8b, 0x4, 0x3, 0xcd, 0x0, 0x1f, 0xf1, 0x58,
    0x80, 0x72, 0xc8, 0x7, 0xff, 0x5, 0x34, 0x3,
    0x15, 0x0, 0x73, 0x6f, 0xf4, 0x88, 0x6, 0x38,
    0x0, 0xac, 0x3, 0x9e, 0x48, 0x5, 0xb0, 0x3,
    0x9c, 0x40, 0xc, 0x1, 0x86, 0x0, 0x38, 0xa0,
    0x3, 0x98, 0x10, 0x3, 0x9c, 0x3, 0xe5, 0x0,
    0xec, 0x3, 0x0, 0xec, 0x0, 0xf8, 0x84, 0x3,
    0x28, 0x70, 0x7, 0x30, 0x7, 0xe2, 0x0, 0xc2,
    0x6, 0x1, 0xc2, 0x1, 0xf9, 0xc0, 0x38, 0x44,
    0x1, 0xc6, 0x1, 0xff, 0xc2, 0x30, 0xf, 0xfe,
    0x18, 0x80, 0x79, 0xc0, 0x3f, 0xfe, 0xae, 0x1,
    0xc6, 0x1, 0xf8, 0x40, 0x3f, 0xf8, 0x2, 0x1,
    0xf9, 0xc0, 0x38, 0xc4, 0x3, 0x9c, 0x3, 0xf0,
    0x80, 0x70, 0x98, 0x7, 0x10, 0x7, 0xe2, 0x0,
    0xf7, 0x0, 0x77, 0x80, 0x7c, 0x40, 0x1c, 0x40,
    0x60, 0x1c, 0xe0, 0x1f, 0x28, 0x7, 0x30, 0x28,
    0x7, 0xa, 0x80, 0x7a, 0x40, 0x3b, 0x0, 0x50,
    0x3, 0xa9, 0x40, 0x22, 0xc1, 0x0, 0xe5, 0x0,
    0x78, 0x7, 0xab, 0xb3, 0x74, 0x60, 0x1c, 0x84,
    0x0, 0x45, 0x0, 0xf0, 0x99, 0x0, 0x7d, 0x20,
    0x1a, 0x8c, 0x3, 0xff, 0x85, 0x64, 0x1, 0xd8,
    0xc0, 0x1f, 0xf0, 0xe2, 0x0, 0x7d, 0x38, 0x80,
    0x1f, 0xb, 0xf1, 0x80, 0x7f, 0x1d, 0xfd, 0xcc,
    0x42, 0xb7, 0xa0, 0x3, 0xc0,

    /* U+39 "9" */
    0x0, 0xf2, 0x4e, 0x77, 0xf6, 0xd3, 0x8, 0x7,
    0xf8, 0xf2, 0xd8, 0xc4, 0x4, 0x96, 0x79, 0xc0,
    0x3f, 0x2e, 0x18, 0x7, 0xfa, 0x28, 0x3, 0xc7,
    0x40, 0x1f, 0xfc, 0x15, 0x90, 0xe, 0xe0, 0xf,
    0xfe, 0x1b, 0x18, 0x4, 0xc4, 0x1, 0xc5, 0x17,
    0x4a, 0x1, 0xef, 0x0, 0xa8, 0x3, 0x97, 0x5d,
    0x16, 0xac, 0x3, 0x8c, 0x80, 0x4c, 0x3, 0xac,
    0x3, 0x91, 0x80, 0x39, 0x41, 0x0, 0x39, 0x4,
    0x3, 0xd4, 0x1, 0xd8, 0x4, 0x1, 0xd8, 0x1,
    0xf1, 0x80, 0x72, 0x87, 0x0, 0x71, 0x0, 0x7e,
    0x10, 0xc, 0x20, 0x60, 0x1c, 0xc0, 0x1f, 0x88,
    0x3, 0x84, 0x40, 0x1c, 0x20, 0x1f, 0x9c, 0x3,
    0xff, 0x80, 0x60, 0x1f, 0x84, 0x3, 0x8d, 0xc0,
    0x3f, 0xfe, 0xae, 0x1, 0xff, 0xc8, 0x30, 0xf,
    0x18, 0x7, 0xe1, 0x0, 0xf0, 0x80, 0x70, 0x80,
    0x7e, 0x70, 0xe, 0x13, 0x0, 0xe6, 0x0, 0xfc,
    0x20, 0x18, 0x40, 0x40, 0x38, 0x80, 0x3f, 0x10,
    0x6, 0x20, 0xe0, 0xe, 0xd0, 0xf, 0x88, 0x3,
    0x98, 0x14, 0x3, 0x90, 0x3, 0xe5, 0x0, 0xed,
    0x3, 0x10, 0xc, 0x2e, 0x1, 0xc3, 0x20, 0x1c,
    0x80, 0x7, 0x0, 0xe8, 0x92, 0x1, 0x5c, 0x10,
    0xe, 0x30, 0x5, 0x80, 0x79, 0xb7, 0xfa, 0x88,
    0x3, 0x90, 0x2, 0x27, 0x0, 0xff, 0xe2, 0x68,
    0x6, 0x85, 0x0, 0xff, 0xe1, 0xb8, 0x7, 0x53,
    0x80, 0x7f, 0xf0, 0x54, 0x40, 0x3d, 0x1b, 0x8,
    0x42, 0x92, 0xe0, 0x1d, 0xc0, 0x1f, 0x89, 0xef,
    0x7a, 0xd9, 0x40, 0x30, 0xa0, 0x7, 0xff, 0x9,
    0x8, 0x3, 0x30, 0x7, 0xff, 0xf, 0x80, 0x3a,
    0x80, 0x3f, 0xf8, 0x42, 0xa0, 0x18, 0xc8, 0x3,
    0xff, 0x84, 0xc0, 0x1d, 0x40, 0x1f, 0xfc, 0x3a,
    0x0, 0xe6, 0x0, 0xff, 0xe1, 0x19, 0x0, 0x66,
    0x0, 0xff, 0xe1, 0xd0, 0x7, 0x50, 0x7, 0xff,
    0xd, 0x80, 0x31, 0x18, 0x7, 0xff, 0x9, 0x80,
    0x3a, 0x80, 0x3f, 0xf8, 0x74, 0x1, 0xcc, 0x1,
    0xff, 0xc2, 0x23, 0x0, 0xc8, 0x20, 0x1f, 0xfc,
    0x2b, 0x0, 0xee, 0x0, 0xff, 0xe1, 0xb8, 0x6,
    0x15, 0x0, 0xff, 0xe1, 0x28, 0x80, 0x67, 0x0,
    0xff, 0xe1, 0xc8, 0x7, 0x58, 0x7, 0xff, 0x8,
    0x8c, 0x3, 0x19, 0x0, 0x7f, 0xf0, 0xa8, 0x3,
    0xa8, 0x3, 0xff, 0x86, 0xc0, 0x1c, 0xe0, 0x1f,
    0xfc, 0x25, 0x10, 0xc, 0xa2, 0x1, 0xfe,

    /* U+3A ":" */
    0xff, 0xf8, 0x80, 0x3f, 0xfc, 0x9b, 0xbf, 0x11,
    0x7e, 0x0, 0xff, 0xff, 0x80, 0x7f, 0xf6, 0x88,
    0xbe, 0xd, 0xdf, 0x88, 0x3, 0xff, 0xc8,

    /* U+44 "D" */
    0x6f, 0xff, 0xfe, 0x7, 0x6d, 0x28, 0x80, 0x7f,
    0xf2, 0x4, 0x96, 0xb9, 0xc0, 0x3f, 0xf9, 0x91,
    0xa4, 0x1, 0xff, 0xcb, 0x2c, 0x20, 0xf, 0xfe,
    0x58, 0xf8, 0x80, 0x7e, 0x16, 0x6f, 0x20, 0x7,
    0xc5, 0x0, 0x1f, 0x8a, 0x67, 0xd7, 0xee, 0x1,
    0xe6, 0x20, 0xf, 0xfe, 0x24, 0x40, 0x3, 0xca,
    0x1, 0xff, 0xc5, 0x73, 0x0, 0xea, 0x0, 0xff,
    0xe3, 0x48, 0x7, 0x10, 0x7, 0xff, 0x19, 0x0,
    0x3c, 0x60, 0x1f, 0xfc, 0x51, 0x20, 0xe, 0x60,
    0xf, 0xfe, 0x33, 0x0, 0x71, 0x0, 0x7f, 0xf1,
    0x88, 0x3, 0xbc, 0x3, 0xff, 0x8c, 0x20, 0x1c,
    0x20, 0x1f, 0xfc, 0x6f, 0x0, 0xe3, 0x0, 0xff,
    0xe6, 0x8, 0x7, 0xff, 0x18, 0x40, 0x39, 0xc0,
    0x3f, 0xfb, 0xe6, 0x1, 0xff, 0xd2, 0x10, 0xf,
    0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3, 0xff, 0xfe,
    0x1, 0xff, 0xe5, 0x10, 0xf, 0xfe, 0x31, 0x80,
    0x7f, 0xf9, 0x44, 0x3, 0x9c, 0x3, 0xff, 0x98,
    0x20, 0x1f, 0xfc, 0x6f, 0x0, 0xe3, 0x0, 0xff,
    0xe3, 0x8, 0x7, 0x8, 0x7, 0xff, 0x18, 0x80,
    0x3b, 0xc0, 0x3f, 0xf8, 0xcc, 0x1, 0xc4, 0x1,
    0xff, 0xc5, 0x12, 0x0, 0xe6, 0x0, 0xff, 0xe2,
    0xa0, 0x7, 0x8c, 0x3, 0xff, 0x8b, 0x20, 0x1c,
    0x40, 0x1f, 0xfc, 0x57, 0x30, 0xe, 0xa0, 0xf,
    0xfe, 0x24, 0x40, 0x3, 0xca, 0x1, 0xf1, 0x4c,
    0xfa, 0xfd, 0xc0, 0x3c, 0xc4, 0x1, 0xf0, 0xb3,
    0x79, 0x0, 0x3e, 0x28, 0x0, 0xff, 0xe5, 0xf,
    0x88, 0x7, 0xff, 0x24, 0xb0, 0x80, 0x3f, 0xf9,
    0x31, 0xa4, 0x1, 0xff, 0xc5, 0x12, 0x5a, 0xe7,
    0x0, 0xf0,

    /* U+48 "H" */
    0x6f, 0xfe, 0xc0, 0xf, 0xfb, 0x7f, 0xf9, 0x80,
    0x3f, 0xff, 0xe0, 0x1f, 0xff, 0xf0, 0xf, 0xff,
    0xf8, 0x7, 0xff, 0xfc, 0x3, 0xff, 0xfe, 0x1,
    0xff, 0xff, 0x0, 0xff, 0xff, 0x80, 0x78, 0xff,
    0xff, 0xe2, 0x0, 0xff, 0xff, 0x80, 0x7f, 0xf6,
    0x45, 0x9b, 0xfe, 0x10, 0xf, 0xfe, 0x1, 0x4c,
    0xff, 0xc6, 0x1, 0xff, 0xff, 0x0, 0xff, 0xff,
    0x80, 0x7f, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0x1f,
    0xff, 0xf0, 0xf, 0xff, 0xf8, 0x7, 0xff, 0xfc,
    0x3, 0xff, 0xa6,

    /* U+4D "M" */
    0x6f, 0xfe, 0x90, 0xf, 0xfe, 0x38, 0xff, 0xf8,
    0x3, 0xcc, 0x1, 0xff, 0xc7, 0x70, 0xf, 0xfe,
    0xa, 0x80, 0x7f, 0xf1, 0xa8, 0x3, 0xff, 0x83,
    0xc0, 0x1f, 0xfc, 0x52, 0x30, 0xf, 0xfe, 0xa,
    0x8, 0x7, 0xff, 0x12, 0x80, 0x3f, 0xf8, 0x6c,
    0x1, 0xff, 0xc4, 0x60, 0xf, 0xfe, 0x1d, 0x0,
    0x7f, 0xf0, 0xd0, 0x40, 0x3f, 0xf8, 0x64, 0x40,
    0xf, 0xfe, 0x16, 0x80, 0x7f, 0xf1, 0x68, 0x3,
    0xff, 0x84, 0xc0, 0x1f, 0xfc, 0x56, 0x0, 0xff,
    0xe0, 0xa8, 0x7, 0xff, 0x18, 0x50, 0x3, 0xff,
    0x81, 0xc0, 0x1f, 0xfc, 0x7e, 0x0, 0xff, 0x85,
    0x0, 0x3f, 0xf8, 0xea, 0x1, 0xff, 0x38, 0x7,
    0xff, 0x25, 0x40, 0x3f, 0xd4, 0x1, 0xff, 0xc9,
    0xe0, 0xf, 0xe2, 0x30, 0xf, 0xfe, 0x20, 0x80,
    0x64, 0x10, 0xf, 0xd4, 0x1, 0x90, 0x3, 0xff,
    0x80, 0x46, 0x1, 0x98, 0x3, 0xf3, 0x0, 0x6d,
    0x0, 0xff, 0xe0, 0xd8, 0x6, 0xa0, 0xf, 0x8c,
    0x40, 0x23, 0x20, 0xf, 0xfe, 0xb, 0x0, 0x62,
    0x30, 0xf, 0x50, 0x6, 0xb0, 0xf, 0xfe, 0x10,
    0x98, 0x6, 0xa0, 0xf, 0x30, 0x6, 0x60, 0xf,
    0xfe, 0x1d, 0x0, 0x67, 0x0, 0xe5, 0x0, 0xc6,
    0x20, 0x1f, 0xfc, 0x37, 0x0, 0xc2, 0x80, 0x1b,
    0x80, 0x35, 0x0, 0x7f, 0xf1, 0x5, 0x0, 0x37,
    0x0, 0x42, 0x80, 0x19, 0xc0, 0x3f, 0xf8, 0xba,
    0x1, 0x94, 0x2, 0x70, 0xc, 0x82, 0x1, 0xff,
    0xc5, 0x60, 0xe, 0x60, 0x5, 0x0, 0x6d, 0x0,
    0xff, 0xe3, 0xa0, 0x6, 0xa0, 0x23, 0x0, 0xce,
    0x1, 0xff, 0xc7, 0xe0, 0xc, 0x65, 0x40, 0x19,
    0x4, 0x3, 0xff, 0x8e, 0xa0, 0x1c, 0xaa, 0x0,
    0xda, 0x1, 0xff, 0xc9, 0x50, 0xd, 0x4, 0x1,
    0x9c, 0x3, 0xff, 0x93, 0xe0, 0x1f, 0xc8, 0x20,
    0x1f, 0xfc, 0x95, 0x0, 0xfe, 0xe0, 0xf, 0xfe,
    0x5a, 0x80, 0x7e, 0x50, 0xf, 0xfe, 0x5f, 0x0,
    0x7c, 0xa0, 0x1f, 0xfc, 0xc4, 0x10, 0xf, 0x78,
    0x7, 0xff, 0x35, 0xc0, 0x3c, 0xa0, 0x1f, 0xfc,
    0xdd, 0x0, 0xe5, 0x0, 0xff, 0xe7, 0x20, 0x80,
    0x6e, 0x0, 0xff, 0xe7, 0xb8, 0x6, 0x40, 0xf,
    0xfe, 0x7d, 0xbb, 0xd2, 0x1, 0xff, 0xd0, 0x28,
    0x89, 0x80, 0x3f, 0xff, 0xe0, 0x1f, 0xff, 0xf0,
    0xf, 0xff, 0xf8, 0x7, 0xff, 0xfc, 0x3, 0xff,
    0xfe, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 215, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 439, .box_w = 21, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 186, .adv_w = 439, .box_w = 15, .box_h = 51, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 439, .box_w = 22, .box_h = 51, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 439, .box_w = 22, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 898, .adv_w = 439, .box_w = 24, .box_h = 51, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1159, .adv_w = 439, .box_w = 22, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1400, .adv_w = 439, .box_w = 22, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1733, .adv_w = 439, .box_w = 23, .box_h = 51, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2018, .adv_w = 439, .box_w = 22, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 2375, .adv_w = 439, .box_w = 22, .box_h = 51, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2702, .adv_w = 279, .box_w = 8, .box_h = 31, .ofs_x = 6, .ofs_y = 0},
    {.bitmap_index = 2725, .adv_w = 516, .box_w = 25, .box_h = 51, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 2951, .adv_w = 528, .box_w = 25, .box_h = 51, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 3026, .adv_w = 666, .box_w = 33, .box_h = 51, .ofs_x = 4, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x24, 0x28, 0x2d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 46, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 15, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 1
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t DIN1451_m_cond_72 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 52,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -10,
    .underline_thickness = 4,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DIN1451_M_COND_72*/
