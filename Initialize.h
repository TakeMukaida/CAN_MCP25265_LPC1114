#pragma once

#include "mbed.h"
#include "mcp2515.h"

//基本定義一覧
#define RXF0SIDH    (0xFF)                       
#define RXF0SIDL    (0x00 << 5)
#define RXF1SIDH    (0xFF)
#define RXF1SIDL    (0x01 << 5)
#define RXF2SIDH    (0xFF)
#define RXF2SIDL    (0x02 << 5)
#define RXF3SIDH    (0xFF)
#define RXF3SIDL    (0x03 << 5)
#define RXF4SIDH    (0xFF)
#define RXF4SIDL    (0x04 << 5)
#define RXF5SIDH    (0xFF)
#define RXF5SIDL    (0x05 << 5)

#define RXM0SIDH    (0xFF) //0x10
#define RXM0SIDL    (0xE0) //0x00 << 5
#define RXM1SIDH    (0xFF) //0x10
#define RXM1SIDL    (0xE0) //0x01 << 5 

//0x04から0x07まで受入
//#define RXF0SIDH_FROM_4_TO_7   0x00 //0x00            
//#define RXF0SIDL_FROM_4_TO_7   0x00 //0x80            //F:"(0000_0000"_"100)0_0000"
//#define RXM0SIDH_FROM_4_TO_7   0xFF //0xFF
//#define RXM0SIDL_FROM_4_TO_7   0xE0 //0x80            //M:"(1111_1111"_"100)0_0000"

class MCP2515_INIT {
private:                                //変数を突っ込む
    DigitalOut *cs;
    SPI *spi;
    
public:                                 //関数を突っ込む
    MCP2515_INIT(DigitalOut *, SPI *);  //instructor
    
    void MCP2515_Initialize();
    void CSsupport();
    
    ~MCP2515_INIT();    //destructor

};