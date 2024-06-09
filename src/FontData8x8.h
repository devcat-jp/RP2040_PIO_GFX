#ifndef FONTDATA8X8_H
#define FONTDATA8X8_H
#include <avr/pgmspace.h>

namespace RP2040_PIO_GFX {
    const uint8_t FontData8 [] PROGMEM = {
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // !
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // "
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // #
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // $
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // %
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // &
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // '
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // (
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // )
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // *
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // +
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // ,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // -
        0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x60,                  // .
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // /
        0x0,0x3C,0x42,0x46,0x5A,0x62,0x42,0x3C,             // 0
        0x0,0x8,0x18,0x8,0x8,0x8,0x8,0x1C,                  // 1
        0x0,0x3C,0x42,0x2,0xC,0x30,0x40,0x7E,               // 2
        0x0,0x3C,0x42,0x2,0x1C,0x2,0x42,0x3C,               // 3
        0x0,0xC,0x14,0x24,0x24,0x24,0x3E,0x4,               // 4
        0x0,0x7E,0x40,0x7C,0x2,0x2,0x42,0x3C,               // 5
        0x0,0x3C,0x40,0x7C,0x42,0x42,0x42,0x3C,             // 6
        0x0,0x7E,0x42,0x2,0x4,0x4,0x8,0x8,                  // 7
        0x0,0x3C,0x42,0x42,0x3C,0x42,0x42,0x3C,             // 8
        0x0,0x3C,0x42,0x42,0x3E,0x2,0x2,0x3C,               // 9
        0x0,0x18,0x18,0x0,0x0,0x18,0x18,0x0,                // :
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // ;
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // <
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // =
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // >
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // ?
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,                    // @
        0x0,0x3C,0x42,0x42,0x7E,0x42,0x42,0x42,             // A
        0x0,0x7C,0x22,0x22,0x3C,0x22,0x22,0x7C,             // B
        0x0,0x3C,0x42,0x40,0x40,0x40,0x42,0x3C,             // C
        0x0,0x7C,0x22,0x22,0x22,0x22,0x22,0x7C,             // D
        0x0,0x7E,0x40,0x40,0x7E,0x40,0x40,0x7E,             // E
        0x0,0x7E,0x40,0x40,0x7E,0x40,0x40,0x40,             // F
        0x0,0x3C,0x42,0x40,0x4E,0x42,0x42,0x3C,             // G
        0x0,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,             // H
        0x0,0x1C,0x8,0x8,0x8,0x8,0x8,0x1C,                  // I
        0x0,0x1E,0x4,0x4,0x4,0x4,0x44,0x38,                 // J
        0x0,0x44,0x48,0x50,0x60,0x50,0x48,0x44,             // K
        0x0,0x40,0x40,0x40,0x40,0x40,0x40,0x7C,             // L
        0x0,0x82,0xC6,0xAA,0x92,0x92,0x82,0x82,             // M
        0x0,0x42,0x62,0x52,0x5A,0x4A,0x46,0x42,             // N
        0x0,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,             // O
        0x0,0x7C,0x42,0x42,0x42,0x7C,0x40,0x40,             // P
        0x0,0x3C,0x42,0x42,0x42,0x4A,0x44,0x3A,             // Q
        0x0,0x7C,0x42,0x42,0x42,0x7C,0x44,0x42,             // R
        0x0,0x3C,0x42,0x40,0x3C,0x2,0x42,0x3C,              // S
        0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8,                   // T
        0x0,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,             // U
        0x0,0x42,0x42,0x42,0x24,0x24,0x24,0x18,             // V
        0x0,0x82,0x92,0x92,0xAA,0xAA,0x44,0x44,             // W
        0x0,0x42,0x42,0x24,0x18,0x24,0x42,0x42,             // X
        0x0,0x82,0x44,0x28,0x10,0x10,0x10,0x10,             // Y
        0x0,0x7E,0x2,0x4,0x18,0x20,0x40,0x7E,               // Z
    };
}

#endif