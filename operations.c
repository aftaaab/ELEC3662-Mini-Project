#include "operations.h"

void debug(int debug_value, int secs){																		//function for debugging purposes
	sprintf(debug_buffer,"%d",debug_value);
	clearDisplay();
	printDisplay(debug_buffer);
	SysTick_Wait(secs*80000000);
	
}
int remove_this_operator_from_operationArray(char operator_to_remove){		// function for removing an operator from op array, for debugging at one point
	char operatorArray_temp[16];
	int new_oP=0;
	for(int i=0;i<op_array_index;i++){
		if(op_array[i]!=operator_to_remove){
			operatorArray_temp[new_oP++]=op_array[i];
		}
}
	for(int i=0;i<new_oP;i++){
		op_array[i]=operatorArray_temp[i];
	}
	op_array_index=new_oP;
	return op_array_index;
	
}

void main_calc(){											// begins the calc routine
	clearDisplay();
	arrow_graphic();
	initial_array_index = 0; 						//Setting the index to 0.
	while(1){
		key_check();											// repeatedly check for keys pressed
	
	}
}

void key_check(){										// checks for key press and displays it and sends it to the initial_array
	//arrow_graphic();
	char num; 
	num = return_num(); 

	while(num == return_num()){
	if(num == '1'){
		SendDisplayByte_data('1');
		resp_time(1);
		send_array(num);
		}
	if(num == '2'){
		SendDisplayByte_data('2');
		resp_time(1);
		send_array(num);
		}
		if(num == '3'){
			SendDisplayByte_data('3');
			resp_time(1);
			send_array(num);
		}
		if(num == '4'){
			SendDisplayByte_data('4');
			resp_time(1);
			send_array(num);
		}
		if(num == '5'){
		SendDisplayByte_data('5');
			resp_time(1);
			send_array(num);
		}
		if(num == '6'){
		SendDisplayByte_data('6');
			resp_time(1);
			send_array(num);
		}
		if(num == '7'){
		SendDisplayByte_data('7');
			resp_time(1);
			send_array(num);
		}
		if(num == '8'){
		SendDisplayByte_data('8');
			resp_time(1);
			send_array(num);
		}
		if(num == '9'){
		SendDisplayByte_data('9');
			resp_time(1);
			send_array(num);
		}
		if(num == '0'){
		SendDisplayByte_data('0');
			resp_time(1);
			send_array(num);
		}
		if(num == '/'){
			SendDisplayByte_data('/');
			resp_time(1);
			send_array(num);
		}
		if(num == 'x'){
			SendDisplayByte_data('x');
			resp_time(1);
			send_array(num);
		}
		if(num == '-'){
			SendDisplayByte_data('-');
			resp_time(1);
			send_array(num);
		}
		if(num == '+'){
			SendDisplayByte_data('+');
			resp_time(1);
			send_array(num);
		}
		if(num == 'E'){
			SendDisplayByte_data('E');
			resp_time(1);
			send_array(num);
		}
		if(num == '.'){
			SendDisplayByte_data('.');
			resp_time(1);
			send_array(num);
		}
		if(num == '*'){
			result_function();
			arrow_graphic();
		}
		if(num == '#'){
			//overwrite();
			reset_calc();
			arrow_graphic();
			//arrow_graphic();
		}
	}
}

void result_function(void) {				// function which executes upon pressing equal (*) and this calls split_array() and then calculator()
  split_array(); 										//divides the initial_array into 2 seperate arrays, for num and op
  calculator(); 										//does the calculation
}

void send_array(char button){										// function where the pressed key (button) is loaded into the initial_array
	initial_array[initial_array_index] = button; //initial_array index is the same as key pressed.
	initial_array_index++; 												//Increment index
}

