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

int Keyboard_scan_next(void)
{
    static uint8_t scan_stage = 0;
    if (++scan_stage >= 8)
        scan_stage = 0;
    uint8_t row = scan_stage >> 1;

    // on even stage - set pin
    if ((scan_stage & 0x01) == 0) {
        ROW0_GPIO_Port->BRR = ROW0_Pin;
        ROW1_GPIO_Port->BRR = ROW1_Pin;
        ROW2_GPIO_Port->BRR = ROW2_Pin;
        ROW3_GPIO_Port->BRR = ROW3_Pin;
        switch (row) {
        case 0:
            ROW0_GPIO_Port->BSRR = ROW0_Pin;
            break;
        case 1:
            ROW1_GPIO_Port->BSRR = ROW1_Pin;
            break;
        case 2:
            ROW2_GPIO_Port->BSRR = ROW2_Pin;
            break;
        case 3:
            ROW3_GPIO_Port->BSRR = ROW3_Pin;
            break;
        }
    // on odd stage - check pins
    } else {
        if (COL0_GPIO_Port->IDR & COL0_Pin) {
            ___put_key(0x10 | row);
            return 1;
        }
        if (COL1_GPIO_Port->IDR & COL1_Pin) {
            ___put_key(0x20 | row);
            return 1;
        }
        if (COL2_GPIO_Port->IDR & COL2_Pin) {
            ___put_key(0x30 | row);
            return 1;
        }
        if (COL3_GPIO_Port->IDR & COL3_Pin) {
            ___put_key(0x40 | row);
            return 1;
        }
    }
    return 0;
}

int Keyboard_get_key(void)
{
    return __key_buf_index == 0 ? -1 : key_buffer[--__key_buf_index];
}
