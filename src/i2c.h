#ifndef __i2c__
#define __i2c__

#include <avr/io.h>
#include <stdbool.h>
#include "sfrdef.h"

#define SUCCESS	0

#define TW_STATUS		(TWSR & TW_STATUS_MASK)
#define TW_STATUS_MASK	(0xF8)
#define TW_WRITE 0 
#define TW_READ 1
#define TW_START 0x08
#define TW_REP_START 0x10
#define TW_MT_SLA_ACK		0x18
#define TW_MR_SLA_ACK		0x40
#define TW_MT_DATA_ACK		0x28
#define TW_MR_DATA_ACK		0x50
#define TW_MR_DATA_NACK		0x58

#define I2C_SCL_PIN PORTC5
#define I2C_SDA_PIN	PORTC4

#define I2C_SLA_W(ADDR)		((ADDR << 1) | TW_WRITE)
#define I2C_SLA_R(ADDR)		((ADDR << 1) | TW_READ)
#define I2C_READ_ACK	1
#define I2C_READ_NACK	0

#define TWCR *__SFR_8(0xBC)
#define TWDR *__SFR_8(0xBB)
#define TWAR *__SFR_8(0xBA)
#define TWSR *__SFR_8(0xB9)
#define TWBR *__SFR_8(0xB8)

#define TWINT 7
#define TWEA 6
#define TWSTA 5 
#define TWSTO 4
#define TWEN 2 


typedef uint16_t ret_code_t;

typedef enum {
	I2C_FREQ_100K,
	I2C_FREQ_250K,
	I2C_FREQ_400K
} i2c_freq_mode_t;

void i2c_Init(i2c_freq_mode_t twi_freq, bool pullup_en);

ret_code_t i2c_Start(void);

void i2c_Stop(void);

ret_code_t i2c_WriteSla(uint8_t sla);

ret_code_t i2c_Write(uint8_t data);

uint8_t i2c_Read(bool read_ack);

ret_code_t i2c_MasterTransmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, bool repeat_start);
ret_code_t i2c_MasterTransmitByte(uint8_t slave_addr, uint8_t p_data);

ret_code_t i2c_MasterReceive(uint8_t slave_addr, uint8_t* p_data, uint8_t len);

#endif /* TWI_MASTER_H_ */
