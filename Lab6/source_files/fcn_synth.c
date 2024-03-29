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
    .min = 20,
    .max = 35,
    .div = 1,
    .type = 1,
    .lines = { { "DS1631" }, { "       " } },
};

static esos_menu_entry_t leds = {
	.entries[0].label = "LEDs = ",
	.entries[0].value = 7,
	.entries[0].min = 0,
	.entries[0].max = 7,
};

/*
static esos_menu_staticmenu_t greet = {
	.u8_numlines = 2,
	.u8_currentline = 0,
	.lines = {{"Hello"}, {"friend"}},
};
*/

static esos_menu_longmenu_t wvform = {
    .u8_numitems = 4,
    .u8_choice = 0,
    .ast_items = { { "Select", "Tri", 0 },
                   { "Select", "Square", 0 },
                   { "Select", "Sine", 0 },
                   { "Select", "Custom", 0 } },
};

static esos_menu_entry_t freq = {
    .entries[0].label = "Freq = ",
    .entries[0].value = 1000,
    .entries[0].min = 64,
    .entries[0].max = 2047,
};

static esos_menu_entry_t ampl = {
    .entries[0].label = "Ampl = ",
    .entries[0].value = 30,
    .entries[0].min = 0,
    .entries[0].max = 30,
};

static esos_menu_entry_t duty = {
    .entries[0].label = "Duty = ",
    .entries[0].value = 50,
    .entries[0].min = 0,
    .entries[0].max = 100,
};

static esos_menu_staticmenu_t about = {
    .u8_numlines = 2,
    .u8_currentline = 0,
    .lines = { { "Scons" }, { "Sucks <3" } },
};

