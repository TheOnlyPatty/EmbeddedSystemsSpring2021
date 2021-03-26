#include "revF14.h"
#include "fall17lib.h"
#include "esos_menu.h"
#include "esos_f14ui.h"
#include "esos_sensor.h"
#include "esos_pic24.h"
#include "esos_pic24_sensor.h"
#include "esos_pic24_spi.h"
#include "esos_pic24_i2c.h"
#include "esos_pic24_irq.h"
#include "pic24_timer.h"

static BOOL b_updating_lm60;
static BOOL b_updating_1631;

static esos_menu_longmenu_t main_menu = {
	.u8_numitems = 8,
	.u8_choice = 0, //Default
	.ast_items = {
		{ "Set", "wvform", 0 },
        { "Set", "freq", 0 },
		{ "Set", "ampltd", 0 },
		{ "Set", "duty", 1 },
		{ "Read", "LM60", 0 },
		{ "Read", "1631", 0 },
		{ "Set", "LEDs", 0 },
		{ "About", "...", 0 },
	},
};

/*
static esos_menu_staticmenu_t err = {
	.u8_numlines = 2,
	.u8_currentline = 0,
	.lines = {{"404"}, {"NotFnd"}},
};
*/

static esos_menu_slider_bar_t lm60 = {
    .value = 2500,
    .min = 2000,
    .max = 3500,
    .div = 100,
    .type = 1,
    .lines = { { "LM60" }, { "       " } },
};

static esos_menu_slider_bar_t ds1631 = {
    .value = 25,
    .min = 18,
    .max = 34,
    .div = 1,
    .type = 1,
    .lines = { { "DS1631" }, { "       " } },
};

static esos_menu_entry_t leds = {
	.entries[0].label = "LEDs = ",
	.entries[0].value = 1,
	.entries[0].min = 0,
	.entries[0].max = 7,
};

static esos_menu_staticmenu_t greet = {
	.u8_numlines = 2,
	.u8_currentline = 0,
	.lines = {{"Hello"}, {"friend"}},
};
static esos_menu_staticmenu_t about = {
    .u8_numlines = 2,
    .u8_currentline = 0,
	.lines = {{"scons"}, {"sucks"}}, // Maybe too long? nope
};

ESOS_USER_TASK(menu_choices) {
	ESOS_TASK_BEGIN();

	while(TRUE) {
		ESOS_TASK_WAIT_ESOS_MENU_LONGMENU(main_menu);
		/*
		// Waveform
		if (main_menu.u8_choice == 0) {
			
		}
		// Frequency
		else if (main_menu.u8_choice == 1) {
			
		}
		// Amplitude
		else if (main_menu.u8_choice == 2) {
			
		}
		// Duty Cycle
		else if (main_menu.u8_choice == 3) {
			
		}
		*/
		// LM60 (Temp sensor on board)
		if (main_menu.u8_choice == 4) {
			b_updating_lm60 = 1;
            ESOS_TASK_WAIT_ESOS_MENU_SLIDER_BAR(lm60);
            b_updating_lm60 = 0;
		}
		// 1631 (I2C temp sensor)
		else if (main_menu.u8_choice == 5) {
			b_updating_1631 = 1;
            ESOS_TASK_WAIT_ESOS_MENU_SLIDER_BAR(ds1631);
            b_updating_1631 = 0;
		}
		// LEDs
		else if (main_menu.u8_choice == 6) {
			ESOS_TASK_WAIT_ESOS_MENU_ENTRY(leds);
		}
		// About
		else if (main_menu.u8_choice == 7) {
			ESOS_TASK_WAIT_ESOS_MENU_STATICMENU(about);
		}
	}

	ESOS_TASK_END();
}

ESOS_USER_TASK(binary_leds) {
	ESOS_TASK_BEGIN();

	esos_uiF14_turnLED1Off();
	esos_uiF14_turnLED2Off();
	esos_uiF14_turnLED3Off();

	while (TRUE) {
		LED1 = (leds.entries[0].value & 0b100);
		LED2 = (leds.entries[0].value & 0b010);
		LED3 = (leds.entries[0].value & 0b001) != 0b001;
		ESOS_TASK_WAIT_TICKS(100);
	}
	ESOS_TASK_END();
}

/* Small error relating to converting to string
ESOS_USER_TASK(update_lm60)
{
    static ESOS_TASK_HANDLE read_temp;
    static uint16_t pu16_data;
    static uint32_t u32_temp_temp, u32_temp_int, u32_temp_dec;
    static char temp32_str[12];
    static uint8_t i;

    ESOS_TASK_BEGIN();

    while (TRUE) {
        if (b_updating_lm60) {
            ESOS_ALLOCATE_CHILD_TASK(read_temp);
            ESOS_TASK_SPAWN_AND_WAIT(read_temp, _WAIT_ON_AVAILABLE_SENSOR, THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
            ESOS_TASK_SPAWN_AND_WAIT(read_temp, _WAIT_SENSOR_READ, &pu16_data, ESOS_SENSOR_ONE_SHOT,
                                     ESOS_SENSOR_FORMAT_VOLTAGE);
            ESOS_SENSOR_CLOSE();

			// Convert from voltage in mV to temperature in Celsius
			u32_temp_temp = (uint32_t)pu16_data * 1000; // no decimals
			u32_temp_temp = (u32_temp_temp - 424000) / 625; // see datasheet page 1 "Typical Application" for formula
			u32_temp_int = u32_temp_temp / 100; // integer only
			u32_temp_dec = u32_temp_temp - (u32_temp_int * 100); // decimal only

            convert_uint32_t_to_str(u32_temp_int, temp32_str, 12, 10);
            temp32_str[2] = '.';
            convert_uint32_t_to_str(u32_temp_dec, temp32_str + 3, 8, 10);
            if (u32_temp_dec >= 0 && u32_temp_dec <= 9) {
                temp32_str[4] = temp32_str[3];
                temp32_str[3] = '0';
            }

            temp32_str[5] = 'C';

            for (i = 0; i < 8; i++) {
                lm60.lines[1][i] = temp32_str[i];
            }

            lm60.value = u32_temp_temp;

        }
        ESOS_TASK_WAIT_TICKS(125);
    }
    ESOS_TASK_END();
}
*/

void user_init() {
	esos_menu_init();
	esos_pic24_configI2C1(500);
	//configSPI1();
	esos_RegisterTask(menu_choices);
	esos_RegisterTask(binary_leds);
}
