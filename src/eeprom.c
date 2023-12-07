#include"eeprom.h"
#include "util/delay.h"


void eeprom_write(uint16_t address_u16, uint8_t data)
{ 
    while (EECR & (1<<EEPE));

    EEAR = address_u16;
    
    EECR |= (1<<EEMPE);//enable writing
    
    EEDR = data;
    EECR |= (1<<EEPE);//start writing 

}

uint8_t eeprom_read(uint16_t address_u16)
{
  
    while (EECR & (1<<EEPE));
    EEAR = address_u16;
    EECR |= (1<<EERE);//start reading
    return EEDR;
 
}


void eeprom_WriteBytes(uint16_t address_u16, uint8_t* data){
  for(size_t i = 0; i < sizeof(data); i++){
    if((address_u16 + i) >= (1024)) break;
    eeprom_write(address_u16 + i, data[i]);
  }
}


void eeprom_ReadBytes(uint16_t address_u16, uint8_t* buf, uint16_t len){
  for(size_t i = 0; i < len; i++){
    if(i > sizeof(buf) || address_u16 + i >= (1<<10)) break;
    buf[i] = eeprom_read(address_u16 + i);
  }
}
