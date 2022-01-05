#include"init.h"
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>

//Define global variables
static int temp_num_index = 0; 						
static int num_array_index = 0;							
static int op_array_index = 0;							
static char initial_array[16];				
static int initial_array_index = 0;				
static float temp_num_array[16];	
static float num_array[16];			
static char op_array[16];		
	
static int num_div = 0; 
static int num_mul = 0; 
static int num_add = 0; 
static int num_sub = 0; 
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
void main_calc(void);
void key_check(void);
void result_function(void);
void send_array(char button);
void split_array(void);
void calculator(void);
void divi(int i);
void subt(int i);
void addi(int i);
void mult(int i);
void pow_ten(int i);
void dec(int i);
void pi(int i);
void buffer_print(void);
void display_result(void);
void reset_calc(void);
