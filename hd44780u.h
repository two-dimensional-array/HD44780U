#ifndef __HD44780U__
#define __HD44780U__

#ifdef __cplusplus
extern "C" {
#endif

#define HD44780U_USE_ONLY_HALF_CONN_MODE 0
#define HD44780U_USE_ONLY_FULL_CONN_MODE 1
#define HD44780U_USE_BOTH_CONN_MODES     2

#define HD44780U_USE_ONLY_5X8_FONT       0
#define HD44780U_USE_ONLY_5X10_FONT      1
#define HD44780U_USE_BOTH_FONTS          2

#define HD44780U_USE_ONLY_1_ROW_COUNT    0
#define HD44780U_USE_ONLY_2_ROW_COUNT    1
#define HD44780U_USE_BOTH_ROW_COUNTS     2

#define HD44780U_USE_ONLY_8_ROW_LENGHT   0
#define HD44780U_USE_ONLY_16_ROW_LENGHT  1
#define HD44780U_USE_BOTH_ROW_LENGHTS    2

#include <stdint.h>
#include "hd44780u_config.h"

#ifndef HD44780U_CONN_MODE
#define HD44780U_CONN_MODE HD44780U_USE_BOTH_CONN_MODES
#endif

#ifndef HD44780U_FONT
#define HD44780U_FONT HD44780U_USE_BOTH_FONTS
#endif

#ifndef HD44780U_ROW_COUNT
#define HD44780U_ROW_COUNT HD44780U_USE_BOTH_ROW_COUNTS
#endif

#ifndef HD44780U_ROW_LENGHT
#define HD44780U_ROW_LENGHT HD44780U_USE_BOTH_ROW_LENGHTS
#endif

#if (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES) 
enum EHD44780UConnMode
{
    Half = 0,
    Full = 1
};

typedef enum EHD44780UConnMode hd44780u_conn_mode_t;
#endif

#if (HD44780U_FONT == HD44780U_USE_BOTH_FONTS) 
enum EHD44780UFont
{
    Size5x8 = 0,
    Size5x10 = 1
};

typedef enum EHD44780UFont hd44780u_font_t;
#endif

#if (HD44780U_ROW_COUNT == HD44780U_USE_BOTH_ROW_COUNTS) 
enum EHD44780URowCount
{
    OneRow = 0,
    TwoRows = 1
};

typedef enum EHD44780URowCount hd44780u_row_count_t;
#endif

#if (HD44780U_ROW_LENGHT == HD44780U_USE_BOTH_ROW_LENGHTS) 
enum EHD44780URowLenght
{
    Lenght8 = 0,
    Lenght16 = 1
};

typedef enum EHD44780URowLenght hd44780u_row_lenght_t;
#endif

typedef void (*hd44780u_set_gpio_state_t)(bool);
typedef void (*hd44780u_set_data_gpio_state_t)(uint8_t);

struct SHD44780U
{
#if (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES) 
    hd44780u_conn_mode_t connMode : 1;
#endif
#if (HD44780U_FONT == HD44780U_USE_BOTH_FONTS) 
    hd44780u_font_t font : 1;
#endif
#if (HD44780U_ROW_COUNT == HD44780U_USE_BOTH_ROW_COUNTS) 
    hd44780u_row_count_t rowCount : 1;
#endif
#if (HD44780U_ROW_LENGHT == HD44780U_USE_BOTH_ROW_LENGHTS) 
    hd44780u_row_lenght_t rowLenght : 1;
#endif
    hd44780u_set_gpio_state_t setEN;
    hd44780u_set_gpio_state_t setRW;
    hd44780u_set_gpio_state_t setRS;
    hd44780u_set_data_gpio_state_t setData;
};

typedef struct SHD44780U hd44780u_t;

void HD44780UInit(hd44780u_t* pDisplay);
void HD44780USetPosition(hd44780u_t* pDisplay, uint8_t position);
void HD44780UWriteString(hd44780u_t* pDisplay, const char* str);

#ifdef __cplusplus
}
#endif // extern "C"

#endif // __HD44780U__
