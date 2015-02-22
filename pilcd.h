//PiLCD - LCD Library for Raspberry Pi
//For hd44780 lcd with backpack marked: "YwRobot Arduino LCM1602 IIC V1"
//based on http://tech2077.blogspot.com.au/2012/06/running-hd44780-lcd-over-i2c-on.html?m=1

/*
Usage:
open i2c-bus and retreive device number by calling lcd_dec_init with
int dev_num = lcd_dev_init(1, 0x27); (device: /dev/i2c-1, i2c-address: 0x27 (i2cdetect -y 1) )

initiate display with device number from previous step
lcd_init(dev_num);

print to lcd with
const char *str = "Hello World";
lcd_print_str(dev_num, str, 1); (for row 1)
*/

#ifndef __pilcd_h__
#define __pilcd_h__

int lcd_dev_init(int i2c_num, int i2c_addr);
void lcd_init(int i2c);
int lcd_print_str(int i2c, const char *str, int row);

#endif
