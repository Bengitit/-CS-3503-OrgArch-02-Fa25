//defines it and include convert.h file
#ifndef CONVERT_H//opens it
#define CONVERT_H//creates it

#include <stdint.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
uint32_t power(int base, uint32_t n);
void print_tables(int n);

#endif//closes the #ifndef CONVERT_H
