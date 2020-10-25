#include "ILI9341.h"

uint16_t MAX_X = X_max;
uint16_t MAX_Y = Y_max;
uint16_t curr_y = 0;

void ILI9341_reset()
{
    RST_ACTIVE;
    HAL_Delay(15);
    RST_IDLE;
    HAL_Delay(15);
}


void write_bus(uint8_t value)
{
    TFT_DATA->BSRR = ((~value) << 16) | (value);

    WR_STROBE;
}


void write(uint8_t value, uint8_t mode)
{
    if (mode == DAT)
        CD_DATA;
    else
        CD_COMMAND;

    CS_ACTIVE;
    write_bus(value);
    CS_IDLE;
}


void write_REG_DATA(uint8_t reg, uint8_t data_value)
{
    write(reg, CMD);
    write(data_value, DAT);
}

GPIO_InitTypeDef GPIO_InitStruct = {0};
void setWriteDataBus(void) {
    // set the pins to output mode
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TFT_DATA, &GPIO_InitStruct);
}

void setReadDataBus(void) {
    //set the pins to input mode
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TFT_DATA, &GPIO_InitStruct);
}

void ILI9341_init()
{
    ILI9341_GPIO_init();

    ILI9341_reset();
    write(ILI9341_RESET, CMD);
    HAL_Delay(60);

    write(ILI9341_DISPLAY_OFF, CMD);

    write(ILI9341_POWERA, CMD);
    write(0x39, DAT);
    write(0x2C, DAT);
    write(0x00, DAT);
    write(0x34, DAT);
    write(0x02, DAT);

    write(ILI9341_POWERB, CMD);
    write(0x00, DAT);
    write(0xC1, DAT);
    write(0x30, DAT);

    write(ILI9341_DTCA, CMD);
    write(0x85, DAT);
    write(0x00, DAT);
    write(0x78, DAT);

    write(ILI9341_DTCB, CMD);
    write(0x00, DAT);
    write(0x00, DAT);

    write(ILI9341_POWER_SEQ, CMD);
    write(0x64, DAT);
    write(0x03, DAT);
    write(0x12, DAT);
    write(0x81, DAT);

    write(ILI9341_PRC, CMD);
    write(0x20, DAT);

    write(ILI9341_POWER1, CMD);
    write(0x23, DAT);

    write(ILI9341_POWER2, CMD);
    write(0x10, DAT);

    write(ILI9341_VCOM1, CMD);
    write(0x3E, DAT);
    write(0x28, DAT);

    write(ILI9341_VCOM2, CMD);
    write(0x86, DAT);

    write(ILI9341_MAC, CMD);
    write(0x48, DAT);

    write(ILI9341_PIXEL_FORMAT, CMD);
    write(0x55, DAT);

    write(ILI9341_FRC, CMD);
    write(0x00, DAT);
    write(0x18, DAT);

    write(ILI9341_DFC, CMD);
    write(0x08, DAT);
    write(0x82, DAT);
    write(0x27, DAT);

    write(ILI9341_3GAMMA_EN, CMD);
    write(0x00, DAT);

    write(ILI9341_COLUMN_ADDR, CMD);
    write(0x00, DAT);
    write(0x00, DAT);
    write(0x00, DAT);
    write(0xEF, DAT);

    write(ILI9341_PAGE_ADDR, CMD);
    write(0x00, DAT);
    write(0x00, DAT);
    write(0x01, DAT);
    write(0x3F, DAT);

    write(ILI9341_GAMMA, CMD);
    write(0x01, DAT);

    write(ILI9341_PGAMMA, CMD);
    write(0x0F, DAT);
    write(0x31, DAT);
    write(0x2B, DAT);
    write(0x0C, DAT);
    write(0x0E, DAT);
    write(0x08, DAT);
    write(0x4E, DAT);
    write(0xF1, DAT);
    write(0x37, DAT);
    write(0x07, DAT);
    write(0x10, DAT);
    write(0x03, DAT);
    write(0x0E, DAT);
    write(0x09, DAT);
    write(0x00, DAT);

    write(ILI9341_NGAMMA, CMD);
    write(0x00, DAT);
    write(0x0E, DAT);
    write(0x14, DAT);
    write(0x03, DAT);
    write(0x11, DAT);
    write(0x07, DAT);
    write(0x31, DAT);
    write(0xC1, DAT);
    write(0x48, DAT);
    write(0x08, DAT);
    write(0x0F, DAT);
    write(0x0C, DAT);
    write(0x31, DAT);
    write(0x36, DAT);
    write(0x0F, DAT);

    write(ILI9341_SLEEP_OUT, CMD);
    HAL_Delay(100);

    write(ILI9341_DISPLAY_ON, CMD);
    write(ILI9341_GRAM, CMD);
}


