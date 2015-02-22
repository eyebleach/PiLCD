#include <stdio.h>
#include "pilcd.h"

int main(int argc, char **argv) {

    int display;

    if((display = lcd_dev_init(1,0x27)) < 0 ) {
        printf("Error opening i2c bus");
        return -1;
    }

    lcd_init(display);

    char *str = "Hello world!";
    char *str2 = "Goodbye..";

    lcd_print_str(display, str,1);
    lcd_print_str(display, str2, 2);

    return 0;
}
