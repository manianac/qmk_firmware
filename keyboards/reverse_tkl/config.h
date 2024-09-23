#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_DISPLAY_128X64
#define OLED_COM_PINS COM_PINS_ALT
#define OLED_BRIGHTNESS 128
#define OLED_IC OLED_IC_SH1106
#define OLED_COLUMN_OFFSET 2
#define OLED_TIMEOUT 120000
#define OLED_BOOT_LOGO_TIMEOUT 1500
#define OLED_BRIGHTNESS_STEP 4

//#define WS2812_BITBANG_NOP_FUDGE 1
#define WS2812_TIMING 800
// #define WS2812_T1H 580
// #define WS2812_T1L 220
// #define WS2812_T0H 200
// #define WS2812_T0L 480
#define WS2812_TRST_US 300
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB

#define WS2812_PWM_DRIVER	PWMD8
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 4
// #define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM1
// #define WS2812_PWM_DMA_CHANNEL 1
#define WS2812_PWM_DMAMUX_ID STM32_DMAMUX1_TIM8_UP
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_TARGET_PERIOD 800000

#define DEBUG_MATRIX_SCAN_RATE

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define OLED_FONT_H "custom_font.h"
