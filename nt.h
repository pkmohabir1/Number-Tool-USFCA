#include <stdbool.h>
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

struct conversion{
	char* binary;
	char* hex;
	char* range;
	int decimal;
	unsigned int unsigned_decimal;
	int bandwith_sz;
	bool is_negative;
};

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






