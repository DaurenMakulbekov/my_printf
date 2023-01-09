#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

// convert int

char reVal(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}
 
// Utility function to reverse a string
void strev(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len/2; i++)
    {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}
 
// Function to convert a given decimal number
// to a base 'base' and
char* fromDeci(char res[], int base, int inputNum)
{
    int index = 0;  // Initialize index of result
 
    // Convert input number is given base by repeatedly
    // dividing it by base and taking remainder
    while (inputNum > 0)
    {
        res[index++] = reVal(inputNum % base);
        inputNum /= base;
    }
    res[index] = '\0';
 
    // Reverse the result
    strev(res);
 
    return res;
}

//

// itoa

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

//

// print void * pointer argument

void voidptr(void *p) {

    unsigned char buf[sizeof(p)];
    memcpy(buf, &p, sizeof(p));

    write(1, "0x", 2);

    int a = 0;

    for (int i = sizeof(p) - 1; i >= 0; i--) {
        unsigned char hi = (buf[i] >> 4) & 0xf; 
        unsigned char lo = buf[i] & 0xf;        
        char tmp[2] = {hi, lo};

        tmp[0] += hi < 10 ? '0' : 'a' - 10;
        tmp[1] += lo < 10 ? '0' : 'a' - 10;
        
        if (a > 1) {
            write(1, tmp, 2);
        }
        a ++;
    }
}

//

// printf

int my_printf(char * restrict format, ...) {

    int count = 0;
    va_list ap;
    va_start(ap, format);

    char *str;
    unsigned char c;
    int d;
    int o;
    int u;
    int x;
    void *p;

   while(*format) {
        if (*format == '%') {
            format ++;
            // string
            if (*format == 's') {
            str = va_arg(ap, char*);
            fputs(str, stdout);
            format ++;
            count += strlen(str);
            }
            // char
            if (*format == 'c') {
                c = va_arg(ap, int);
                char *ch;
                ch = (char*)malloc(2 * sizeof(char));
                ch[0] = c;
                ch[1] = '\0';
                fputs(ch, stdout);
                format ++;
                count += 1;
                free(ch);
            }
            // d
            if (*format == 'd') {
                d = va_arg(ap, int);
                char *dec;
                dec = (char*)malloc(10 * sizeof(char));
                itoa(d, dec, 10);
                fputs(dec, stdout);
                format ++;
                count += strlen(dec);
                free(dec);
            }
            // o
            if (*format == 'o') {
                o = va_arg(ap, int);
                char res[10];
                char* octal = fromDeci(res, 8, o);
                fputs(octal, stdout);
                format ++;
                count += strlen(octal);
            }
            // u
            if (*format == 'u') {
                u = va_arg(ap, int);
                char udec[10];
                char* unsigneddecimal = fromDeci(udec, 10, u);
                fputs(unsigneddecimal, stdout);
                format ++;
                count += strlen(unsigneddecimal);
            }
            // x
            if (*format == 'x') {
                x = va_arg(ap, int);
                char hexadec[10];
                char* hex = fromDeci(hexadec, 16, x);
                fputs(hex, stdout);
                format ++;
                count += strlen(hex);
            }
            // p
            if (*format == 'p') {
                p = va_arg(ap, void*);
                voidptr(p);
                format ++;
                count += strlen(p);
            }
        }
        else {
            putchar(*format);
            format ++;
            count += 1;
        }
    }
    va_end(ap);
    return count;
}

int main() {
    my_printf("%s\n", "Hello World!");
    //my_printf("%c\n", 'a');
    //my_printf("%d\n", 7); // decimal
    //my_printf("%o\n", 25); // octal
    //my_printf("%u\n", 33); // unsigned decimal
    //my_printf("%x\n", 41); // hexadecimal
    //int p;
    //void *ptr = &p;
    //my_printf("%p\n", ptr);
    return 0;
}
