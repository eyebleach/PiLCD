//PiLCD

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "lcd.h"

/* Initiate i2c-connection
i2c_num: device number of i2c (/dev/i2c-X)
i2c_addr: device address (ex. 0x27)

returns an i2c device
*/
int i2c_init(int i2c_num, int i2c_addr) {
    int file;
    char filename[32];

    snprintf(filename, 31, "/dev/i2c-%d", i2c_num);

    file = open(filename, O_RDWR);

    if(file < 0) {
        return LCD_I2C_FILE_ERROR;
    }

    if(ioctl(file,I2C_SLAVE,i2c_addr) < 0) {
        return LCD_I2C_OPEN_ERROR;
    }

    return file;
}

/* Writes to i2c-bus
device: return-value from i2c_init
cmd: command
cmd2: second command (not used)
len: length of command (always 1 of cmd2 is not used)

returns 0 if ok, other: see constants
*/
int i2c_write(int device, unsigned char cmd, unsigned char cmd2, int len) {

    unsigned char buf[2];
    buf[0] = cmd;
    buf[1] = cmd2;

    if(write(device, buf, len) < 0) {
        return LCD_I2C_WRITE_ERROR;
    }

    return 0;
}

/* Reads from i2c-bus
device: return-value from i2c_init
value: pointer to read-value

returns 0 if ok, other: see constants
*/
int i2c_read(int device, unsigned char *value) {

    if(read(device, value, 1) < 0) {
        return LCD_I2C_READ_ERROR;
    }

    return 0;
}

void i2c_close(int device) {
    close(device);
}

/* Keeps enable-pin on
i2c: device number
*/
void enableLatch(int i2c) {
    unsigned char r = 0;

    i2c_read(i2c,&r);
    i2c_write(i2c,(r | 0x04) | 0x08,0,1);
    i2c_read(i2c,&r),
    i2c_write(i2c,(r & 0xFB) | 0x08,0,1);
}

/*Runs command to lcd
i2c: device number
cmd: command
*/
void lcd_cmd(int i2c, unsigned char cmd) {
    i2c_write(i2c,( (cmd>>4)<<4 ) | 0x08,0,1);
    enableLatch(i2c);
    i2c_write(i2c,( (cmd & 0x0F)<<4 ) | 0x08,0,1);
    enableLatch(i2c);
    i2c_write(i2c,0x0 | 0x08,0,1); //0x08 for backlight!
}

/*Runs write-command to lcd
i2c: device number
chr: character
*/
void lcd_write_char(int i2c, unsigned char chr) {
    i2c_write(i2c,(0x01 | (chr>>4)<<4) | 0x08,0,1);
    enableLatch(i2c);
    i2c_write(i2c,(0x01 | (chr & 0x0F)<<4) | 0x08,0,1);
    enableLatch(i2c);
    i2c_write(i2c,0x0 | 0x08,0,1);
}
