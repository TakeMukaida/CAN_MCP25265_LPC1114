#pragma once

#include "mcp2515.h"

class MCP2515_REWRITE {
private:
    DigitalOut *cs;
    SPI        *spi;
    
    char cnt;
    char data[3];
    
public:
    MCP2515_REWRITE(DigitalOut *, SPI *);  //instructor
    
    void MCP2515_ReWrite(unsigned char, unsigned char);
    void CSsupport();
    
    ~MCP2515_REWRITE();    //destructor
    
};