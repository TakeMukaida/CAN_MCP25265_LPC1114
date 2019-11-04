#include "ReWrite.h"

MCP2515_REWRITE::MCP2515_REWRITE(DigitalOut *di, SPI *sp) {
    cs     = di;
    spi    = sp;
}

void MCP2515_REWRITE::MCP2515_ReWrite(unsigned char SIDH, unsigned char SIDL) {
    cs->write(0);
    // Enter configuration mode
    data[0] = MCP2515_REQUEST_WRITE;                                //L027, 0x02
    data[1] = MCP2515_REQUEST_MODE_SELECT;                          //L030, 0x0F    CANCTRL     レジスタ10-1参照
    data[2] = MCP2515_MODE_SELECT_CONFIGURATION;                    //L031, 0x80    100_0_0_0_00
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER0_10_3;               //L085, 0x00    RXF0SIDH
    data[2] = SIDH;                                                     //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXF0(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER0_2_0;                //L092, 0x01    RXF0SIDL
    data[2] = SIDL;                                                     //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]); 
    
    CSsupport();
    // Enter mode
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_MODE_SELECT;                              //L030, 0x0F    CANCTRL
    data[2] = MCP2515_MODE_SELECT_NORMAL;                               //mode
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
        
    cs->write(1);
}              

void MCP2515_REWRITE::CSsupport() {
    cs->write(1); 
    
    wait_us(10);
    
    cs->write(0);   
}

MCP2515_REWRITE::~MCP2515_REWRITE(){
    
}