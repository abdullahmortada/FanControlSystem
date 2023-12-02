#include"eeprom.h"



void eeprom_write(unsigned int address_u16,data_u8)
{ 
    while (EECR & (1<<EEPE));

    EEAR=address_u16
    EEDR=data_u8
    
    EECR|=(1<<EEPM1)//setting the mode to writing only
    
    EECR|=(1<<EEMPE)//enable writing
    
    EECR|=(1<<EEPE)//start writing 


}

void eeprom_read(unsigned int address_u16,data_u8)
{
  
    while (EECR & (1<<EEPE));
    EEAR=address_u16
    EECR|=(1<<EERE)//start reading
    return (EEDR)
    
    
 
}