void split_array(void) {																				// function which loads all the ops and nums from the initial_array into 2 arrays for op and num.
  temp_num_index = 0; 																					//Set all the array indices to 0
  num_array_index = 0;				
  op_array_index = 0;					
	
  for (int x = 0; x <= initial_array_index; x++) {  						// loop to iterate through every number of the initial_array and then checks if it is a num or op.
    if (isdigit((int)(initial_array[x]))) { 										//If it is a number then store in temp_num_array 
      temp_num_array[temp_num_index] = initial_array[x] - '0'; 	//Storing a char in an int variable 
      temp_num_index++; 																				// increment index
    } else { 																										// if op then load it into op_array and convert the temp number array into the number array as a single number value.
     
			float value_1 = 0; 																				// value_1 of type float which will be the number generated for the num_array
      op_array[op_array_index] = initial_array[x]; 							//Move operator into operator array from initial_array
      for (int y = 0; y < temp_num_index; y++) {
        value_1 = value_1 + temp_num_array[y]; 									//Adding a current number to the next num in array
				value_1 = value_1 * 10; 																//Multiplying with 10 for next num to become a whole number.
      }
      num_array[num_array_index] = value_1/10; 									// divide the number by 10 as the loop ends which ensures the number is not large by a 10s factor
      num_array_index++; 																				// num and op array index incremented
      op_array_index++; 																				
      temp_num_index = 0; 																			//Resetting temp_num_array index
    }
    
    if (x == initial_array_index - 1) { 												//if it reaches the final number then add to the temp_number_array
      float value_1 = 0; 																				
      for (int y = 0; y < temp_num_index; y++) {
        value_1 = value_1 + temp_num_array[y]; 									
				value_1 = value_1 * 10; 																
      }

      num_array[num_array_index] = value_1/10; 
      num_array_index++; 																					
      temp_num_index = 0; 																				//Resetting
    }
  }

}

void calculator(void) {
	SendDisplayByte_ins(0xC);
  char i; 
		prev_op_index=-1;																						// used for debugging
																																//loop for setting op_array values by checking and incrementing the respective num_"op"
  for (int j = 0; j < op_array_index; j++) {
    if (op_array[j] == '+') { 																		
      num_add++; 
			prev_op_index=j;
		}
    if (op_array[j] == '-') { 
      num_sub++; 
			prev_op_index=j;
    }
    if (op_array[j] == '/') {
      num_div++; 
			prev_op_index=j;
    }
    if (op_array[j] == 'x') {
      num_mul++; 
			prev_op_index=j;
    }
		if (op_array[j] == 'E') { 
      num_pow++; 
			prev_op_index=j;
    }
		if (op_array[j] == '.') { 
      num_dec++; 
			prev_op_index=j;
    }
  }

					//If pow found then find and calculate until reaches a count of 0
  if (num_pow != 0) {
    while (num_pow != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == 'E') {
          pow_ten(i);		
          num_pow--;	
        }
      }
    }
  }
	
		  //If mul found then find and calculate until reaches a count of 0
  if (num_mul != 0) {
    while (num_mul != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == 'x') {
          mult(i);			
          num_mul--;	
        }
      }
    }
  }	
	
		 //If sub found then find and calculate until reaches a count of 0
  if (num_sub != 0) {
    while (num_sub != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '-') {
          subt(i);		
          num_sub--;	
        }
      }
    }
}
	
	//If add found then find and calculate until reaches a count of 0
  if (num_add != 0) {
    //Addition
    while (num_add != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '+') {
          addi(i);		
          num_add--;	
        }
      }
    }
  }
			//If div found then find and calculate until reaches a count of 0
	if (num_div != 0){
  while (num_div != 0) {
    for (i = 0; i < op_array_index; i++) {
      if (op_array[i] == '/') {
        divi(i); 	
        num_div--; 
      }
    }
  }
}
														//If dec found then find and calculate until reaches a count of 0
  if (num_dec != 0) {
    while (num_dec != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '.') {
          dec(i);		
					//remove_this_operator_from_operationArray('.');
          num_dec--;
        }
      }
    }
  }
	
  display_result(); 
}



