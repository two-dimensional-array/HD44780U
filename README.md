# HD44780U

## Usage
Add/link hd44780u.c to your project and include hd44780u.h. That's it. Implement your low-level function of delay in microseconds needed for the correct working of this library:
```C
void HD44780UDelayUS(volatile uint32_t micros)
{
    // Wait time delay in microseconds.
}
```
## Compiler Switches/Defines
Define HD44780U_INCLUDE_CONFIG as compiler switch (e.g. gcc -DHD44780U_INCLUDE_CONFIG) to include a "hd44780u_config.h" definition file.
|Name|Default value|Values|Description|
|----|-------------|------|-----------|
|HD44780U_CONN_MODE     |HD44780U_USE_BOTH_CONN_MODES |HD44780U_USE_ONLY_HALF_CONN_MODE, HD44780U_USE_ONLY_FULL_CONN_MODE, HD44780U_USE_BOTH_CONN_MODES|Suported connetion modes : 4 pins, 8 pins|
|HD44780U_FONT          |HD44780U_USE_BOTH_FONTS      |HD44780U_USE_ONLY_5X8_FONT, HD44780U_USE_ONLY_5X10_FONT, HD44780U_USE_BOTH_FONTS                |Suported font types : 5x8, 5x10|
|HD44780U_ROW_COUNT     |HD44780U_USE_BOTH_ROW_COUNTS |HD44780U_USE_ONLY_1_ROW_COUNT, HD44780U_USE_ONLY_2_ROW_COUNT, HD44780U_USE_BOTH_ROW_COUNTS      |Suported row count : 1, 2|
|HD44780U_ROW_LENGHT    |HD44780U_USE_BOTH_ROW_LENGHTS|HD44780U_USE_ONLY_8_ROW_LENGHT, HD44780U_USE_ONLY_16_ROW_LENGHT, HD44780U_USE_BOTH_ROW_LENGHTS  |Suported row lenght : 8, 16|
