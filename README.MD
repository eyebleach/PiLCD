# PiLCD
A library for controlling a lcd with a Raspberry Pi, using a [lcm1602 backpack](http://arduino-info.wikispaces.com/LCD-Blue-I2C)

* Print text to display
* Add custom characters

### Usage

`#include "pilcd.h` to include library in your code.

`int lcd_dev_init(int i2c_num, i2c_addr)`  
Initiates i2c connection and returns a device number.  
`i2c-num` - device number (ex. 1 for /dev/i2c-1)  
`i2c-addr` - lcd address (normally 0x27)

`void lcd_init(int i2c)`  
Initiates the display.  
`i2c` - device number

`int lcd_print_str(int i2c, const char *str, int row, int chars)`  
Prints a c-string to given row.  
`i2c` - device number  
`*str` - c-string (pointer to char-array)  
`row` - which row to print at  
`chars` - how many chars (ex. strlen(str))

`void lcd_add_char(int i2c, unsigned char chr[], int lines)`  
Adds a custom character to volatile memory.  
`i2c` - device number  
`chr[]` - char-array with character-codes (see below)  
`lines` - how many lines (8 for each character for 5x8 lcd (see below)

###Custom characters

To add custom characters, use the `lcd_add_char()`-function and supply a character array like the example.

You need to supply all characters each time, so you can't add characters by running the function multiple times.

To print your custom characters, you simply print the number of your characters, starting on 0.



Example, 3 custom characters (forms a bottle):

    unsigned char bottle[] = { 0x0,0x1,0x2,0x2,0x2,0x2,0x2,0x1,
                               0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x1f,
                               0x0,0x10,0x8,0x7,0x1,0x7,0x8,0x10 };

    lcd_add_char(display,bottle,24);

    char beer[] = { 0, 1, 2 };
    lcd_print_str(display, beer, 1, 3); //row 1, 3 characters

[Automatic way to make custom characters](http://www.quinapalus.com/hd44780udg.html)


### Thanks to
[tech2077 blog](http://tech2077.blogspot.com.au/2012/06/running-hd44780-lcd-over-i2c-on.html?m=1) for making this possible at all.



