/* Copyright 2024 Manianac(Jeff K)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

// #undef STM32_HSE_ENABLED
// #define STM32_HSE_ENABLED                   TRUE

// #undef STM32_PLLSRC
// #define STM32_PLLSRC                        STM32_PLLSRC_HSE

// #undef STM32_PLLM_VALUE
// #define STM32_PLLM_VALUE                    1

// #undef STM32_PLLN_VALUE
// #define STM32_PLLN_VALUE                    12

// #undef STM32_PLLPDIV_VALUE
// #define STM32_PLLPDIV_VALUE                 2

// // #undef STM32_PLLP_VALUE
// // #define STM32_PLLP_VALUE                    7

// #undef STM32_PLLQ_VALUE
// #define STM32_PLLQ_VALUE                    4

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE

#define I2C_DRIVER I2CD2
#define I2C2_SCL_PIN A9
#define I2C2_SCL_PAL_MODE 4
#define I2C2_SDA_PIN A8
#define I2C2_SDA_PAL_MODE 4

#define I2C2_TIMINGR_PRESC   0x0U
#define I2C2_TIMINGR_SCLDEL  0x3U
#define I2C2_TIMINGR_SDADEL  0x3U
#define I2C2_TIMINGR_SCLH   0x10U
#define I2C2_TIMINGR_SCLL   0x61U

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

/* Reallocate the SysTick timer from TIM2 to TIM5, TIM2 is used for in switch leds */
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5
