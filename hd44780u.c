#include "hd44780u.h"

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

#if (HD44780U_ROW_LENGHT == HD44780U_USE_ONLY_8_ROW_LENGHT)
#define __GET_ROW_LENGHT(handler) (8u)
#elif (HD44780U_ROW_LENGHT == HD44780U_USE_ONLY_16_ROW_LENGHT)
#define __GET_ROW_LENGHT(handler) (16u)
#elif (HD44780U_ROW_LENGHT == HD44780U_USE_BOTH_ROW_LENGHTS)
#define __GET_ROW_LENGHT(handler) ((Lenght8 == (handler)->rowLenght) ? 8 : 16)
#endif

#if (HD44780U_ROW_COUNT == HD44780U_USE_ONLY_1_ROW_COUNT)
#define __GET_ROW_COUNT(handler) (1u)
#elif (HD44780U_ROW_COUNT == HD44780U_USE_ONLY_2_ROW_COUNT)
#define __GET_ROW_COUNT(handler) (2u)
#elif (HD44780U_ROW_COUNT == HD44780U_USE_BOTH_ROW_COUNTS)
#define __GET_ROW_COUNT(handler) ((OneRow == (handler)->rowCount) ? 1 : 2)
#endif

#if (HD44780U_CONN_MODE != HD44780U_USE_ONLY_HALF_CONN_MODE) && \
	(HD44780U_CONN_MODE != HD44780U_USE_ONLY_FULL_CONN_MODE) && \
	(HD44780U_CONN_MODE != HD44780U_USE_BOTH_CONN_MODES)
#error Define HD44780U_CONN_MODE is incorrect
#endif

#if (HD44780U_FONT != HD44780U_USE_ONLY_5X8_FONT) && \
	(HD44780U_FONT != HD44780U_USE_ONLY_5X10_FONT) && \
	(HD44780U_FONT != HD44780U_USE_BOTH_FONTS)
#error Define HD44780U_FONT is incorrect
#endif

#if (HD44780U_ROW_COUNT != HD44780U_USE_ONLY_1_ROW_COUNT) && \
	(HD44780U_ROW_COUNT != HD44780U_USE_ONLY_2_ROW_COUNT) && \
	(HD44780U_ROW_COUNT != HD44780U_USE_BOTH_ROW_COUNTS)
#error Define HD44780U_ROW_COUNT is incorrect
#endif

#if (HD44780U_ROW_LENGHT != HD44780U_USE_ONLY_8_ROW_LENGHT) && \
	(HD44780U_ROW_LENGHT != HD44780U_USE_ONLY_16_ROW_LENGHT) && \
	(HD44780U_ROW_LENGHT != HD44780U_USE_BOTH_ROW_LENGHTS)
#error Define HD44780U_ROW_LENGHT is incorrect
#endif

#define COMMAND_CLEAR 0x01u
#define COMMAND_CLEAR_DELAY_MS 1600ul

#define COMMAND_RET_HOME 0x02u
#define COMMAND_RET_HOME_DELAY_MS 1600ul

#define COMMAND_SET_ENTRY_MODE 0x04u
#define COMMAND_SET_ENTRY_MODE_SHIFT_MASK 0x01u // 0 - disable shift, 1 - enable shift
#define COMMAND_SET_ENTRY_MODE_DIRECTION_MASK 0x02u // 0 - deinc, 1 - inc
#define COMMAND_SET_ENTRY_MODE_DELAY_MS 45ul

#define COMMAND_SET_DISPLAY_CNTR 0x08u
#define COMMAND_SET_DISPLAY_CNTR_BLINK_MASK 0x01u
#define COMMAND_SET_DISPLAY_CNTR_CURSOR_MASK 0x02u
#define COMMAND_SET_DISPLAY_CNTR_DISPLAY_MASK 0x04u // 0 - off, 1 - on
#define COMMAND_SET_DISPLAY_CNTR_DELAY_MS 45ul

#define COMMAND_MOVE 0x10u
#define COMMAND_MOVE_DIRECTION_MASK 0x04u // 0 - left, 1 - right
#define COMMAND_MOVE_TYPE_MASK 0x08u // 0 - cursor shift, 1 - display move
#define COMMAND_MOVE_DELAY_MS 45ul

#define COMMAND_SET_FUCTION 0x20u
#define COMMAND_SET_FUCTION_FONT_MASK 0x04u // 0 - 5x8, 1 - 5x10
#define COMMAND_SET_FUCTION_LINES_MASK 0x08u // 0 - 1 line, 1 - 2 lines
#define COMMAND_SET_FUCTION_DATA_LEN_MASK 0x10u // 0 - 4 pins, 1 - 8 pins
#define COMMAND_SET_FUCTION_DELAY_MS 45ul

#define COMMAND_SET_POS 0x80u
#define COMMAND_SET_POS_LINE_MASK 0x40u // 0 - first line, 1 - 2nd line
#define COMMAND_SET_POS_DELAY_MS 45ul

