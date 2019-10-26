#ifndef _LCD12864B_S_HH
#define _LCD12864B_S_HH

#include <Arduino.h>

class LCD12864B_S{
private:
    uint8_t clk,data,cs;
    void sendbyte(uint8_t zdata);
public:
    LCD12864B_S(uint8_t clock, uint8_t data, uint8_t cs);
    ~LCD12864B_S();
    void write_com(uint8_t cmdcode);
    void write_data(uint8_t Dispdata);
    void init();
    void cls();
    void setxy(uint8_t x, uint8_t y);
    void writeString(const char *s);
    void printxy(uint8_t x,uint8_t y,const char *s);
    void printfxy(uint8_t x,uint8_t y,const char *s,...);
    //void drawString(uint8_t x,uint8_t y,const char *s);
};



#endif