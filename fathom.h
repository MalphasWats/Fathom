#ifndef FATHOM_H
#define FATHOM_H

#include "GLYPH.h"
#include "tilemap-engine.h"
#include "ASCII.h"

#define BTN_DELAY 20

static const __flash uint8_t TILES[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xe0, 0xa0,
    0xa0, 0xa0, 0xe0, 0xa0, 0xa0, 0xa0, 0xa0, 0xe0,
    0xa0, 0xa0, 0xa0, 0xa0, 0xe0, 0xa0, 0xa0, 0xa0,
    0xe0, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10,  //water
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08,
    0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x10,
    0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08,
    0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08,
};

static const __flash uint8_t CHARACTER[] = {
    0x40, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x20, 0xf0,
    0xa0, 0x90, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xdf, 0x00, 0x10, 0x10, 0x18, 0x06, 0xde,
    0x77, 0x7b, 0xdc, 0x06, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd,
    0x02, 0x04, 0xf7, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x02, 0x02, 0x02, 0x38, 0x42, 0x92, 0x78, // RUN
    0xd2, 0xca, 0x72, 0x82, 0x83, 0x82, 0x43, 0x42,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xef,
    0x3b, 0x3d, 0xee, 0x43, 0x40, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x04, 0x04, 0x04, 0x06,
    0x01, 0x02, 0x03, 0x00, 0x00, 0x07, 0x04, 0x00,
};

#define STANDING 0*8
#define WALKING 6*8

#define TRANSP &BLOCK_MASKS[TRANSPARENT]

#define PLANK_L 0*8
#define PLANK_A 1*8
#define PLANK_B 2*8
#define PLANK_R 3*8

#define WATER_A 8*8
#define WATER_B 9*8
#define WATER_C 10*8
#define WATER_D 11*8
#define WATER_E 12*8
#define WATER_F 13*8
#define WATER_G 14*8
#define WATER_H 15*8

typedef struct Tile {
    int16_t x;
    int16_t y;

    const __flash uint8_t* tile;
    const __flash uint8_t* mask;
} Tile;

typedef struct Layer {
    uint16_t num_tiles;
    Tile tiles[];
} Layer;

static const Layer platforms = {
    .num_tiles = 8,
    .tiles = {
        {.x=5*8, .y=5*8, .tile=&TILES[PLANK_L], .mask=TRANSP},
        {.x=6*8, .y=5*8, .tile=&TILES[PLANK_A], .mask=TRANSP},
        {.x=7*8, .y=5*8, .tile=&TILES[PLANK_B], .mask=TRANSP},
        {.x=8*8, .y=5*8, .tile=&TILES[PLANK_A], .mask=TRANSP},
        {.x=9*8, .y=5*8, .tile=&TILES[PLANK_B], .mask=TRANSP},
        {.x=10*8, .y=5*8, .tile=&TILES[PLANK_A], .mask=TRANSP},
        {.x=11*8, .y=5*8, .tile=&TILES[PLANK_B], .mask=TRANSP},
        {.x=12*8, .y=5*8, .tile=&TILES[PLANK_R], .mask=TRANSP},
    }
};

static const Layer background = {
    .num_tiles = 16,
    .tiles = {
        {.x=0*8, .y=6*8, .tile=&TILES[WATER_A], .mask=TRANSP},
        {.x=1*8, .y=6*8, .tile=&TILES[WATER_C], .mask=TRANSP},
        {.x=2*8, .y=6*8, .tile=&TILES[WATER_B], .mask=TRANSP},
        {.x=3*8, .y=6*8, .tile=&TILES[WATER_E], .mask=TRANSP},
        {.x=4*8, .y=6*8, .tile=&TILES[WATER_F], .mask=TRANSP},
        {.x=5*8, .y=6*8, .tile=&TILES[WATER_D], .mask=TRANSP},
        {.x=6*8, .y=6*8, .tile=&TILES[WATER_A], .mask=TRANSP},
        {.x=7*8, .y=6*8, .tile=&TILES[WATER_B], .mask=TRANSP},
        {.x=8*8, .y=6*8, .tile=&TILES[WATER_A], .mask=TRANSP},
        {.x=9*8, .y=6*8, .tile=&TILES[WATER_H], .mask=TRANSP},
        {.x=10*8, .y=6*8, .tile=&TILES[WATER_G], .mask=TRANSP},
        {.x=11*8, .y=6*8, .tile=&TILES[WATER_E], .mask=TRANSP},
        {.x=12*8, .y=6*8, .tile=&TILES[WATER_F], .mask=TRANSP},
        {.x=13*8, .y=6*8, .tile=&TILES[WATER_G], .mask=TRANSP},
        {.x=14*8, .y=6*8, .tile=&TILES[WATER_D], .mask=TRANSP},
        {.x=15*8, .y=6*8, .tile=&TILES[WATER_H], .mask=TRANSP},

        //TODO: Poles
    }
};

/*static const __flash uint8_t MASKS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // SPACE

};*/


void fathom(void);

#endif