#define WRITE_DATA_DELAY_MS 45ul

#if (HD44780U_CONN_MODE == HD44780U_USE_ONLY_HALF_CONN_MODE)
#define __GET_FUNCTION_SET_DATA_LEN_MASK(handler) (0)
#elif (HD44780U_CONN_MODE == HD44780U_USE_ONLY_FULL_CONN_MODE)
#define __GET_FUNCTION_SET_DATA_LEN_MASK(handler) (COMMAND_SET_FUCTION_DATA_LEN_MASK)
#elif (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES)
#define __GET_FUNCTION_SET_DATA_LEN_MASK(handler) (((handler)->connMode == Full) ? COMMAND_SET_FUCTION_DATA_LEN_MASK : 0)
#endif

#if (HD44780U_FONT == HD44780U_USE_ONLY_5X8_FONT)
#define __GET_FUNCTION_SET_FONT_MASK(handler) (0)
#elif (HD44780U_FONT == HD44780U_USE_ONLY_5X10_FONT)
#define __GET_FUNCTION_SET_FONT_MASK(handler) (COMMAND_SET_FUCTION_FONT_MASK)
#elif (HD44780U_FONT == HD44780U_USE_BOTH_FONTS)
#define __GET_FUNCTION_SET_FONT_MASK(handler) (((handler)->font == Size5x10) ? COMMAND_SET_FUCTION_FONT_MASK : 0)
#endif


#if (HD44780U_ROW_COUNT == HD44780U_USE_ONLY_1_ROW_COUNT)
#define __GET_FUNCTION_SET_LINES_MASK(handler) (0)
#elif (HD44780U_ROW_COUNT == HD44780U_USE_ONLY_2_ROW_COUNT)
#define __GET_FUNCTION_SET_LINES_MASK(handler) (COMMAND_SET_FUCTION_LINES_MASK)
#elif (HD44780U_ROW_COUNT == HD44780U_USE_BOTH_ROW_COUNTS)
#define __GET_FUNCTION_SET_LINES_MASK(handler) (((handler)->rowCount == TwoRows) ? COMMAND_SET_FUCTION_LINES_MASK : 0)
#endif


#if (HD44780U_CONN_MODE == HD44780U_USE_ONLY_HALF_CONN_MODE)
#define __GET_DATA_SIZE(handler) (4u)
#elif (HD44780U_CONN_MODE == HD44780U_USE_ONLY_FULL_CONN_MODE)
#define __GET_DATA_SIZE(handler) (8u)
#elif (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES)
#define __GET_DATA_SIZE(handler) ((Half == (handler)->connMode) ? 4 : 8)
#endif

#ifdef HD44780U_GPIO_WRITE
#define __SET_EN(handler, state) (HD44780U_GPIO_WRITE(&(handler)->en, (state)))
#define __SET_RW(handler, state) (HD44780U_GPIO_WRITE(&(handler)->rw, (state)))
#define __SET_RS(handler, state) (HD44780U_GPIO_WRITE(&(handler)->rs, (state)))

#ifndef HD44780U_GPIO_WRITE_ARR
static void SetData(hd44780u_t* pDisplay, uint8_t byte)
{
	for (size_t i = 0; i < __GET_DATA_SIZE(pDisplay); i++)
	{
		HD44780U_GPIO_WRITE(&pDisplay->dataPins[i], (byte & 1));
		byte >>= 1;
	}
}
#define __SET_DATA(handler, data) (SetData((handler), (data)))
#else
#define __SET_DATA(handler, data) (HD44780U_GPIO_WRITE_ARR((handler)->dataPins, __GET_DATA_SIZE(handler), (data)))
#endif

#else
#define __SET_EN(handler, state) ((handler)->setEN(state))
#define __SET_RW(handler, state) ((handler)->setRW(state))
#define __SET_RS(handler, state) ((handler)->setRS(state))
#define __SET_DATA(handler, data) ((handler)->setData(data))
#endif

#if ((HD44780U_CONN_MODE == HD44780U_USE_ONLY_HALF_CONN_MODE) || (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES))
static void SendHalfByte(hd44780u_t* pDisplay, uint8_t byte)
{
	__SET_EN(pDisplay, true);
	__SET_DATA(pDisplay, (byte & 0x0F));
	HD44780UDelayUS(1);
	__SET_EN(pDisplay, false);
	HD44780UDelayUS(1);
}
#endif

#define __SEND_BY_HALF_CONN_MODE(handler, byte) \
	SendHalfByte((handler), ((byte) >> 4));     \
	SendHalfByte((handler), (byte));

#define __SEND_BY_FULL_CONN_MODE(handler, byte) \
	__SET_EN(handler, true);                     \
	__SET_DATA(handler, (byte));                 \
	HD44780UDelayMS(1);                         \
	__SET_EN(handler, false);                    \
	HD44780UDelayMS(1);

