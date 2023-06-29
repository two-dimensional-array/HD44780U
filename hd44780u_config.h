#ifndef __HD44780U_CONFIG__
#define __HD44780U_CONFIG__

#include "hd44780u.h"

// Example of definition defines for working with GPIO
// place to include GPIO hw header
//#include <gpio.hpp>
//
//#define HD44780U_GPIO_TYPE gpio_t
//#define HD44780U_GPIO_WRITE(pHW, state) (GPIOWrite(pHW, (state)))
//#define HD44780U_GPIO_WRITE_ARR(pHWArray, size, data) (GPIOWriteArray((pHWArray), (size), (data)))

// WH1602 HALF PINS 5X10 FONT CONFIG
#define HD44780U_CONN_MODE  HD44780U_USE_ONLY_HALF_CONN_MODE
#define HD44780U_FONT       HD44780U_USE_ONLY_5X10_FONT
#define HD44780U_ROW_COUNT  HD44780U_USE_ONLY_2_ROW_COUNT
#define HD44780U_ROW_LENGHT HD44780U_USE_ONLY_16_ROW_LENGHT
// WH1602 HALF PINS 5X10 FONT CONFIG

#endif
