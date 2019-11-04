#pragma once

#include "mcp2515.h"

class MCP2515_READ {
private:
    DigitalOut *cs;
    SPI        *spi;
    Serial     *device;
     
    unsigned char code_rx;
    
public:
    MCP2515_READ(DigitalOut *, SPI *, Serial *);  //instructor
    
    void MCP2515_Read_RXBn(unsigned char);
    
    ~MCP2515_READ();    //destructor
    
};