void ILI9341_GPIO_init()
{
    setWriteDataBus();

    WR_ACTIVE;
    RD_ACTIVE;
    CD_DATA;
    CS_IDLE;
    RST_IDLE;

    HAL_Delay(10);
}


void ILI9341_set_rotation(uint8_t value)
{
    write(ILI9341_MAC, CMD);

    switch(value) {
        case PORTRAIT_1: {
            write(0x58, DAT);
            break;
        }
        case PORTRAIT_2: {
            write(0x88, DAT);
            break;
        }
        case LANDSCAPE_1: {
            write(0x28, DAT);
            break;
        }
        case LANDSCAPE_2: {
            write(0xE8, DAT);
            break;
        }
    }

    if((value == PORTRAIT_1) || (value == PORTRAIT_2)) {
        MAX_X = X_max;
        MAX_Y = Y_max;
    }

    if((value == LANDSCAPE_1) || (value == LANDSCAPE_2)) {
        MAX_X = Y_max;
        MAX_Y = X_max;
    }
}

void ILI9341_set_display_window(uint16_t x_pos1, uint16_t y_pos1, uint16_t x_pos2, uint16_t y_pos2)
{
    write(ILI9341_COLUMN_ADDR, CMD);
    write((x_pos1 >> 8), DAT);
    write(x_pos1, DAT);
    write((x_pos2 >> 8), DAT);
    write(x_pos2, DAT);

    write(ILI9341_PAGE_ADDR, CMD);
    write((y_pos1 >> 8), DAT);
    write(y_pos1, DAT);
    write((y_pos2 >> 8), DAT);
    write(y_pos2, DAT);

    write(ILI9341_GRAM, CMD);
}

void ILI9341_fill(uint16_t colour)
{
    unsigned long index = pixels;

    ILI9341_set_display_window(0, 0, (MAX_X - 1), (MAX_Y - 1));

    CD_DATA;
    CS_ACTIVE;
    uint8_t hi = colour >> 8, lo = colour;
    while(index) {
        write_bus(hi);
        write_bus(lo);
        index--;
    }
    CS_IDLE;
}

void ILI9341_fill_area(int x1, int y1, int x2, int y2, uint16_t colour)
{
    unsigned long index = 0x00000000;

    if(x1 > x2) {
        swap(&x1, &x2);
    }
    if(y1 > y2) {
        swap(&y1, &y2);
    }

    index = (x2 - x1);
    index *= (y2 - y1);

    ILI9341_set_display_window(x1, y1, (x2 - 1), (y2 - 1));

    CD_DATA;
    CS_ACTIVE;
    uint8_t hi = colour >> 8, lo = colour;
    while(index) {
        write_bus(hi);
        write_bus(lo);
        index--;
    }
    CS_IDLE;
}

uint16_t ILI9341_BGR2RGB(uint16_t colour)
{
    uint16_t r = 0x0000;
    uint16_t g = 0x0000;
    uint16_t b = 0x0000;
    uint16_t rgb_colour = 0x0000;

    b = ((colour >> 0)  & 0x1F);
    g = ((colour >> 5)  & 0x3F);
    r = ((colour >> 11) & 0x1F);

    rgb_colour = ((b << 11) + (g << 5) + (r << 0));

    return rgb_colour;
}

uint16_t RGB565_converter(uint8_t r, uint8_t g, uint8_t b)
{
    return (((((uint16_t)r) >> 3) << 11) | ((((uint16_t)g) >> 2) << 5) | (((uint16_t)b) >> 3));
}

void swap(int *a, int *b)
{
    int temp = 0;

    temp = *b;
    *b = *a;
    *a = temp;
}

void ILI9341_draw_pixel(uint16_t x_pos, uint16_t y_pos, uint16_t colour)
{
    ILI9341_set_display_window(x_pos, y_pos, x_pos, y_pos);
    write(colour >> 8, DAT);
    write(colour, DAT);
}

