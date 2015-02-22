#include <stdio.h>
#include <string.h>
#include "pilcd.h"

int main(int argc, char **argv) {

    int display;

    if((display = lcd_dev_init(1,0x27)) < 0 ) {
        printf("Error opening i2c bus");
        return -1;
    }

    lcd_init(display);

    unsigned char bottle[] = { 0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                               0x0,0x1,0x2,0x2,0x2,0x2,0x2,0x1,
                               0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x1f,
                               0x0,0x10,0x8,0x7,0x1,0x7,0x8,0x10 };

    lcd_add_char(display,bottle,24);

    char buf[16];
    char *str = "Beer! ";

    strcpy(buf,str);

    char b[] = { 0x01, 0x02, 0x03, 0x00 };

    strcat(buf,b);

    lcd_print_str(display, str, 1, 5);
    lcd_print_str(display, buf, 2, strlen(buf));

    lcd_close(display);
    return 0;
}
