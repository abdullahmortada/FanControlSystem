#include "helpers.h"

void intToString(int num, char *arr, uint8_t base)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (base == 10 && num < 0);    

    //make sure value is positive
    if (sign) v = -num;
    else v = (unsigned)num;


    //convert digits to char
    while (v || tp == tmp)
    {
        i = v % base;
        v /= base;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    //length is last char pointer - first char pointer
    int len = tp - tmp;

    //add negative sign before copying rest of string
    if (sign) 
    {
        *arr++ = '-';
        len++;
    }

    //copy in reverse order from temp to output array
    while (tp > tmp)
        *arr++ = *--tp;

    
    //add terminating character
    *arr = '\0';
}


size_t clamp(size_t value, size_t min, size_t max){
  size_t t = value < min ? min : value;
  return t > max ? max : t;
}
