#include "lcd12864b_s.h"
#include <stdio.h>
#include <stdarg.h>

LCD12864B_S::LCD12864B_S(uint8_t _clk, uint8_t _data, uint8_t _cs){
    clk = _clk;
    data = _data;
    cs = _cs;
}

LCD12864B_S::~LCD12864B_S(){
}

void LCD12864B_S::sendbyte(uint8_t zdata){
    uint8_t i;
    for(i=0; i<8; i++){
        if((zdata << i) & 0x80){
                digitalWrite(data,HIGH);
        }else{
                digitalWrite(data,LOW);
        }
        delay_us(1);
        digitalWrite(clk,LOW);
        delay_us(1);
        digitalWrite(clk,HIGH);
        delay_us(1);
    }
}

void LCD12864B_S::write_com(uint8_t cmdcode){
        digitalWrite(cs,HIGH);
        sendbyte(0xf8);
        sendbyte(cmdcode & 0xf0);
        sendbyte((cmdcode << 4) & 0xf0);
        delay_us(1);
}

void LCD12864B_S::write_data(uint8_t Dispdata){
        digitalWrite(cs,HIGH);
        sendbyte(0xfa);
        sendbyte(Dispdata & 0xf0);
        sendbyte((Dispdata << 4) & 0xf0);
        delay_us(1);
}

void LCD12864B_S::cls(){
    write_com(0x01);
    delay(5);
}


void LCD12864B_S::init(){  
    pinMode(clk,OUTPUT);
    pinMode(data,OUTPUT);
    pinMode(cs,OUTPUT);
    // RST = 0;
    // delay(100);
    // RST = 1;
    cls();
    write_com(0x30);//地址归位
    delay(5);
    write_com(0x0c);//进入点设定
    delay(1);
}

void LCD12864B_S::setxy(uint8_t x, uint8_t y){
    uint8_t data;
    switch(y){
        case 0: data = 0x80;break;
        case 1: data = 0x90;break;
        case 2: data = 0x88;break;
        case 3: 
        default: data = 0x98;
    }
    write_com(data);
    delay(1);
}

void LCD12864B_S::writeString(const char *s){
    while(*s > 0){ 
        write_data(*s);
        s++;
    }
}

void LCD12864B_S::printxy(uint8_t x,uint8_t y,const char *s){
    setxy(x,y);
    writeString(s);
}

void LCD12864B_S::printfxy(uint8_t x,uint8_t y,const char *s,...){
    va_list vp;     
    va_start(vp, s);
    char buf[20];
    vsprintf(buf,s,vp);
    printxy(x,y,buf);
    va_end(vp);
}
