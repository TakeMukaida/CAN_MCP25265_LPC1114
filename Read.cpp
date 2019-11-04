#include "Read.h"

MCP2515_READ::MCP2515_READ(DigitalOut *di , SPI *sp, Serial *se) {
    cs     = di;
    spi    = sp;
    device = se;
}

void MCP2515_READ::MCP2515_Read_RXBn(unsigned char buf_data) {
    cs->write(0);
    
    spi->write(buf_data);     
    code_rx = spi->write(0x00);     
 
    cs->write(1);

    device->putc(0xA6);
    device->putc(0xB6);
    device->putc(code_rx);
}

MCP2515_READ::~MCP2515_READ(){
    
}