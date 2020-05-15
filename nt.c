#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <locale.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <wchar.h>
#include <getopt.h>
#include "nt.h"

bool flag_b = false;
bool flag_r = false;

struct conversion con_struct; 

unsigned int str_to_int(char *s) {
	
    int len = strlen(s);
    int base = 10;
    int place_value = 1;
    int retval = 0;
    for (int i = len-1; i >= 0; i--) {
        int digit = s[i] - '0';
        retval += place_value * digit;
        place_value *= base;
    }
    return retval;
}
void binary_to_decimal(){

	char* number_str = strdup(con_struct.binary);

	unsigned int decimal_number = 0;

	int base_number = 1;

	int sz = strlen(number_str);

	for(int i = sz-1;i>=0;i--){
		if(number_str[i] != '0'){
			decimal_number = decimal_number + base_number;
		}
		base_number = base_number * 2;
	}

	if(con_struct.is_negative){
		con_struct.decimal = 0-decimal_number;
		con_struct.unsigned_decimal = (unsigned int)con_struct.decimal;
				
	}else{
		con_struct.unsigned_decimal = (unsigned int)decimal_number;
		con_struct.decimal = 0 - con_struct.unsigned_decimal;
				
	}
}
void hex_to_binary(){
	
	char* pointer;

	int decimal = 0; 
	char* binary_num;
	bool flag = false;



	for(int i =2; i<strlen(con_struct.hex);i++){
		 
		switch(con_struct.hex[i]){
			case 'A':
				decimal = 10;
				break;
			case 'B':
				decimal = 11;
				break;
			case 'C':
				decimal = 12;
				break;
			case 'D':
				decimal = 13;
				break;
			case 'E':
				decimal = 14;
				break;
			case 'F':
				decimal = 15;
				break;
			default:
				decimal = con_struct.hex[i];
				break;
		}
		binary_num = decimal_to_binary(4, decimal);
		if(!flag){
			pointer = strdup(binary_num);
			flag = true;
		}else{
			strcat(pointer,binary_num);
		}
		
	}
	con_struct.binary = strdup(pointer);
}

char* decimal_to_binary(int bit_width, unsigned int num){
	char arr[bit_width];
	int index = 0;

	int b;

	for(int i = bit_width-1; i>=0; i--){

		
		b = num >> i;
		

		if(b & 1){
			arr[index] = '1';
		}else{
			arr[index] = '0';
		}
		index++;
	} 
	arr[index] = '\0';

	char* result = strdup(arr);

	return result;

	

}

void decimal_to_hex(){

	char buff[20];
	
	char reverse[10];
	


	int i_x = 8;
	int unsigned remainder = 0;

	int index = 0;

	unsigned int dec = con_struct.unsigned_decimal;


	while(dec != 0){
		remainder = dec%16;
		switch(remainder){
			case 10:
				reverse[i_x] = 'A';
				break;
			case 11:
				reverse[i_x] = 'B';
				break;
			case 12:
				reverse[i_x] = 'C';
				break;
			case 13:
				reverse[i_x] = 'D';
				break;
			case 14:
				reverse[i_x] = 'E';
				break;
			case 15:
				reverse[i_x] = 'F';
				break;
			default:
				sprintf(buff, "%d", remainder);
				
				reverse[i_x] = buff[0];
		}

		dec = dec/16;
		index++;
		i_x--;
	}
	for(int p = i_x;p>=2;p--){
		reverse[p] = '0';
	}

	reverse[0] = '0';
	reverse[1] = 'x';
	reverse[9] = '\0';
	
	
	con_struct.hex = strdup(reverse);

}

void check_arguement(char* arguement){
	char pointer[strlen(arguement)];

	if(arguement[0] == '0'){
		if(arguement[1] == 'b'){
			int count = 0;
			for(int i = 2; i<strlen(arguement);i++){
				if(isalpha(arguement[1]) == 0){
					count = -1;
					break;
				
				}
			}
			if(count == 0){
			
				strncpy(pointer, arguement+2,strlen(arguement));
				con_struct.binary = strdup(pointer);
				bin_input();
			}else{
				perror("Invalid Binary input");
			}
		}else{
			if(arguement[1] == 'x'){
				con_struct.hex = strdup(arguement);
				hex_input();
			}
		}
	}
	else{
		
		int count = 0; 
		for(int i = 0; i<strlen(arguement); i++){
			if(isalpha(arguement[i])!=0){
				count = -1;
				break;
			}
		}
		if(count == 0){

			if(con_struct.is_negative){
				con_struct.decimal = 0-atoi(arguement);
				con_struct.unsigned_decimal = (unsigned int)con_struct.decimal;
				dec_input();
			}else{
				con_struct.unsigned_decimal = (unsigned int)(atoi(arguement));
				con_struct.decimal = 0 - con_struct.unsigned_decimal;
				dec_input();
			}

		}else{
			perror("Invalid Decimal Number");
		}

	}
}//check_arguement

void hex_input(){
	bool flag = true;
	hex_to_binary();
	binary_to_decimal();
	print(flag);
}
void dec_input(){
	bool flag = false;
	char* pointer = decimal_to_binary(con_struct.bandwith_sz, con_struct.unsigned_decimal);
	con_struct.binary = strdup(pointer);
	decimal_to_hex();
	print(flag);
}
void bin_input(){
	bool flag = true; 
	binary_to_decimal();
//	decimal_to_binary(con_struct.bandwith_sz, con_struct.unsigned_decimal);
	decimal_to_hex();
	print(flag);
}

void print(bool flag){
	if(flag){ 
		char temp[con_struct.bandwith_sz];
		int difference =con_struct.bandwith_sz - strlen(con_struct.binary);
		int i = 0;
		for(i = 0; i<difference; i++){
			temp[i]='0';
		}
		int index = 0;
		for(int k = i; k<con_struct.bandwith_sz;k++){
			char c = con_struct.binary[index];
			temp[k] = c;
			index++;
		}
	//	temp[index]='\0';
		con_struct.binary = strdup(temp);
	}

	printf("%c", con_struct.binary[0]);
	for(int i = 1; i<strlen(con_struct.binary);i++){
		if((i%4) == 0){
			printf(" ");
		}
		printf("%c", con_struct.binary[i]);
	}
	printf(" (base 2)\n");


	printf("0b");
	printf("%s (base 2)\n", con_struct.binary);
	printf("%s (base 16)\n", con_struct.hex);
	printf("%u (base 10 unsigned) \n", con_struct.unsigned_decimal);
	printf("%d (base 10 signed) \n", con_struct.decimal);
}

int main(int argc, char** argv){

	con_struct.bandwith_sz = 32;
	con_struct.is_negative = false;

	char* arguement;

	if(argc <= 1){
		perror("no arguements");
	}

	char* str1;
	char* str2;
	int index = 0;
	int c;
	opterr = 0;


	for(int i = 1; i<argc; i++){

		if(strcmp(argv[i],"-b")==0){
			con_struct.bandwith_sz = atoi(argv[i+1]);
			flag_b = true;
		}
		if(strcmp(argv[i],"-r")==0){
			con_struct.range = strdup(argv[i+1]);
			flag_r = true;			
		}
		arguement = strdup(argv[i]);
	}

	if(arguement[0] == '-'){
		con_struct.is_negative = true; 
		arguement = strtok(arguement, "-");

	}
	
	check_arguement(arguement);
	return 0;

}//main
