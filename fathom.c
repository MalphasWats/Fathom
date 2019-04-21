#include "fathom.h"

void fathom(void)
{
    uint32_t t = 0;
    uint32_t btn_timer = 0;

    uint32_t move_timer = 0;

    uint32_t led_timer = 0;
    int16_t leds = 0;

    uint8_t buttons;

    Sprite player = {
        .x = 6*8,
        .y = 1*8,
        .width = 16,
        .height = 24,
        .tile = &CHARACTER[STANDING],
        .mask = &BLOCK_MASKS[TRANSPARENT],
    };

    int8_t vy = 0;

    for(ever)
    {
        t = millis();

        if (btn_timer <= t)
        {
            if (player.tile == &CHARACTER[WALKING])
                player.tile = &CHARACTER[STANDING];

            buttons = read_buttons();
            if ( buttons & BTN_UP )
            {
                note(_A4, 30);
                leds += 12;
            }
            if ( buttons & BTN_DOWN )
            {
                note(_Bb4, 30);
                leds += 12;
            }
            if ( buttons & BTN_LEFT )
            {
                note(_B4, 30);
                leds += 12;

                player.tile=&CHARACTER[WALKING];
                player.x -= 2;
            }
            if ( buttons & BTN_RIGHT )
            {
                note(_D5, 30);
                leds += 12;

                player.tile=&CHARACTER[WALKING];
                player.x += 2;
            }

            if ( buttons & BTN_A )
            {
                note(_Ds5, 30);
                leds += 12;

                vy = -6;
            }
            if ( buttons & BTN_B )
            {
                note(_E5, 30);
                leds += 12;
            }
            if ( buttons & BTN_C )
            {
                note(_Fs5, 30);
                leds += 12;
            }
            if ( buttons & BTN_D )
            {
                note(_A5, 30);
                leds += 12;
            }

            btn_timer = t+BTN_DELAY;
        }

        if (led_timer <= t)
        {
            leds -= 5;
            led_timer = t+BTN_DELAY+20;
        }

        if (leds < 0)
            leds = 0;
        if (leds > 255)
            leds = 255;

        set_LED_brightness(BOTH, leds);

        clear_buffer();

        for (uint8_t i=0 ; i<platforms.num_tiles ; i++)
            draw_tile(platforms.tiles[i].tile, platforms.tiles[i].mask, platforms.tiles[i].x, platforms.tiles[i].y);

        if (move_timer <= t)
        {
            vy += 1; // GRAVITY
            if (vy > 4)
                vy = 4;

            move_timer = t+10;

            //TODO: make into function
            for(uint8_t dy=player.y+12 ; dy<player.y+vy+12 ; dy++)
            {
                if (buffer[ (dy>>3) * SCREEN_WIDTH + player.x ] & (1 << (dy&7)))
                {
                    vy = 0;
                    player.y = dy-12;
                    break;
                }
            }

            player.y += vy;

            if (player.y > SCREEN_HEIGHT-12)
                player.y = SCREEN_HEIGHT-12;
        }

        draw_sprite(&player);

        for (uint8_t i=0 ; i<background.num_tiles ; i++)
            draw_tile(background.tiles[i].tile, background.tiles[i].mask, background.tiles[i].x, background.tiles[i].y);

        draw();
    }
}
