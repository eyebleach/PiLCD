//PiLCD
#ifndef __lcd_h__
#define __lcd_h__

#define LCD_OK              0
#define LCD_I2C_FILE_ERROR  -2
#define LCD_I2C_OPEN_ERROR  -4
#define LCD_I2C_WRITE_ERROR -6
#define LCD_I2C_READ_ERROR  -8
#define LCD_UNKNOWN_ERROR   -10

typedef struct Displays {
    int addr;

} Lcd;

int i2c_init(int i2c_num, int i2c_addr);
int i2c_write(int device, unsigned char cmd, unsigned char cmd2, int len);
int i2c_read(int device, unsigned char *value);
//NEW
void enableLatch(int i2c);
void lcd_cmd(int i2c, unsigned char cmd);
void lcd_write_char(int i2c, unsigned char chr);

//new features!
//void lcd_clear(int i2c);
//void lcd_write_str(int i2c, char[] *str);
//void lcd_add_custom(i2c, unsigned char chr);
#endif
