#include <stdint.h>
#include <stdio.h>
#include <string.h>
//needed for the convert.h file if used
//#include "convert.h"

////////////////////////////////////divsion conversion////////////////////////////////////
void div_convert ( uint32_t n , int base , char * out ) {
    char temp [100]; // Temporary buffer
    int pos = 0; //incrementor

    // Handle zero case
    if ( n == 0) {
        strcpy ( out , "0");
        return ;
    }

    // Extract digits from right to left until n is lesss then 0
    while ( n > 0) 
    {
        //updates the remainder
        int remainder = n % base;
        // updatees n while the base stays the same
        n = n / base;
        // Convert digit to character
        //saves the remainder
        if ( remainder < 10)
            temp [ pos ++] = '0' + remainder;
        else
            temp [ pos ++] = 'A' + ( remainder - 10);
    }

    // Reverse the result
    int i;
    for(i = 0; i < pos; i++)
    {
        //gets the last element in 'temp' array
        out[i] = temp[pos - i - 1];
    }
    //must print out
    out[i] = '\0';
}

/////self-implected power conversion/////////////////////////////////////////////
//returns the largest power of base less than or equal to n
uint32_t power(int base, uint32_t n)
{
    uint32_t result = 1;
    if (base <= 1) return result; // avoid infinite loop for base 0/1
    while (result <= n / (uint32_t)base) {
    //gets the exponet closes to the target
        result *= (uint32_t)base;
    }
    return result;
}

////////////////////////////////////sub conversion////////////////////////////////////
void sub_convert ( uint32_t n , int base , char * out ) {
    char temp [100]; // Temporary buffer
    int pos = 0;
       
    // Handle zero case
    if ( n == 0) {
        strcpy ( out , "0");
        return ;
    }

    // get the highest power of base less than or equal to n
    uint32_t p = power(base, n);

    // Extract digits from left to right
    while ( p > 0) 
    {
        // extract digits
        int remainder = n / p;
        n %= p; // reduce remainder

        // Convert digit to character
        //saves the remainder
        if ( remainder < 10)
            temp [ pos ++] = '0' + remainder ;
        else
            temp [ pos ++] = 'A' + ( remainder - 10) ;

        // move down one power
        p /= base; 
    }

    //must print out
    temp[pos] = '\0';
    //number now at zero
    strcpy(out, temp);
}


// Helper: convert uint32 to minimal binary string (no leading zeros, "0" for zero)
static void uint32_to_binary_str(uint32_t v, char *out, size_t outsz) {
    if (v == 0) {
        strncpy(out, "0", outsz);
        out[outsz-1] = '\0';
        return;
    }
    char buf[33];
    int i = 0;
    for (int b = 31; b >= 0; --b) {
        if ( (v >> b) & 1U ) {
            // write the remaining bits
            for (int k = b; k >= 0; --k) {
                buf[i++] = ((v >> k) & 1U) ? '1' : '0';
            }
            break;
        }
    }
    buf[i] = '\0';
    strncpy(out, buf, outsz);
    out[outsz-1] = '\0';
}


////////////////////////////////////print the tables function////////////////////////////////////
void print_tables(int n) {
    // We will print three labeled lines:
    // Original: Binary=<binary> Octal=<octal> Decimal=<decimal> Hex=<hex>
    // LeftShift3: ...
    // And0xFF: ...
    //ensures consistent behavior for bit operations like shifting and masking
    uint32_t val = (uint32_t)n;
    char bin[40], bin2[40], bin3[40];
    char oct[40], oct2[40], oct3[40];
    char hex[40], hex2[40], hex3[40];
    char dec[40], dec2[40], dec3[40];

    // Original
    uint32_to_binary_str(val, bin, sizeof(bin));
    //Original Number Formatting
    sprintf(oct, "%o", val);
    sprintf(hex, "%X", val);
    sprintf(dec, "%u", val);

    // Left shift by 3 (32-bit wrap as unsigned)
    uint32_t ls = val << 3;
    uint32_to_binary_str(ls, bin2, sizeof(bin2));
    sprintf(oct2, "%o", ls);
    sprintf(hex2, "%X", ls);
    sprintf(dec2, "%u", ls);

    // AND with 0xFF
    uint32_t m = val & 0xFFU;
    uint32_to_binary_str(m, bin3, sizeof(bin3));
    sprintf(oct3, "%o", m);
    sprintf(hex3, "%X", m);
    sprintf(dec3, "%u", m);
	//Prints the results
    printf("Original: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin, oct, dec, hex);
    printf("LeftShift3: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin2, oct2, dec2, hex2);
    printf("And0xFF: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin3, oct3, dec3, hex3);
    /*
    n=21
    Original: Binary=10101 Octal=25 Decimal=21 Hex=15
    LeftShift3: Binary=10101000 Octal=250 Decimal=168 Hex=A8
    And0xFF: Binary=10101 Octal=25 Decimal=21 Hex=15
    */
}
