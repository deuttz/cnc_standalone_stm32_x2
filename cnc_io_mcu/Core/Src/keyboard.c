#include "keyboard.h"

#include "main.h"

#if !defined(COL0_Pin) || !defined(COL1_Pin) || !defined(COL2_Pin) || !defined(COL3_Pin) || \
    !defined(ROW0_Pin) || !defined(ROW1_Pin) || !defined(ROW2_Pin) || !defined(ROW3_Pin) || \
    !defined(COL0_GPIO_Port) || !defined(COL1_GPIO_Port) || !defined(COL2_GPIO_Port) || !defined(COL3_GPIO_Port) || \
    !defined(ROW0_GPIO_Port) || !defined(ROW1_GPIO_Port) || !defined(ROW2_GPIO_Port) || !defined(ROW3_GPIO_Port)
    #error "Define input (Rows) and output (Columns) pins for keyboard before using this module!"
#endif

void Keyboard_init(void)
{
    // map CubeMX configurator pin names to this module's pin names
}

volatile uint8_t key_buffer[6], __key_buf_index = 0;

static void ___put_key(uint8_t key)
{
    if (__key_buf_index >= sizeof(key_buffer))
        return;
    key_buffer[__key_buf_index++] = key;
}

void Keyboard_scan_next(void)
{
    static uint8_t scan_stage = 0;
    if (++scan_stage >= 8)
        scan_stage = 0;
    uint8_t row = scan_stage >> 1;

    // on even stage - set pin
    if ((scan_stage & 0x01) == 0) {
        COL0_GPIO_Port->BRR = COL0_Pin;
        COL1_GPIO_Port->BRR = COL1_Pin;
        COL2_GPIO_Port->BRR = COL2_Pin;
        COL3_GPIO_Port->BRR = COL3_Pin;
        switch (row) {
        case 0:
            COL0_GPIO_Port->BSRR = COL0_Pin;
            break;
        case 1:
            COL1_GPIO_Port->BSRR = COL1_Pin;
            break;
        case 2:
            COL2_GPIO_Port->BSRR = COL2_Pin;
            break;
        case 3:
            COL3_GPIO_Port->BSRR = COL3_Pin;
            break;
        }
    // on odd stage - check pins
    } else {
        if (ROW0_GPIO_Port->IDR & ROW0_Pin)
            ___put_key(0x10 | row);
        if (ROW1_GPIO_Port->IDR & ROW1_Pin)
            ___put_key(0x20 | row);
        if (ROW2_GPIO_Port->IDR & ROW2_Pin)
            ___put_key(0x30 | row);
        if (ROW3_GPIO_Port->IDR & ROW3_Pin)
            ___put_key(0x40 | row);
    }
}

int Keyboard_get_key(void)
{
    return __key_buf_index == 0 ? -1 : key_buffer[--__key_buf_index];
}