void ILI9341_draw_point(uint16_t x_pos, uint16_t y_pos, uint8_t pen_width, uint16_t colour)
{
    ILI9341_draw_circle(x_pos, y_pos, pen_width, YES, colour);
}

void ILI9341_draw_line(int x1, int y1, int x2, int y2, uint16_t colour)
{
    int dx = 0x0000;
    int dy = 0x0000;
    int stepx = 0x0000;
    int stepy = 0x0000;
    int fraction = 0x0000;

    dy = (y2 - y1);
    dx = (x2 - x1);

    if(dy < 0) {
        dy = -dy;
        stepy = -1;
    } else {
        stepy = 1;
    }

    if(dx < 0) {
        dx = -dx;
        stepx = -1;
    } else {
        stepx = 1;
    }

    dx <<= 0x01;
    dy <<= 0x01;

    ILI9341_draw_pixel(x1, y1, colour);

    if(dx > dy){
        fraction = (dy - (dx >> 1));
        while(x1 != x2) {
            if(fraction >= 0) {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            ILI9341_draw_pixel(x1, y1, colour);
        }
    } else {
        fraction = (dx - (dy >> 1));

        while(y1 != y2) {
            if (fraction >= 0) {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            ILI9341_draw_pixel(x1, y1, colour);
        }
    }
}

void ILI9341_draw_v_line(int x1, int y1, int y2, uint16_t colour)
{

    if(y1 > y2) {
        swap(&y1, &y2);
    }

    while(y2 > (y1 - 1)) {
        ILI9341_draw_pixel(x1, y2, colour);
        y2--;
    }
}

void ILI9341_draw_h_line(int x1, int x2, int y1, uint16_t colour)
{

    if(x1 > x2) {
        swap(&x1, &x2);
    }

    while(x2 > (x1 - 1)) {
        ILI9341_draw_pixel(x2, y1, colour);
        x2--;
    }
}

void ILI9341_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint8_t fill, uint16_t colour)
{
    int a = 0;
    int b = 0;
    int sa = 0;
    int sb = 0;
    int yp = 0;
    int last = 0;
    int dx12 = 0;
    int dx23 = 0;
    int dx13 = 0;
    int dy12 = 0;
    int dy23 = 0;
    int dy13 = 0;

    switch(fill) {
        case YES: {
            if(y1 > y2) {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }
            if(y2 > y3) {
                swap(&y3, &y2);
                swap(&x3, &x2);
            }
            if(y1 > y2) {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }

            if(y1 == y3) {
                a = b = x1;

                if(x2 < a) {
                    a = x2;
                } else if(x2 > b) {
                    b = x2;
                }
                if(x2 < a) {
                    a = x3;
                } else if(x3 > b) {
                    b = x3;
                }

                ILI9341_draw_h_line(a, (a + (b - (a + 1))), y1, colour);
                return;
            }

            dx12 = (x2 - x1);
            dy12 = (y2 - y1);
            dx13 = (x3 - x1);
            dy13 = (y3 - y1);
            dx23 = (x3 - x2);
            dy23 = (y3 - y2);
            sa = 0,
                    sb = 0;

            if(y2 == y3) {
                last = y2;
            } else {
                last = (y2 - 1);
            }

            for (yp = y1; yp <= last; yp++) {
                a = (x1 + (sa / dy12));
                b = (x1 + (sb / dy13));
                sa += dx12;
                sb += dx13;
                if(a > b) {
                    swap(&a, &b);
                }
                ILI9341_draw_h_line(a, (a + (b - (a + 1))), yp, colour);
            }

            sa = (dx23 * (yp - y2));
            sb = (dx13 * (yp - y1));
            for(; yp <= y3; yp++) {
                a = (x2 + (sa / dy23));
                b = (x1 + (sb / dy13));
                sa += dx23;
                sb += dx13;

                if(a > b) {
                    swap(&a, &b);
                }
                ILI9341_draw_h_line(a, (a + (b - (a + 1))), yp, colour);
            }


            break;
        }
        default: {
            ILI9341_draw_line(x1, y1, x2, y2, colour);
            ILI9341_draw_line(x2, y2, x3, y3, colour);
            ILI9341_draw_line(x3, y3, x1, y1, colour);
            break;
        }
    }
}

void ILI9341_draw_rectangle(int x1, int y1, int x2, int y2, uint8_t fill,
                            uint8_t type, uint16_t colour, uint16_t back_colour)
{
    int i = 0x0000;
    int xmin = 0x0000;
    int xmax = 0x0000;
    int ymin = 0x0000;
    int ymax = 0x0000;

    switch(fill) {
        case YES: {
            if(x1 < x2) {
                xmin = x1;
                xmax = x2;
            } else {
                xmin = x2;
                xmax = x1;
            }

            if(y1 < y2) {
                ymin = y1;
                ymax = y2;
            } else {
                ymin = y2;
                ymax = y1;
            }

            for(; xmin <= xmax; ++xmin) {
                for(i = ymin; i <= ymax; ++i) {
                    ILI9341_draw_pixel(xmin, i, colour);
                }
            }

            break;
        }
        default: {
            ILI9341_draw_v_line(x1, y1, y2, colour);
            ILI9341_draw_v_line(x2, y1, y2, colour);
            ILI9341_draw_h_line(x1, x2, y1, colour);
            ILI9341_draw_h_line(x1, x2, y2, colour);
            break;
        }
    }

    if(type != SQUARE) {
        ILI9341_draw_pixel(x1, y1, back_colour);
        ILI9341_draw_pixel(x1, y2, back_colour);
        ILI9341_draw_pixel(x2, y1, back_colour);
        ILI9341_draw_pixel(x2, y2, back_colour);
    }
}

void ILI9341_draw_h_bar(int x1, int x2, int y1, int bar_width, int bar_value,
                    uint16_t border_colour, uint16_t bar_colour, uint16_t back_colour, uint8_t border)
{
    switch(border) {
        case YES: {
            ILI9341_draw_rectangle((x1 + 1), (y1 + 1), (x1 + bar_value), (y1 + bar_width - 1), YES, SQUARE, bar_colour, back_colour);
            ILI9341_draw_rectangle((x2 - 1), (y1 + 1), (x1 + bar_value + 1), (y1 + bar_width - 1), YES, SQUARE, back_colour, back_colour);
            ILI9341_draw_rectangle(x1, y1, x2, (y1 + bar_width), NO, SQUARE, border_colour, back_colour);
            break;
        }
        default: {
            ILI9341_draw_rectangle(x1, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, bar_colour, back_colour);
            ILI9341_draw_rectangle(x2, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, back_colour, back_colour);
            break;
        }
    }
}

void ILI9341_draw_v_bar(int x1, int y1, int y2, int bar_width, int bar_value,
                    uint16_t border_colour, uint16_t bar_colour, uint16_t back_colour, uint8_t border)
{
    switch(border) {
    case YES: {
        ILI9341_draw_rectangle((x1 + 1), (y2 - 1), (x1 + bar_width - 1), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
        ILI9341_draw_rectangle((x1 + 1), (y2 - bar_value - 1), (x1 + bar_width - 1), (y1 + 1), YES, SQUARE, back_colour, back_colour);
        ILI9341_draw_rectangle(x1, y1, (x1 + bar_width), y2, NO, SQUARE, border_colour, back_colour);
        break;
    }
    default: {
        ILI9341_draw_rectangle(x1, y2, (x1 + bar_width), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
        ILI9341_draw_rectangle(x1, (y2 - bar_value), (x1 + bar_width), y1, YES, SQUARE, back_colour, back_colour);
        break;
    }
    }
}

void ILI9341_draw_circle(int xc, int yc, int radius, uint8_t fill, uint16_t colour)
{
    int a = 0x0000;
    int b = 0x0000;
    int p = 0x0000;

    b = radius;
    p = (1 - b);

    do {
        switch(fill) {
        case YES: {
            ILI9341_draw_line((xc - a), (yc + b), (xc + a), (yc + b), colour);
            ILI9341_draw_line((xc - a), (yc - b), (xc + a), (yc - b), colour);
            ILI9341_draw_line((xc - b), (yc + a), (xc + b), (yc + a), colour);
            ILI9341_draw_line((xc - b), (yc - a), (xc + b), (yc - a), colour);
            break;
        }
        default: {
            ILI9341_draw_pixel((xc + a), (yc + b), colour);
            ILI9341_draw_pixel((xc + b), (yc + a), colour);
            ILI9341_draw_pixel((xc - a), (yc + b), colour);
            ILI9341_draw_pixel((xc - b), (yc + a), colour);
            ILI9341_draw_pixel((xc + b), (yc - a), colour);
            ILI9341_draw_pixel((xc + a), (yc - b), colour);
            ILI9341_draw_pixel((xc - a), (yc - b), colour);
            ILI9341_draw_pixel((xc - b), (yc - a), colour);
            break;
        }
        }

        if(p < 0) {
            p += (0x03 + (0x02 * a++));
        } else {
            p += (0x05 + (0x02 * ((a++) - (b--))));
        }
    } while(a <= b);
}

void ILI9341_draw_font_pixel(uint16_t x_pos, uint16_t y_pos, uint16_t colour, uint8_t pixel_size)
{
    volatile uint8_t i = (pixel_size * pixel_size);

    ILI9341_set_display_window(x_pos, y_pos, (x_pos + pixel_size - 1), (y_pos + pixel_size - 1));

    while(i > 0) {
        write(colour >> 8, DAT);
        write(colour, DAT);
        i--;
    }
}

void ILI9341_print_char(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                        uint16_t colour, uint16_t back_colour, char ch)
{
    volatile uint8_t i = 0x00;
    volatile uint8_t j = 0x00;
    volatile uint8_t value = 0x00;

    if(font_size <= 0) {
        font_size = 1;
    }

    if(x_pos < font_size) {
        x_pos = font_size;
    }

    if (font_size == 1) {
        for(i = 0x00; i < 0x05; i++) {
            value = 0x0000;
            value = ((font[((uint8_t)ch) - 0x20][i]));
            for(j = 0x00; j < 0x08; j++) {
                if(((value >> j) & 0x01) != 0x00) {
                    ILI9341_draw_font_pixel(x_pos, y_pos, colour, font_size);
                } else {
                    ILI9341_draw_font_pixel(x_pos, y_pos, back_colour, font_size);
                }

                y_pos += font_size;
            }

            y_pos -= (font_size << 0x03);
            x_pos += font_size;
        }
    } else if (font_size == 2) {
        for(i = 0x00; i < 0x10; i++) {
            value = 0x0000;
            value = ((ascii_8x16[((uint8_t)ch) - 0x20][i]));
            for(j = 0x00; j < 0x08; j++) {
                if(((value >> j) & 0x01) != 0x00) {
                    ILI9341_draw_font_pixel(x_pos, y_pos, colour, 1);
                } else {
                    ILI9341_draw_font_pixel(x_pos, y_pos, back_colour, 1);
                }

                x_pos -= 1;
            }

            x_pos += (1 << 0x03);
            y_pos += 1;
        }
    }
}


void ILI9341_print_str(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                        uint16_t colour, uint16_t back_colour, char *ch)
{
    do {
        switch (*ch) {
            case '\t': {
                for (int i = 0; i < 4; i++) {
                    ILI9341_print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
                    x_pos += (font_size * 0x06);
                }
            }
                break;
            case '\n': {
                if (font_size == 1) {
                    curr_y += 10;
                    y_pos += 10;
                } else {
                    curr_y += 16;
                    y_pos += 16;
                }
                if (curr_y > MAX_Y) {
                    curr_y = 0;
                    y_pos = 0;
                }
            }
                break;
            default: {
                ILI9341_print_char(x_pos, y_pos, font_size, colour, back_colour, *ch);
                x_pos += (font_size * 0x06);
            }
                break;
        }
        ch++;
    } while (((*ch >= 0x20) && (*ch <= 0x7F)) || (*ch == '\t') || (*ch == '\n'));
}

void ILI9341_print_c(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                    uint16_t colour, uint16_t back_colour, int value)
{
    uint8_t ch[4];

    if(value < 0x00) {
        ch[0] = 0x2D;
        value = -value;
    } else {
        ch[0] = 0x20;
    }

    if((value > 99) && (value <= 999)) {
        ch[1] = ((value / 100) + 0x30);
        ch[2] = (((value % 100) / 10) + 0x30);
        ch[3] = ((value % 10) + 0x30);

    } else if((value > 9) && (value <= 99)) {
        ch[1] = (((value % 100) / 10) + 0x30);
        ch[2] = ((value % 10) + 0x30);
        ch[3] = 0x20;

    } else if((value >= 0) && (value <= 9)) {
        ch[1] = ((value % 10) + 0x30);
        ch[2] = 0x20;
        ch[3] = 0x20;
    }

    ILI9341_print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}

void ILI9341_print_i(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                    uint16_t colour, uint16_t back_colour, int value)
{
    uint8_t ch[6];

    if(value < 0) {
        ch[0] = 0x2D;
        value = -value;
    } else {
        ch[0] = 0x20;
    }

    if(value > 9999) {
        ch[1] = ((value / 10000) + 0x30);
        ch[2] = (((value % 10000)/ 1000) + 0x30);
        ch[3] = (((value % 1000) / 100) + 0x30);
        ch[4] = (((value % 100) / 10) + 0x30);
        ch[5] = ((value % 10) + 0x30);

    } else if((value > 999) && (value <= 9999)) {
        ch[1] = (((value % 10000)/ 1000) + 0x30);
        ch[2] = (((value % 1000) / 100) + 0x30);
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
        ch[5] = 0x20;

    } else if((value > 99) && (value <= 999)) {
        ch[1] = (((value % 1000) / 100) + 0x30);
        ch[2] = (((value % 100) / 10) + 0x30);
        ch[3] = ((value % 10) + 0x30);
        ch[4] = 0x20;
        ch[5] = 0x20;

    } else if((value > 9) && (value <= 99)) {
        ch[1] = (((value % 100) / 10) + 0x30);
        ch[2] = ((value % 10) + 0x30);
        ch[3] = 0x20;
        ch[4] = 0x20;
        ch[5] = 0x20;

    } else {
        ch[1] = ((value % 10) + 0x30);
        ch[2] = 0x20;
        ch[3] = 0x20;
        ch[4] = 0x20;
        ch[5] = 0x20;
    }

    ILI9341_print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}

void ILI9341_print_d(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                    uint16_t colour, uint16_t back_colour, uint16_t value, uint8_t points)
{
    volatile uint8_t ch[5];

    ch[0] = 0x2E;
    ch[1] = ((value / 1000) + 0x30);

    if(points > 1) {
        ch[2] = (((value % 1000) / 100) + 0x30);

        if(points > 2) {
            ch[3] = (((value % 100) / 10) + 0x30);

            if(points > 3) {
                ch[4] = ((value % 10) + 0x30);
            }
        }
    }

    ILI9341_print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
}

void ILI9341_print_f(uint16_t x_pos, uint16_t y_pos, uint8_t font_size,
                    uint16_t colour, uint16_t back_colour, float value, uint8_t points)
{
    long tmp = 0x00000000;

    tmp = value;
    ILI9341_print_i(x_pos, y_pos, font_size, colour, back_colour, tmp);
    tmp = ((value - tmp) * 10000);

    if(tmp < 0) {
        tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000)) {
        ILI9341_print_d((x_pos + (36 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
    } else if((value >= 1000) && (value < 10000)) {
        ILI9341_print_d((x_pos + (30 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
    } else if((value >= 100) && (value < 1000)) {
        ILI9341_print_d((x_pos + (24 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
    } else if((value >= 10) && (value < 100)) {
        ILI9341_print_d((x_pos + (18 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
    } else if(value < 10) {
        ILI9341_print_d((x_pos + (12 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);

        if((value) < 0) {
            ILI9341_print_char(x_pos, y_pos, font_size, colour, back_colour, 0x2D);
        } else {
            ILI9341_print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
        }
    }
}

void ILI9341_draw_bmp(int x_pos1, int y_pos1, int x_pos2, int y_pos2, const uint16_t *bitmap)
{
    unsigned long size = 0x00000000;
    unsigned long index = 0x00000000;

    if(x_pos1 > x_pos2) {
        swap(&x_pos1, &x_pos2);
    }

    if(y_pos1 > y_pos2) {
        swap(&y_pos1, &y_pos2);
    }

    size = (y_pos2 - y_pos1);
    size *= (x_pos2 - x_pos1);
    //size <<= 1;

    ILI9341_set_display_window(x_pos1, y_pos1, (x_pos2 - 1), (y_pos2 - 1));

    for(index = 0; index < size; index++) {
        write(*bitmap >> 8, DAT);
        write(*bitmap++, DAT);
    }
}
