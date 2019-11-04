#include "Initialize.h"

MCP2515_INIT::MCP2515_INIT(DigitalOut *o, SPI *s){
    cs   = o;
    spi  = s;
}

void MCP2515_INIT::MCP2515_Initialize() {
    int  cnt;
    char data[3];
    
    cs->write(0);
    
    // Reset mcp2515
    data[0] = MCP2515_REQUEST_RESET;                                //L025,         110000000
    spi->write(data[0]);
    
    CSsupport();
    
    // Enter configuration mode
    data[0] = MCP2515_REQUEST_WRITE;                                //L027, 0x02
    data[1] = MCP2515_REQUEST_MODE_SELECT;                          //L030, 0x0F    CANCTRL     レジスタ10-1参照
    data[2] = MCP2515_MODE_SELECT_CONFIGURATION;                    //L031, 0x80    100_0_0_0_00
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
    
    CSsupport();
    
    // Enable interrupt pin
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SETTING_RECV_DATA_ENABLE_RXBF;        //L070, 0x0C    BFPCTRL     レジスタ4-3参照
    data[2] = MCP2515_SETTING_RECV_DATA_ENABLE_RXBF;                //L071, 0x0F    0_0_0_0_1_1_1_1
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
        
    CSsupport();
    
    // Setting filter(F0~F5) and mask(M0~M1)        
    
        //RXF0
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER0_10_3;               //L085, 0x00    RXF0SIDH
    data[2] = RXF0SIDH;                                     //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXF0(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER0_2_0;                //L092, 0x01    RXF0SIDL
    data[2] = RXF0SIDL;                                     //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                          //Setting of RXF0(SIDL)
    
    CSsupport();
    
        //RXF1
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER1_10_3;               //L086, 0x04    RXF1SIDH
    data[2] = RXF1SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXF1(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER1_2_0;                //L093, 0x05    RXF1SIDL
    data[2] = RXF1SIDL;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                          //Setting of RXF1(SIDL)
    
    CSsupport();
    
        //RXF2
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER2_10_3;               //L087, 0x08    RXF2SIDH
    data[2] = RXF2SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                           //Setting of RXF3(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER2_2_0;                //L094, 0x09    RXF2SIDL
    data[2] = RXF2SIDL;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                           //Setting of RXF2(SIDL)
    
    CSsupport();
    
        //RXF3
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER3_10_3;               //L088, 0x10    RXF3SIDH
    data[2] = RXF3SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                           //Setting of RXF3(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER3_2_0;                //L095, 0x11    RXF3SIDL
    data[2] = RXF3SIDL;                                                 //data 
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                           //Setting of RXF3(SIDL)
    
    CSsupport();
    
        //RXF4
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER4_10_3;               //L089, 0x14    RXF4SIDH
    data[2] = RXF4SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXF4(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER4_2_0;                //L096, 0x15    RXF4SIDL
    data[2] = RXF4SIDL;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                          //Setting of RXF4(SIDL)
    
    CSsupport();
    
        //RXF5
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER5_10_3;               //L090, 0x18    RXF5SIDH
    data[2] = RXF5SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXF5(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_FILTER5_2_0;                //L097, 0x19    RXF5SIDL
    data[2] = RXF5SIDL;                                                 //data 
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                          //Setting of RXF5(SIDL)
    
    CSsupport();
    
        //RXM0
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_MASK0_10_3;                 //L099, 0x20    RXF4SIDH
    data[2] = RXM0SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                          //Setting of RXM0(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_MASK0_2_0;                  //L102, 0x24    RXF4SIDL
    data[2] = RXM0SIDL;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                          //Setting of RXM0(SIDL)
    
    CSsupport();
    
        //RXM1
        
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_MASK1_10_3;                 //L100, 0x21    RXF5SIDH
    data[2] = RXM1SIDH;                                                 //data
    for(cnt = 0; cnt <= 2; cnt++)                                       
        spi->write(data[cnt]);                                           //Setting of RXM1(SIDH)
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_READ_DATA_MASK1_2_0;                  //L103, 0x25    RXF5SIDL
    data[2] = RXM1SIDL;                                                 //data 
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                           //Setting of RXM1(SIDL)
    
    CSsupport();
    
    // Setting receive buf0(filter etc.)
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SETTING_RECV_DATA_BUF0;                   //L063, 0x60    RXB0CTRL
    data[2] = MCP2515_SETTING_RECV_DATA_ENABLE_NORMAL_FILTER            //L066, 0x20
            + MCP2515_SETTING_RECV_DATA_ENABLE_CHANGE_SAVE_BUF0_TO_1;   //L068, 0x06    0_01_0_0_1_1_0
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
    
    CSsupport();
        
    // Setting receive buf1(filter etc.)
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SETTING_RECV_DATA_BUF1;                   //L074, 0x70    RXB1CTRL
    data[2] = MCP2515_SETTING_RECV_DATA_ENABLE_NORMAL_FILTER            //L067, 0x20    
            + MCP2515_SETTING_RECV_DATA_ENABLE_CHANGE_SAVE_BUF1_TO_0;   //L0??, 0x00    0_01_0_0_000
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

void MCP2515_INIT::CSsupport() {
    cs->write(1); 
    
    wait_us(10);
    
    cs->write(0);   
}

MCP2515_INIT::~MCP2515_INIT(){
    
}