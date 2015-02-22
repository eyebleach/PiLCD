//PiLCD - LCD Library for Raspberry Pi
//For hd44780 lcd with backpack marked: "YwRobot Arduino LCM1602 IIC V1"
//based on http://tech2077.blogspot.com.au/2012/06/running-hd44780-lcd-over-i2c-on.html?m=1

#include <unistd.h>
#include <string.h>

#include "lcd.h"

/*
Initiate i2c-connection to lcd
i2c_num: i2c device number (/dev/i2c-X)
i2c_addr: Display i2c address (0x27?)

returns device number, -1 on error
*/
int lcd_dev_init(int i2c_num, int i2c_addr) {
    int i2c = 0;

    if((i2c = i2c_init(i2c_num, i2c_addr)) < 0) {
        return -1;
    }
    return i2c;
}

/*
Initiate lcd
i2c: device number
*/
void lcd_init(int i2c) {
    i2c_write(i2c,(0x30),0,1);

    enableLatch(i2c);
    usleep(2);
    enableLatch(i2c);
    usleep(2);
    enableLatch(i2c);
    usleep(2);

    i2c_write(i2c,(0x20),0,1);

    enableLatch(i2c);
    usleep(2);

    lcd_cmd(i2c,0x28);
    lcd_cmd(i2c,0x08);
    lcd_cmd(i2c,0x01);
    lcd_cmd(i2c,0x06);
    lcd_cmd(i2c,0x0C);
    lcd_cmd(i2c,0x0F);
}

/*
Print text to lcd
i2c: device number
str: c-string
row: row

returns -1 on error
*/
int lcd_print_str(int i2c, const char *str, int row) {
    switch(row) {
        case 1:
            lcd_cmd(i2c,0x80);
            break;
        case 2:
            lcd_cmd(i2c,0xC0);
            break;
        default:
            return -1;
    }

    int i;
    for(i = 0; i < strlen(str);i++) {
        lcd_write_char(i2c,str[i]);
    }

    lcd_cmd(i2c,0xC);

    return 0;
}