ESOS_USER_TASK(menu_choices) {
	ESOS_TASK_BEGIN();

	while(TRUE) {
        
        //Show or hide duty bsaed on if square wave is chosen
        if (wvform.u8_choice == 1) main_menu.ast_items[3].b_hidden = FALSE;
        else main_menu.ast_items[3].b_hidden = TRUE;

        ESOS_TASK_WAIT_ESOS_MENU_LONGMENU(main_menu);
        
        //Set waveform type
        if (main_menu.u8_choice == 0) {
            ESOS_TASK_WAIT_ESOS_MENU_LONGMENU(wvform);
            ESOS_ALLOCATE_CHILD_TASK(update_hdl);
            ESOS_TASK_SPAWN_AND_WAIT(update_hdl, update_wvform, wvform.u8_choice, duty.entries[0].value, ampl.entries[0].value);
        //Set waveform frequency
        } else if (main_menu.u8_choice == 1) {
            ESOS_TASK_WAIT_ESOS_MENU_ENTRY(freq);
            PR4 = FCY / 8 / 128 / freq.entries[0].value;
            ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING(PR4);
            ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
        //Set waveform amplitude
        } else if (main_menu.u8_choice == 2) {
            ESOS_TASK_WAIT_ESOS_MENU_ENTRY(ampl);
            ESOS_TASK_SPAWN_AND_WAIT(update_hdl, update_wvform, wvform.u8_choice, duty.entries[0].value, ampl.entries[0].value);
        //Set square wave duty cycle
        } else if (main_menu.u8_choice == 3) {
            ESOS_TASK_WAIT_ESOS_MENU_ENTRY(duty);
            ESOS_TASK_SPAWN_AND_WAIT(update_hdl, update_wvform, wvform.u8_choice, duty.entries[0].value, ampl.entries[0].value);
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
    }
	ESOS_TASK_END();
}

ESOS_USER_TASK(binary_leds) {
	ESOS_TASK_BEGIN();

	esos_uiF14_turnLED1Off();
	esos_uiF14_turnLED2Off();
	esos_uiF14_turnLED3Off();

	while (TRUE) {
		if (leds.entries[0].value & 0b100) {
			esos_uiF14_turnLED1On();
		}
		else {
			esos_uiF14_turnLED1Off();
		}
			
		if (leds.entries[0].value & 0b010) {
			esos_uiF14_turnLED2On();
		}
		else {
			esos_uiF14_turnLED2Off();
		}
		if (leds.entries[0].value & 0b001) {
			esos_uiF14_turnLED3On();
		}
		else {
			esos_uiF14_turnLED3Off();
		}
		ESOS_TASK_WAIT_TICKS(100);
	}
	ESOS_TASK_END();
}


//ESOS_USER_TASK(read_lm60)

void writeSPI(uint16_t *pu16_out, uint16_t *pu16_in, uint16_t u16_cnt) {
    static uint16_t *pu16_inPtr;
    static uint16_t *pu16_outPtr;
    static uint16_t u16_tempCnt, u16_i;
    static uint8_t u8_isReading, u8_isWriting;
    uint16_t u16_scratch;
    pu16_outPtr = pu16_out;
    pu16_inPtr = pu16_in;
    u16_tempCnt = u16_cnt;

    if (pu16_outPtr == NULLPTR)
        u8_isWriting = FALSE;
    else
        u8_isWriting = TRUE;

    if (pu16_inPtr == NULLPTR)
        u8_isReading = FALSE;
    else
        u8_isReading = TRUE;

    if (SPI1STATbits.SPIROV) SPI1STATbits.SPIROV = 0;
    _SPI1IF = 0;
    u16_scratch = SPI1BUF;
    for (u16_i = 0; u16_i < u16_tempCnt; u16_i++) {
        if (u8_isWriting) {
            SPI1BUF = *pu16_outPtr;
            pu16_outPtr++;
        } else {
            SPI1BUF = 0;
        }
        while (SPI1STAT & SPI_TX_BUFFER_FULL);

        while (!(SPI1STAT & SPI_RX_BUFFER_FULL));
        
        u16_scratch = SPI1BUF;
        if (u8_isReading) *pu16_inPtr++ = u16_scratch;
    }
}

void write_DAC(uint16_t u16_data) {
    u16_data = 0x3000 | (u16_data >> 4);
    SLAVE_ENABLE();
    writeSPI(&u16_data, NULLPTR, 1);
    SLAVE_DISABLE();
}

ESOS_USER_INTERRUPT(ESOS_IRQ_PIC24_T4) {
    write_DAC(wvform_data[u8_wvform_idx]);
    u8_wvform_idx = ++u8_wvform_idx % 128;
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(ESOS_IRQ_PIC24_T4);
}

ESOS_CHILD_TASK(update_wvform, uint8_t u8_type, uint8_t u8_duty, uint8_t u8_ampl) {
    ESOS_TASK_BEGIN();
    static uint8_t u16_addr;
    static uint16_t u16_scaledData;
    static uint8_t u8_rawData;
    static uint16_t i;
    static uint8_t u8_currAmplitude;
    u8_currAmplitude = u8_ampl * UINT8_MAX / 30;
    
    if (u8_type == TRI_WVFORM) {
        for (i = 0; i < 64; i++) {
            u8_rawData = i * 2;
            u16_scaledData = u8_rawData * u8_currAmplitude;
            wvform_data[i] = u16_scaledData * 2;
        }
        for (i = 64; i > 0; i--) {
            u8_rawData = i * 2;
            u16_scaledData = u8_rawData * u8_currAmplitude;
            wvform_data[64 + (64 - i)] = u16_scaledData * 2;
        }
    }
    
    if (u8_type == SQUARE_WVFORM) {
        u8_duty = 128 * u8_duty / 100;
        for (i = 0; i < 128; i++) {
            u8_rawData = (i < u8_duty) ? 255 : 0;
            u16_scaledData = u8_rawData * u8_currAmplitude;
            wvform_data[i] = u16_scaledData;
        }
    }

    if (u8_type == SINE_WVFORM || u8_type == USER_WVFORM) {
        if (u8_type == SINE_WVFORM) {
            u16_addr = SINE_WVFORM_ADDR;
        } else {
            u16_addr = USER_WVFORM_ADDR;
        }
        ESOS_DISABLE_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_T4);
        for (i = 0; i < 128; i++) {
            ESOS_TASK_WAIT_ON_AVAILABLE_I2C();
            ESOS_TASK_WAIT_ON_WRITE1I2C1(AT24C02D_ADDR, u16_addr + i);
            ESOS_TASK_WAIT_ON_READ1I2C1(AT24C02D_ADDR, u8_rawData);
            ESOS_TASK_SIGNAL_AVAILABLE_I2C();
            ESOS_TASK_WAIT_TICKS(1);
            uint16_t a = u8_rawData;
            uint16_t b = u8_currAmplitude;
            u16_scaledData = a * b;
            wvform_data[i] = u16_scaledData;
        }
        ESOS_ENABLE_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_T4);
    }
    ESOS_TASK_YIELD();
    ESOS_TASK_END();
}

