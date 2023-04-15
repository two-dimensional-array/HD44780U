#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum EWH1602ConnMode
{
    Half,
    Full
};

enum EWH1602Font
{
    Size5x8,
    Size5x10
};

struct SWH1602
{
    enum EWH1602ConnMode connMode : 1;
    enum EWH1602Font font : 1;
    uint8_t rowCount : 2; // 1 or 2
    uint8_t rowLenght : 5; // 8 or 16
    void (*setEN)(bool);
    void (*setRW)(bool);
    void (*setRS)(bool);
    void (*setData)(uint8_t);
};

typedef struct SWH1602 wh1602_t;

void WH1602Init(wh1602_t* pDisplay);
void WH1602WriteString(wh1602_t* pDisplay, const char* str);

#ifdef __cplusplus
}
#endif // extern "C"
