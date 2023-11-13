#include <SPI.h>
#define CS 10

uint8_t val16;
uint8_t receivedVal;
uint8_t kom;
uint16_t itemp;/*internal temperature*/
uint16_t valit;
uint8_t konf_temp=0b00010000;
uint16_t sel_temp=0b00001000000010110;
uint8_t czyt_temp=0b01011000;



void setup()
{
  Serial.begin(2400,SERIAL_8E2);
  SPI.begin();
  
  kom=0x60;
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  digitalWrite(CS, LOW);
  SPI.transfer16(0xFFFF);
  SPI.transfer16(0xFFFF);

  digitalWrite(CS,1);
  digitalWrite(CS, LOW);
  SPI.transfer(0x8);
  SPI.transfer16(0x500A);
  digitalWrite(CS, 1);
  delay(5);
  digitalWrite(CS, LOW);
SPI.transfer(kom);
delay(3);
receivedVal = SPI.transfer(val16);
digitalWrite(CS,1);
Serial.print("id to: ");
Serial.print(receivedVal,HEX);
Serial.print('\n');
delay(100);
Serial.print(CS,HEX);
digitalWrite(CS,1);
Serial.print('\n');
delay(100);

}


void loop() 
{
 digitalWrite(CS, LOW);
delay(100);
SPI.transfer(0x8);
SPI.transfer16(0x100A);
digitalWrite(CS, 1);
digitalWrite(CS, 0);
SPI.transfer(konf_temp);
SPI.transfer16(sel_temp);
digitalWrite(CS, 1);
digitalWrite(CS, 0);

SPI.transfer(czyt_temp);
do
{

 
} while (digitalRead(MISO)==1);
itemp=SPI.transfer16(valit);
Serial.print(itemp);
Serial.print('\n');

digitalWrite(CS,1);

}

