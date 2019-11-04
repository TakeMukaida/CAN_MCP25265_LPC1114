#pragma once

#include "mcp2515.h"

class MCP2515_WRITE {
private:
    DigitalOut *cs;
    SPI        *spi;
    
    char cnt;
    char data[3];
    
public:
    MCP2515_WRITE(DigitalOut *, SPI *);  //instructor
    
    void MCP2515_Write(unsigned char, unsigned char, unsigned char);
    void CSsupport();
    
    ~MCP2515_WRITE();    //destructor
    
};