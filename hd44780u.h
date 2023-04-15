#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum EHD44780UConnMode
{
    Half,
    Full
};

enum EHD44780UFont
{
    Size5x8,
    Size5x10
};

struct SHD44780U
{
    enum EHD44780UConnMode connMode : 1;
    enum EHD44780UFont font : 1;
    uint8_t rowCount : 2; // 1 or 2
    uint8_t rowLenght : 5; // 8 or 16
    void (*setEN)(bool);
    void (*setRW)(bool);
    void (*setRS)(bool);
    void (*setData)(uint8_t);
};

typedef struct SHD44780U hd44780u_t;

void HD44780UInit(hd44780u_t* pDisplay);
void HD44780USetPosition(hd44780u_t* pDisplay, uint8_t position);
void HD44780UWriteString(hd44780u_t* pDisplay, const char* str);

#ifdef __cplusplus
}
#endif // extern "C"
