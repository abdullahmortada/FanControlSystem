#ifndef __sfr__
#define __sfr__

#define __SFR_8(mem_addr) (volatile uint8_t *)(mem_addr)
#define __SFR_16(mem_addr) (volatile uint16_t *)(mem_addr)

#endif