ESOS_USER_TASK(read_lm60) {
    static uint16_t pu16_data; // data coming from sensor
    static uint32_t pu32_data; // final (data together)
	static uint32_t temp32_int; // integer part (part before decimal)
	static uint32_t temp32_deci; // decimal part
    static char temp32_str[12];
    static uint8_t i;

    ESOS_TASK_BEGIN();

    while (TRUE) {
        if (b_updating_lm60) {
			ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
			ESOS_TASK_WAIT_SENSOR_READ(pu16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_VOLTAGE);

            ESOS_SENSOR_CLOSE();

			pu32_data = (uint32_t)pu16_data * 1000; // No decimals
            pu32_data = (pu32_data - 424000) / 625; // mV to temp
            temp32_int = pu32_data / 100; // Integer only
            temp32_deci = pu32_data - (temp32_int * 100); // Decimal only

			//printf("\n%lu.", temp32_int);
			//printf("%lu\n", temp32_deci);

            uint32_to_str(temp32_int, temp32_str, 12, 10);
            temp32_str[2] = '.'; // Decimal point after integer part
            uint32_to_str(temp32_deci, temp32_str + 3, 8, 10); // Put decimal part after decimal point
            if (temp32_deci >= 0 && temp32_deci <= 9) {
                temp32_str[4] = temp32_str[3];
                temp32_str[3] = '0';
            }

            temp32_str[5] = 'C';

            for (i = 0; i < 8; i++) {
                lm60.lines[1][i] = temp32_str[i];
            }

            lm60.value = pu32_data;

        }
        ESOS_TASK_WAIT_TICKS(200);
    }
    ESOS_TASK_END();
}

ESOS_USER_TASK(read_ds1631) {
    ESOS_TASK_BEGIN();

    ESOS_TASK_WAIT_ON_AVAILABLE_I2C();
    ESOS_TASK_WAIT_ON_WRITE2I2C1(DS1631_ADDRESS, 0xAC, 0x0C);
    ESOS_TASK_WAIT_ON_WRITE1I2C1(DS1631_ADDRESS, 0x51);
    ESOS_TASK_SIGNAL_AVAILABLE_I2C();
    ESOS_TASK_WAIT_TICKS(250); // wait for ds to come online

    static uint8_t i, u8_high, u8_low;
    static char temp32_str[12];

    while (TRUE) {
        if (b_updating_1631) {
            ESOS_TASK_WAIT_ON_AVAILABLE_I2C();
            ESOS_TASK_WAIT_ON_WRITE1I2C1(DS1631_ADDRESS, 0xAA); // Send READ command
            ESOS_TASK_WAIT_ON_READ2I2C1(DS1631_ADDRESS, u8_high, u8_low);
            ESOS_TASK_SIGNAL_AVAILABLE_I2C();

            uint32_to_str(u8_high, temp32_str, 12, 10);
            temp32_str[2] = '.';
            u8_low = u8_low * 100 / 256;
            uint32_to_str(u8_low, temp32_str + 3, 8, 10);
            if (u8_low >= 0 && u8_low <= 9) {
                temp32_str[4] = temp32_str[3];
                temp32_str[3] = '0';
            }

            temp32_str[5] = 'C';

            for (i = 0; i < 8; i++) {
                ds1631.lines[1][i] = temp32_str[i];
            }

            ds1631.value = u8_high;

            ESOS_TASK_WAIT_TICKS(750); // The Temp sensor can only poll at 750ms with 12 bit mode
            continue;
        }
        ESOS_TASK_YIELD();
    }

    ESOS_TASK_END();
}

void user_init() {
	esos_menu_init();
	esos_pic24_configI2C1(500);
    CONFIG_MCP4922_SPI(); 
	esos_RegisterTask(menu_choices);
	esos_RegisterTask(binary_leds);
	esos_RegisterTask(read_lm60);
	esos_RegisterTask(read_ds1631);
}
