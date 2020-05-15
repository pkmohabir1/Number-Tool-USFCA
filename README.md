## Porfirio Mohabir
CS 315 Computer Architecture
Project 02 - Base Conversions

## Project Overview


The Program builds a linux command line utility in C Programming.The Program conducts base 2,10, and 16 conversions(Decimal,HexDecimal, and Binary).The program also take in option flag as arguements. The -b option flag represents the bit width. Value given must fit into the necessary bit length for binaryand hexdecimal. The Program also has a range option flag -r.This flag will extact part of the binary based on the range given. From the right most significant bit to the left most significant. All while still fitting  into the specific bit length or defalut bit length 32. The program also provides conversions for both signed and unsigned numbers. 


## Funtions Prototypes 

```C
void check_arguement(char* arguement);
void binary_to_decimal();
void hex_to_binary();
char* decimal_to_binary(int bit_width, unsigned int num);
void hex_to_decimal();
void hex_input();
void dec_input();
void bin_input();
void execute_cmd();
void print(bool flag);
```

## Compile and Run Program

```
$ gcc -o nt nt.c
$ ./nt 713
0000 0000 0000 0000 0000 0010 1100 1001 (base 2)
0b00000000000000000000001011001001 (base 2)
0x000002C92 (base 16)
713 (base 10 unsigned) 
-713 (base 10 signed) 

$ gcc -o nt nt.c
$ ./nt -713
1111 1111 1111 1111 1111 1101 0011 0111 (base 2)
0b11111111111111111111110100110111 (base 2)
0xFFFFFD373 (base 16)
4294966583 (base 10 unsigned) 
-713 (base 10 signed) 
```

## Included Files

```bash
- nt.c (Main file with funtion implementation)
- nt.h (Header file with struct and fucntion prototypes
```







