#pragma once

// TODO: review key names
#define KEY_0 0x13
#define KEY_1 0x30
#define KEY_2 0x10
#define KEY_3 0x40
#define KEY_4 0x31
#define KEY_5 0x11
#define KEY_6 0x41
#define KEY_7 0x32
#define KEY_8 0x12
#define KEY_9 0x42
#define KEY_A 0x20
#define KEY_B 0x21
#define KEY_C 0x22
#define KEY_D 0x23
#define KEY_STAR 0x33
#define KEY_DIES 0x43

/*
 * GPIO setup
 * redundant with CubeMX config
 */
void Keyboard_init(void);

/*
 * Keyboard scan - should be called periodically, e.g. in SysTick_Handler().
 * Inputs will be pushed into stack until getting by kbd_getKey()
 */
void Keyboard_scan_next(void);

/*
 * Keys getter from the inputs LIFO buffer
 */
int Keyboard_get_key(void);

