#include "Write.h"

MCP2515_WRITE::MCP2515_WRITE(DigitalOut *di, SPI *sp) {
    cs     = di;
    spi    = sp;
}

void MCP2515_WRITE::MCP2515_Write(unsigned char d, unsigned char SIDH, unsigned char SIDL) {
    cs->write(0);
 
    data[0] = MCP2515_REQUEST_WRITE;                            //L027, 0x02
    data[1] = MCP2515_REQUEST_SET_SEND_DATA_SID_BUF0_10_3;      //L046, 0x31        TXB0SIDH
    data[2] = SIDH;                                             //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_SEND_DATA_SID_BUF0_2_0;       //L050, 0x32        TXB0SIDL
    data[2] = SIDL;                                             //data
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
    
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_SEND_DATA_LENGTH_BUF0;        //L054, 0x35        TXB0DLC
    data[2] = 0x01;                                             //qstn, 00000001    0_0_00_0001
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);                                   //ここまでで送信バッファ用のTXBnSIDH,TXB0SIDL,TXB0DLCの設定が完了
    
    CSsupport();
//*** 要検証   
    data[0] = MCP2515_REQUEST_WRITE;//割り込み許可
    data[1] = 0x2B;
    data[2] = 0x00;                                                
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
        
    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;//割り込みフラグ
    data[1] = 0x2C;
    data[2] = 0x00;                                                
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);
        
    CSsupport();
//      要検証 ***/    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SET_SEND_DATA_BUF0;               //L058, 0x36        TXB0D0
    data[2] = d;                                                //data, dddddddd    dddddddd
    for(cnt = 0; cnt <= 2; cnt++) 
        spi->write(data[cnt]);

    CSsupport();
    
    data[0] = MCP2515_REQUEST_WRITE;
    data[1] = MCP2515_REQUEST_SETTING_SEND_DATA_BUF0;           //L036, 0x30        TXB0CTRL
    data[2] = MCP2515_SETTING_SEND_DATA_PRIORITY_LOW            //L041, 0x00
            + MCP2515_SETTING_SEND_DATA_GO;                     //L040, 0x08        0_0_0_0_1_0_00
    for(cnt = 0; cnt <= 2; cnt++)
        spi->write(data[cnt]);
    
    cs->write(1);
}

void MCP2515_WRITE::CSsupport() {
    cs->write(1); 
    
    wait_us(10);
    
    cs->write(0);   
}

MCP2515_WRITE::~MCP2515_WRITE(){
    
}

