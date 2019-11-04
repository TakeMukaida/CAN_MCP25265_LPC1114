#include "mcp2515.h"

#define VALUE       0x00            

Serial device(dp16, dp15);

SPI spi(dp2, dp1, dp6);     // mosi, miso, sclk
DigitalOut cs(dp14);

DigitalOut stby(dp18);

InterruptIn RxB0(dp9);
InterruptIn RxB1(dp10);

DigitalIn bit_3rd(dp13);
DigitalIn bit_2nd(dp17);
DigitalIn bit_1st(dp11);       
DigitalIn bit_0th(dp4);

char cnt;

unsigned char     identifier_tx_SIDH = 0x00,     identifier_tx_SIDL = 0x00;
unsigned char     identifier_rx_SIDH = 0x00,     identifier_rx_SIDL = 0x00;
unsigned char log_identifier_rx_SIDH = 0xF0, log_identifier_rx_SIDL = 0xF0;
unsigned char                address = 0x00,                code_tx = 0x00;

MCP2515_INIT    inits(&cs, &spi);
MCP2515_WRITE   writs(&cs, &spi);
MCP2515_REWRITE rewts(&cs, &spi);
MCP2515_READ    reads(&cs, &spi, &device);

int main() {
    spi.format(8, 0);
    spi.frequency(1000000);
    
    device.baud(38400);
    device.attach(UART_DATA, Serial::RxIrq);
    
    stby = 0;
    
    RxB0.fall(&Read_RXB0);
    RxB1.fall(&Read_RXB1);
    
    inits.MCP2515_Initialize();
    
    while(1) {
        Identifier_RX();
    }
}

void UART_DATA() {
    if(device.getc() == 0xA6) {
        if(device.getc() == 0xB6) {
            address = device.getc();
            code_tx = device.getc();
        }
        else 
            return;
    }
    else 
        return;
 
    identifier_tx_SIDH = (address >> 3); 
    identifier_tx_SIDL = (address << 5);   
    writs.MCP2515_Write(code_tx, identifier_tx_SIDH, identifier_tx_SIDL);     
}

void Read_RXB0() {                                              //L030, 0x92
    reads.MCP2515_Read_RXBn(MCP2515_REQUEST_READ_BUF0_DATA0);
}
   
void Read_RXB1() {                                              //L032, 0x96
    reads.MCP2515_Read_RXBn(MCP2515_REQUEST_READ_BUF1_DATA0);
}

void Identifier_RX() { 
    bool  bit[4];
    short cnt;
    
    bit[3] = bit_3rd;
    bit[2] = bit_2nd;
    bit[1] = bit_1st;
    bit[0] = bit_0th;
    
    identifier_rx_SIDH = bit[3];
    for(cnt = 2; cnt >= 0; cnt--)
        identifier_rx_SIDL |= (bit[cnt] << (cnt + 5));
    
    if((log_identifier_rx_SIDH != identifier_rx_SIDH) || (log_identifier_rx_SIDL != identifier_rx_SIDL))
        rewts.MCP2515_ReWrite(identifier_rx_SIDH, identifier_rx_SIDL);
    
    log_identifier_rx_SIDH = identifier_rx_SIDH;
    log_identifier_rx_SIDL = identifier_rx_SIDL;
}
