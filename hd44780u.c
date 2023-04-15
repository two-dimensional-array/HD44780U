#include <assert.h>
#include "hd44780u.h"

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

__attribute__((weak)) void HD44780UDelayMS(volatile uint32_t micros)
{
	static_assert("Need redefine HD44780UDelayMS function");
}

static void SendHalfByte(hd44780u_t* pDisplay, uint8_t byte)
{
	pDisplay->setEN(true);
	pDisplay->setData(byte & 0x0F);
	HD44780UDelayMS(1);
	pDisplay->setEN(false);
	HD44780UDelayMS(1);
}

static void SendByte(hd44780u_t* pDisplay, uint8_t byte)
{
	if (pDisplay->connMode == Half)
	{
		SendHalfByte(pDisplay, (byte >> 4));
		SendHalfByte(pDisplay, byte);
	}
	else
	{
		pDisplay->setEN(true);
		pDisplay->setData(byte);
		HD44780UDelayMS(1);
		pDisplay->setEN(false);
		HD44780UDelayMS(1);
	}
}

static void WriteInstructionWithDelay(hd44780u_t* pDisplay, uint8_t instruction, uint32_t delay)
{
	pDisplay->setRS(false);
	pDisplay->setRW(false);

	SendByte(pDisplay, instruction);

	if (delay > 0)
	{
		HD44780UDelayMS(delay);
	}
}

static void WriteInstruction(hd44780u_t* pDisplay, uint8_t instruction)
{
	WriteInstructionWithDelay(pDisplay, instruction, 0ul);
}

void HD44780UWriteData(hd44780u_t* pDisplay, uint8_t data)
{
	pDisplay->setRS(true);
	pDisplay->setRW(false);

	SendByte(pDisplay, data);
	HD44780UDelayMS(WRITE_DATA_DELAY_MS);
}

void HD44780USetPosition(hd44780u_t* pDisplay, uint8_t position)
{
	if (position < (pDisplay->rowCount * pDisplay->rowLenght))
	{
		if (position >= pDisplay->rowLenght)
		{
			position -= pDisplay->rowLenght;
			position |= COMMAND_SET_POS_LINE_MASK;
		}

		position |= COMMAND_SET_POS;
		WriteInstructionWithDelay(pDisplay, position, COMMAND_SET_POS_DELAY_MS);
	}
}

void HD44780UWriteString(hd44780u_t* pDisplay, const char* str)
{
	DisplaySetPosition(pDisplay, 0);

	for(uint8_t i = 0; (str[i] != 0 && i < 32); i++)
	{
		if (i == pDisplay->rowLenght)
		{
			DisplaySetPosition(pDisplay, pDisplay->rowLenght);
		}

		DisplayWriteData(pDisplay, (uint8_t)str[i]);
	}
}

void HD44780UInit(hd44780u_t* pDisplay)
{
	pDisplay->setRS(false);
	pDisplay->setRW(false);

	uint8_t command;

	//SendHalfByte(pDisplay, 0x03);
	HD44780UDelayMS(40);

	command = COMMAND_SET_FUCTION;

	if (pDisplay->connMode == Full)
	{
		command |= COMMAND_SET_FUCTION_DATA_LEN_MASK;
	}

	if (pDisplay->font == Size5x10)
	{
		command |= COMMAND_SET_FUCTION_FONT_MASK;
	}

	if (pDisplay->rowCount = 2)
	{
		command = COMMAND_SET_FUCTION_LINES_MASK;
	}
	
	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_FUCTION_DELAY_MS);
	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_FUCTION_DELAY_MS);

	command = COMMAND_SET_DISPLAY_CNTR | COMMAND_SET_DISPLAY_CNTR_BLINK_MASK | COMMAND_SET_DISPLAY_CNTR_CURSOR_MASK | COMMAND_SET_DISPLAY_CNTR_DISPLAY_MASK; 

	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_DISPLAY_CNTR_DELAY_MS);

	command = COMMAND_CLEAR;

	WriteInstructionWithDelay(pDisplay, command, COMMAND_CLEAR_DELAY_MS);

	command = COMMAND_SET_ENTRY_MODE | COMMAND_SET_ENTRY_MODE_DIRECTION_MASK;

	WriteInstructionWithDelay(pDisplay, command, COMMAND_SET_ENTRY_MODE_DELAY_MS);

	command = COMMAND_RET_HOME;

	WriteInstructionWithDelay(pDisplay, command, COMMAND_RET_HOME_DELAY_MS);
}