static void SendByte(hd44780u_t* pDisplay, uint8_t byte)
{
#if (HD44780U_CONN_MODE == HD44780U_USE_ONLY_HALF_CONN_MODE)
	__SEND_BY_HALF_CONN_MODE(pDisplay, byte);
#elif (HD44780U_CONN_MODE == HD44780U_USE_ONLY_FULL_CONN_MODE)
	__SEND_BY_FULL_CONN_MODE(pDisplay, byte);
#elif (HD44780U_CONN_MODE == HD44780U_USE_BOTH_CONN_MODES)
	if (pDisplay->connMode == Half)
	{
		__SEND_BY_HALF_CONN_MODE(pDisplay, byte);
	}
	else
	{
		__SEND_BY_FULL_CONN_MODE(pDisplay, byte);
	}
#endif
}

static void WriteInstructionWithDelay(hd44780u_t* pDisplay, uint8_t instruction, uint32_t delay)
{
	__SET_RS(pDisplay, false);
	__SET_RW(pDisplay, false);

	SendByte(pDisplay, instruction);

	if (delay > 0)
	{
		HD44780UDelayUS(delay);
	}
}

static void WriteData(hd44780u_t* pDisplay, uint8_t data)
{
	__SET_RS(pDisplay, true);
	__SET_RW(pDisplay, false);

	SendByte(pDisplay, data);
	HD44780UDelayUS(WRITE_DATA_DELAY_MS);
}

void HD44780USetPosition(hd44780u_t* pDisplay, uint8_t position)
{
	if (position < (__GET_ROW_COUNT(pDisplay) * __GET_ROW_LENGHT(pDisplay)))
	{
		if (position >= __GET_ROW_LENGHT(pDisplay))
		{
			position -= __GET_ROW_LENGHT(pDisplay);
			position |= COMMAND_SET_POS_LINE_MASK;
		}

		position |= COMMAND_SET_POS;
		WriteInstructionWithDelay(pDisplay, position, COMMAND_SET_POS_DELAY_MS);
	}
}

void HD44780UWriteString(hd44780u_t* pDisplay, const char* str)
{
	HD44780UWriteStringWithOffset(pDisplay, 0, str);
}

void HD44780UWriteStringWithOffset(hd44780u_t* pDisplay, uint8_t offset, const char* str)
{
	HD44780USetPosition(pDisplay, offset);

	for(uint8_t i = 0; (str[i] != 0 && i < 32); i++)
	{
		if (i == __GET_ROW_LENGHT(pDisplay))
		{
			HD44780USetPosition(pDisplay, __GET_ROW_LENGHT(pDisplay));
		}

		WriteData(pDisplay, (uint8_t)str[i]);
	}
}

void HD44780UClear(hd44780u_t* pDisplay)
{
	WriteInstructionWithDelay(pDisplay, COMMAND_CLEAR, COMMAND_CLEAR_DELAY_MS);
}

void HD44780UReturnHome(hd44780u_t* pDisplay)
{
	WriteInstructionWithDelay(pDisplay, COMMAND_RET_HOME, COMMAND_RET_HOME_DELAY_MS);
}

void HD44780USetCursor(hd44780u_t* pDisplay)
{
	uint8_t command = COMMAND_SET_DISPLAY_CNTR | COMMAND_SET_DISPLAY_CNTR_DISPLAY_MASK;

	if (pDisplay->cursorState == true)
	{
		command |= COMMAND_SET_DISPLAY_CNTR_CURSOR_MASK;

		if (pDisplay->blinkCursorState == true)
		{
			command |= COMMAND_SET_DISPLAY_CNTR_BLINK_MASK;
		}
	}

	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_DISPLAY_CNTR_DELAY_MS);
}

void HD44780USetEntryMode(hd44780u_t* pDisplay)
{
	WriteInstructionWithDelay(pDisplay, COMMAND_SET_ENTRY_MODE | COMMAND_SET_ENTRY_MODE_DIRECTION_MASK, COMMAND_SET_ENTRY_MODE_DELAY_MS);
}

void HD44780UInit(hd44780u_t* pDisplay)
{
	__SET_RS(pDisplay, false);
	__SET_RW(pDisplay, false);
	//SendHalfByte(pDisplay, 0x03);
	HD44780UDelayUS(40);

	uint8_t command;

	command = COMMAND_SET_FUCTION;
	command |= __GET_FUNCTION_SET_DATA_LEN_MASK(pDisplay);
	command |= __GET_FUNCTION_SET_FONT_MASK(pDisplay);
	command |= __GET_FUNCTION_SET_LINES_MASK(pDisplay);

	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_FUCTION_DELAY_MS);
	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_FUCTION_DELAY_MS);

	HD44780USetCursor(pDisplay);
	HD44780UClear(pDisplay);
	HD44780USetEntryMode(pDisplay);
	HD44780UReturnHome(pDisplay);
}
