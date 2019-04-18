#include "fathom.h"

void fathom(void)
{
    uint32_t t = 0;
    uint32_t btn_timer = 0;

    uint32_t led_timer = 0;
    int16_t leds = 0;

    uint8_t buttons;

    for(ever)
    {
        t = millis();

        if (btn_timer <= t)
        {
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
            }
            if ( buttons & BTN_RIGHT )
            {
                note(_D5, 30);
                leds += 12;
            }

            if ( buttons & BTN_A )
            {
                note(_Ds5, 30);
                leds += 12;
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

            btn_timer = t+120;
        }

        if (led_timer <= t)
        {
            leds -= 5;
            led_timer = t+130;
        }

        if (leds < 0)
            leds = 0;
        if (leds > 255)
            leds = 255;

        set_LED_brightness(BOTH, leds);

        //draw();
    }
}
