#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum EHD44780UConnMode
{
    Half = 0,
    Full = 1
};

typedef enum EHD44780UConnMode hd44780u_conn_mode_t;

enum EHD44780UFont
{
    Size5x8 = 0,
    Size5x10 = 1
};

typedef enum EHD44780UFont hd44780u_font_t;

enum EHD44780URowCount
{
    OneRow = 0,
    TwoRows = 1
};

typedef enum EHD44780URowCount hd44780u_row_count_t;

enum EHD44780URowLenght
{
    Lenght8 = 0,
    Lenght16 = 1
};

typedef enum EHD44780URowLenght hd44780u_row_lenght_t;

typedef void (*hd44780u_set_gpio_state_t)(bool);
typedef void (*hd44780u_set_data_gpio_state_t)(uint8_t);

struct SHD44780U
{
    hd44780u_conn_mode_t connMode : 1;
    hd44780u_font_t font : 1;
    hd44780u_row_count_t rowCount : 1;
    hd44780u_row_lenght_t rowLenght : 1;
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
