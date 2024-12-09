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

#undef STM32_HSE_ENABLED
#define STM32_HSE_ENABLED                   TRUE

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED                   FALSE

#undef STM32_PLLSRC
#define STM32_PLLSRC                        STM32_PLLSRC_HSE

#undef STM32_I2C2SEL
#define STM32_I2C2SEL                       STM32_I2C2SEL_PCLK1

#undef STM32_CLK48SEL
#define STM32_CLK48SEL                      STM32_CLK48SEL_PLLQCLK

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE                    1

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE                    12

#undef STM32_PLLPDIV_VALUE
#define STM32_PLLPDIV_VALUE                 2

#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE                    7

#undef STM32_PLLR_VALUE
#define STM32_PLLR_VALUE                    2

#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE                    4

#undef STM32_PPRE1
#define STM32_PPRE1                         STM32_PPRE1_DIV1

#undef STM32_PPRE2
#define STM32_PPRE2                         STM32_PPRE2_DIV1

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2                  TRUE

#undef STM32_PWM_USE_TIM5
#define STM32_PWM_USE_TIM5                  TRUE

#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA                   TRUE

#undef STM32_ADC_USE_ADC2
#define STM32_ADC_USE_ADC2 TRUE
