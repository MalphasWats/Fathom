#ifndef FATHOM_H
#define FATHOM_H

#include "GLYPH.h"
#include "tilemap-engine.h"
#include "ASCII.h"

static const __flash uint8_t TILES[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // SPACE

};

static const __flash uint8_t MASKS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // SPACE

};


void fathom(void);

#endif