void divi(int i) {															// function which does the division and then stores the result into a specific buffer array and shifts down the numbers
  double _result;
  _result = ((double)num_array[i] / (double)num_array[i + 1]);
  num_array[i] = (float)_result; 																//place result in array
	if((int)_result != '.' && fmod(_result,2) == 0)	// fmod takes the modulo of floating point values, if no decimal and is divisible by 2 then store as a int value in buffer
	{sprintf(buffer_div, "%d", (int)num_array[i]);}
	else
	{sprintf(buffer_div, "%f", (double)num_array[i]);}	// otherwise as float in buffer

  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {		  //shifting back the array by 1
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 																	// decrement op_array_index
}



void mult(int i) {													// function which does the multiplication and then stores the result into a specific buffer array and shifts down the numbers																		
  float _result; 
  _result = ((num_array[i]*num_array[i + 1])); 
  num_array[i] = _result; 
	sprintf(buffer_mul, "%f", (double)num_array[i]);

  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 
}


void addi(int i) {													// function which does the addition and then stores the result into a specific buffer array and shifts down the numbers		
  float _result; 
  _result = num_array[i] + num_array[i + 1]; 
  num_array[i] = _result; 
	sprintf(buffer_add, "%f", (double)num_array[i]);
  
  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 
}


void subt(int i) {												// function which does the subtraction and then stores the result into a specific buffer array and shifts down the numbers
  float _result; 
  _result = num_array[i] - num_array[i + 1]; 
	num_array[i] = _result; 
	sprintf(buffer_sub, "%f", (double)num_array[i]);

  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 
}


void pow_ten(int i) {										// function which does the pow and then stores the result into a specific buffer array and shifts down the numbers
  int _result; 
  _result = (double)num_array[i] * (pow(10, (double)num_array[i + 1] )); 
	num_array[i] = (float)_result; 
	sprintf(buffer_pow, "%.6f", (double)num_array[i]);

  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 
}


void dec(int i) {											// function which does the decimal and then stores the result into a specific buffer array and shifts down the numbers
	char temp_buffer[16]={0};
	int size_of_right_part=sprintf(temp_buffer,"%d",(int)num_array[i + 1]);
	double _result =(double)num_array[i] +(((double)num_array[i + 1])/pow(10,size_of_right_part));
	sprintf(buffer_dec,"%lf",_result);


  for (int index_shift = i+1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; 
}

void buffer_print() {
	for(int i=0; i<op_array_index; i++) {
	if(op_array[i] == '+')
			printDisplay(buffer_add);
		else if(op_array[i] == '-')
			printDisplay(buffer_sub);
		else if(op_array[i] == 'x')
			printDisplay(buffer_mul);
		else if(op_array[i] == '/')
			printDisplay(buffer_div);
		else if(op_array[i] == 'E')
			printDisplay(buffer_pow);
		else if(op_array[i] == '.')
			printDisplay(buffer_dec);
		else
			printDisplay("Invalid");
}
	}

void display_result(void) {
	int back_array[16];													//array for taking the seperate digits in reverse order
	int back_array_index = 0;										//index for the array above
	int neg_check = 0; 													//Define neg_check check. If 1 - neg_check number, If 0 - Positive number
	
	
	moveDisplayCursor(0,1,0); 									//Move cursor to line 2
	SendDisplayByte_data('='); 	
	printDisplay(" "); 					
	
	
	
	if(num_array[0] < 0){													// checks if num is negative
		num_array[0] = abs(num_array[0]);
		neg_check = 1;
		//SendDisplayByte_data('-');
	}
		
  int value1 = (int)num_array[0]; 
  while (value1 > 0) { 															// returns the value in seperate digits in reverse and stores it to an array
    int output_value = value1 % 10; 
		back_array[back_array_index] = output_value; 		// output_value to array
		back_array_index++; 														//Increment index
    value1 /= 10;
  }
	buffer_print();																		// calls buffer_print which prints the specific buffer to the LCD which has an operation result inside

	if(num_array[0] == 0){ 											//if answer is zero then print zero.
		SendDisplayByte_data('0');
	}
	while (return_num() != '#'){ 								//If clear pressed exit loop
	}
}

void reset_calc(void){
	clearDisplay(); //Clear lcd and return to home
	//Set default values
	initial_array_index = 0; 
	temp_num_index = 0;
	num_array_index = 0;
	op_array_index = 0;
	
	//Reset arrays to zero.
	for (int i=0; i <16; ++i){
	temp_num_array[i] = 0;
	num_array[i] = 0;
	op_array[i] = 0;
	initial_array[i] = 0;
	}
	
	for (int i=0; i<10; i++) {
		buffer_add[i]= 0;
		buffer_sub[i]= 0;
		buffer_mul[i]= 0;
		buffer_div[i]= 0;
		buffer_pow[i]= 0;
		buffer_dec[i] = 0;
	}
}
