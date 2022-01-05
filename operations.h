#include"init.h"
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>

//Define global variables
static int temp_num_index = 0; 						//temp_num_array index number. This is used to keep count of how big the array is without complex code.
static int num_array_index = 0;							//num_array index number. This is used to keep count of how big the array is without complex code.
static int op_array_index = 0;							//op_array index number. This is used to keep count of how big the array is without complex code.
static char initial_array[16];				//Where all the raw input is stored one button at a time.
static int initial_array_index = 0;				//initial_array index number. This is used to keep count of how big the array is without complex code.
static float temp_num_array[16];	//This is where temporary numbers are stored while converting the main array into the operator array and number array.
static float num_array[16];			//This is where the numbers of the equation are stored.
static char op_array[16];		//This is where the operator of the equation are stored.
	
static int num_div = 0; //How many divisions are in the equation
static int num_mul = 0; //How many multiplications are in the equation
static int num_add = 0; //How many additions are in the equation
static int num_sub = 0; //How many subtractions are in the equation
static int num_pow = 0;
static int num_dec = 0;
static int num_pi  = 0;
static float deccnum;
static char debug_buffer[16]={0};
static char buffer_div[10]={0};
static char buffer_add[10]={0};
static char buffer_mul[10]={0};
static char buffer_sub[10]={0};
static char buffer_pow[10]={0};
static char buffer_dec[10]={0};
static char buffer_pi[10]={0};
static int prev_op_index = -1;

void debug(int debug_value, int secs);
int remove_this_operator_from_operationArray(char operator_to_remove);
void startCalc(void);
void checkButtons(void);
void equals(void);
void toArray(char button);
void setArray(void);
void calculation(void);
void divi(int i);
void subt(int i);
void addi(int i);
void mult(int i);
void pow_ten(int i);
void dec(int i);
void pi(int i);
void buffer_print(void);
void printAnswer(void);
void clearcalc(void);
