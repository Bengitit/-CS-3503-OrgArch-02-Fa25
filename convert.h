//connected to the other files through "#include "convert.h""
#ifndef CONVERT_H//finds the file
#define CONVERT_H//opnes the file

#include <stdint.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
uint32_t power(int base, uint32_t n);
void print_tables(int n);

#endif//closes the file
