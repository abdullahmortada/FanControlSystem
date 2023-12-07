#include "i2c.h"

ret_code_t i2c_Start(void)
{
	TWCR =  (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1 << TWINT)));
	
	/* Check error */
	if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
	{
		return TW_STATUS;
	}
	
	return SUCCESS;
}


void i2c_Stop(void)
{
	/* Send STOP condition */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


ret_code_t i2c_WriteSla(uint8_t sla)
{
	/* Transmit slave address with read/write flag */
	TWDR = sla;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
	{
		return TW_STATUS;
	}

	return SUCCESS;
}


ret_code_t i2c_Write(uint8_t data)
{
	/* Transmit 1 byte*/
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		return TW_STATUS;
	}
	
	return SUCCESS;
}


uint8_t i2c_Read(bool read_ack)
{
	if (read_ack)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_ACK)
		{
			return TW_STATUS;
		}
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_NACK)
		{
			return TW_STATUS;
		}
	}
	uint8_t data = TWDR;
	return data;
}


void i2c_Init(i2c_freq_mode_t i2c_freq_mode, bool pullup_en)
{
	DDRC  |= (1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN);
	if (pullup_en)
	{
		PORTC |= (1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN);
	}
	else
	{
		PORTC &= ~((1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN));
	}
	// DDRC  &= ~((1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN));
	
	switch (i2c_freq_mode)
	{
		case I2C_FREQ_100K:
		/* Set bit rate register 72 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*72*1) = 100KHz	*/
		TWBR = 72;
		break;
		
		case I2C_FREQ_250K:
		/* Set bit rate register 24 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*24*1) = 250KHz	*/
		TWBR = 24;
		break;
		
		case I2C_FREQ_400K:
		/* Set bit rate register 12 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*12*1) = 400KHz	*/
		TWBR = 12;
		break;
		
		default: break;
	}
  TWCR = 1<<TWEN;
}


ret_code_t i2c_MasterTransmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, bool repeat_start)
{
	ret_code_t error_code;
	
	/* Send START condition */
	error_code = i2c_Start();
	if (error_code != SUCCESS)
	{
		return error_code;
	}
	
	/* Send slave address with WRITE flag */
	error_code = i2c_WriteSla(I2C_SLA_W(slave_addr));
	if (error_code != SUCCESS)
	{
		return error_code;
	}
	
	/* Send data byte in single or burst mode */
	for (int i = 0; i < len; ++i)
	{
		error_code = i2c_Write(p_data[i]);
		if (error_code != SUCCESS)
		{
			return error_code;
		}
	}
	
	if (!repeat_start)
	{
		/* Send STOP condition */
		i2c_Stop();
	}
	
	return SUCCESS;
}

ret_code_t i2c_MasterTransmitByte(uint8_t slave_addr, uint8_t data){
  return i2c_MasterTransmit(slave_addr, &data, 1, false);
}


ret_code_t i2c_MasterReceive(uint8_t slave_addr, uint8_t* p_data, uint8_t len)
{
	ret_code_t error_code;
	
	/* Send START condition */
	error_code = i2c_Start();
	if (error_code != SUCCESS)
	{
		return error_code;
	}
	
	/* Write slave address with READ flag */
	error_code = i2c_WriteSla(I2C_SLA_R(slave_addr));
	if (error_code != SUCCESS)
	{
		return error_code;
	}
	
	/* Read single or multiple data byte and send ack */
	for (int i = 0; i < len-1; ++i)
	{
		p_data[i] = i2c_Read(I2C_READ_ACK);
	}
	p_data[len-1] = i2c_Read(I2C_READ_NACK);
	
	/* Send STOP condition */
	i2c_Stop();
	
	return SUCCESS;
}
