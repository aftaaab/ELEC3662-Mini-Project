#include "operations.h"

void debug(int debug_value, int secs){
	sprintf(debug_buffer,"%d",debug_value);
	clearDisplay();
	printDisplay(debug_buffer);
	SysTick_Wait(secs*80000000);
	
}
int remove_this_operator_from_operationArray(char operator_to_remove){
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
/* This function starts the calculator code loop*/
void startCalc(){
	clearDisplay();
	arrow_graphic();
	//move_cursor_dir();
	//SendDisplayByte_ins(0xC);
	initial_array_index = 0; //Set main array index to 0.
	while(1){
		checkButtons();
		//move_cursor_dir();//Check buttons pushed.
	}
}
/* This function checks which buttons are pressed and carrys out the appropriate function. */
void checkButtons(){
	//arrow_graphic();
	char num; //Define button pressed variable as char.
	num = return_num(); //Call keyp_shift and move to memory.
	/*
	 *If statements to check which button is pushed.
	 *Then carry out appriate function such as print, equals, or clear
	 *Then move to main array
	*/
	//move_cursor_dir();
	while(num == return_num()){
	if(num == '1'){
		SendDisplayByte_data('1');
		resp_time(1);
		toArray(num);
		}
	if(num == '2'){
		SendDisplayByte_data('2');
		resp_time(1);
		toArray(num);
		}
		if(num == '3'){
			SendDisplayByte_data('3');
			resp_time(1);
			toArray(num);
		}
		if(num == '4'){
			SendDisplayByte_data('4');
			resp_time(1);
			toArray(num);
		}
		if(num == '5'){
		SendDisplayByte_data('5');
			resp_time(1);
			toArray(num);
		}
		if(num == '6'){
		SendDisplayByte_data('6');
			resp_time(1);
			toArray(num);
		}
		if(num == '7'){
		SendDisplayByte_data('7');
			resp_time(1);
			toArray(num);
		}
		if(num == '8'){
		SendDisplayByte_data('8');
			resp_time(1);
			toArray(num);
		}
		if(num == '9'){
		SendDisplayByte_data('9');
			resp_time(1);
			toArray(num);
		}
		if(num == '0'){
		SendDisplayByte_data('0');
			resp_time(1);
			toArray(num);
		}
		if(num == '/'){
			SendDisplayByte_data('/');
			resp_time(1);
			toArray(num);
		}
		if(num == 'x'){
			SendDisplayByte_data('x');
			resp_time(1);
			toArray(num);
		}
		if(num == '-'){
			SendDisplayByte_data('-');
			resp_time(1);
			toArray(num);
		}
		if(num == '+'){
			SendDisplayByte_data('+');
			resp_time(1);
			toArray(num);
		}
		if(num == 'E'){
			SendDisplayByte_data('E');
			resp_time(1);
			toArray(num);
		}
		if(num == '.'){
			SendDisplayByte_data('.');
			resp_time(1);
			toArray(num);
		}
		if(num == 'p'){
			SendDisplayByte_data('p');
			resp_time(1);
			toArray(num);
		}
		if(num == '*'){
			equals();
			arrow_graphic();
		}
		if(num == '#'){
			//overwrite();
			clearcalc();
			arrow_graphic();
			//arrow_graphic();
		}

			//while(GPIO_PORTD_DATA_R & (1<<3) && GPIO_PORTE_DATA_R & (1<<3)) {
				//if(num == '#')
					//clearcalc();
	//}
	}
		//while(return_num() == num){
		//}
}
/* This function starts the appropriate code to show the result. */
void equals(void) {
  setArray(); //Convert main array into 2 seperate arrays. One for numbers, another for operators.
  calculation(); //Carry out bodmas calculation.
}
/* This function moves the pressed button into the main array */
void toArray(char button){
	initial_array[initial_array_index] = button; //initial_array current index is equal to the button pressed.
	initial_array_index++; //Increase index number by 1
}
/* This function moves all the operators and numbers out of the main char array into 2 arrays one made for operators and one made for numbers.*/
void setArray(void) {
  temp_num_index = 0; //Set temp_num_array index to 0
  num_array_index = 0;	//Set num_array index to 0
  op_array_index = 0;	//Set operator Array to 0
	//For loop to go through each number of the initial_array and check if its a digit or operator.
  for (int x = 0; x <= initial_array_index; x++) {
    if (isdigit((int)(initial_array[x]))) { //If the index of the array is a digit then store in digit in the temp_num_array 
      temp_num_array[temp_num_index] = initial_array[x] - '0'; //Store char number to int 
      temp_num_index++; //Increase temp number array index by 1
    } else { //If the index of the array is a operator then store the operator in the op_array and convert the temp number array into the number array as a single number value.
     
			float numbr = 0; //define int of numbr which will be the number generated for the num_array
      op_array[op_array_index] = initial_array[x]; //Move operator into operator array from initial_array
      for (int y = 0; y < temp_num_index; y++) {
        numbr = numbr + temp_num_array[y]; //Add current number to next number in array
				numbr = numbr * 10; //Multiply by 10 for the next number to consturct a whole number.
      }
      num_array[num_array_index] = numbr/10; //Divide by 10 once for loop end. This ensure number is not too big by a factor of 10
      num_array_index++; 		//Increase num_array index by 1
      op_array_index++; 		//Increase op_array index by 1
      temp_num_index = 0; //Reset temp_num_array index to 0
    }
    //final number
    if (x == initial_array_index - 1) { //If on final number then add to number array.
      float numbr = 0; //define int of numbr which will be the number generated for the num_array
      for (int y = 0; y < temp_num_index; y++) {
        numbr = numbr + temp_num_array[y]; //Add current number to next number in array
				numbr = numbr * 10; //Multiply by 10 for the next number to consturct a whole number.
      }

      num_array[num_array_index] = numbr/10; //Divide by 10 once for loop end. This ensure number is not too big by a factor of 10
      num_array_index++; //Increase num_array index by 1
      temp_num_index = 0; //Reset temp_num_array index to 0
    }
  }

}

void calculation(void) {
	SendDisplayByte_ins(0xC);
  char i; //A value used for the for loops
		prev_op_index=-1;
  //count the operator arrays values.
  for (int j = 0; j < op_array_index; j++) {
    if (op_array[j] == '+') { //If '+' found then
      num_add++; //increase num_add by 1
			prev_op_index=j;
		}
    if (op_array[j] == '-') { //If '-' found then
      num_sub++; //increase num_sub by 1
			prev_op_index=j;
    }
    if (op_array[j] == '/') { //If '/' found then
      num_div++; //increase num_div by 1
			prev_op_index=j;
    }
    if (op_array[j] == 'x') { //If '*' found then
      num_mul++; //increase num_mul by 1
			prev_op_index=j;
    }
		if (op_array[j] == 'E') { //If 'E' found then
      num_pow++; //increase num_pow by 1
			prev_op_index=j;
    }
		if (op_array[j] == '.') { //If '.' found then
      num_dec++; //increase num_dec by 1
			prev_op_index=j;
    }
  }

					//If there are additions then find and calculate additions until there are none left.
  if (num_pow != 0) {
    //pow
    while (num_pow != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == 'E') {
          pow_ten(i);		//Calculate additions
          num_pow--;	//Decrease additions count by 1
        }
      }
    }
  }
	
		  //If there are multiplication then find and calculate multiplications until there are none left.
  if (num_mul != 0) {
    while (num_mul != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == 'x') {
          mult(i);			//Calculate multiplication
          num_mul--;	//Decrease multiplication count by 1
        }
      }
    }
  }	
	
		  //If there are subtractions then find and calculate subtractions until there are none left.
  if (num_sub != 0) {
    while (num_sub != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '-') {
          subt(i);		//Calculate subtractions
          num_sub--;	//Decrease subtractions count by 1
        }
      }
    }
}
	
		//If there are additions then find and calculate additions until there are none left.
  if (num_add != 0) {
    //Addition
    while (num_add != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '+') {
          addi(i);		//Calculate additions
          num_add--;	//Decrease additions count by 1
        }
      }
    }
  }
			//If there are divisons then find and calculate divisions until there are none left.
	if (num_div != 0){
  while (num_div != 0) {
    for (i = 0; i < op_array_index; i++) {
      if (op_array[i] == '/') {
        divi(i); 		//Calculate division
        num_div--; //Decrease divison count by 1
      }
    }
  }
}
														//If there are additions then find and calculate additions until there are none left.
  if (num_dec != 0) {
    //pow
    while (num_dec != 0) {
      for (i = 0; i < op_array_index; i++) {
        if (op_array[i] == '.') {
          dec(i);		//Calculate additions
					//remove_this_operator_from_operationArray('.');
          num_dec--;	//Decrease additions count by 1
        }
      }
    }
  }
	
		
  printAnswer(); //Print result to an LCD screen.
}


void overwrite() {
	for(int i=16; i>=0; i--) {
	SendDisplayByte_ins(0x4);
	}
	printDisplay(" ");
	//checkButtons();
	}



/* This function carries out the division and then outputs the result into the num_array and shifts down the numbers.*/
void divi(int i) {
  double _result; //Define new number
  _result = ((double)num_array[i] / (double)num_array[i + 1]); //New number equals the number array index / the number array index plus 1.
  num_array[i] = (float)_result; //place result in array
	if((int)_result != '.' && fmod(_result,2) == 0)
	{sprintf(buffer_div, "%d", (int)num_array[i]);}
	else
	{sprintf(buffer_div, "%f", (double)num_array[i]);}
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the multiplication and then outputs the result into the num_array and shifts down the numbers.*/
void pi(int i) {
  float _result; //Define new number
  _result = (((double)num_array[i]*PI)); //New number equals the number array index * the number array index plus 1.
 // num_array[i] = _result; //place result in array
	sprintf(buffer_pi, "%f", (double)_result);
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the multiplication and then outputs the result into the num_array and shifts down the numbers.*/
void mult(int i) {
  float _result; //Define new number
  _result = ((num_array[i]*num_array[i + 1])); //New number equals the number array index * the number array index plus 1.
  num_array[i] = _result; //place result in array
	sprintf(buffer_mul, "%f", num_array[i]);
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the addition and then outputs the result into the num_array and shifts down the numbers.*/
void addi(int i) {
  int _result; //Define new number
  _result = num_array[i] + num_array[i + 1]; //New number equals the number array index + the number array index plus 1.
  num_array[i] = _result; //place result in array
	sprintf(buffer_add, "%f", num_array[i]);
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the subtraction and then outputs the result into the num_array and shifts down the numbers.*/
void subt(int i) {
  float _result; //Define new number
  _result = num_array[i] - num_array[i + 1]; //New number equals the number array index - the number array index plus 1.
num_array[i] = _result; //place result in array
	sprintf(buffer_sub, "%f", (double)num_array[i]);
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the subtraction and then outputs the result into the num_array and shifts down the numbers.*/
void pow_ten(int i) {
  int _result; //Define new number
  _result = (double)num_array[i] * (pow(10, (double)num_array[i + 1] )); //New number equals the number array index - the number array index plus 1.
	num_array[i] = (float)_result; //place result in array
	int temp=sprintf(buffer_pow, "%.6f", (double)num_array[i]);
	//buffer_pow[4]='\0';
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
}

/* This function carries out the addition and then outputs the result into the num_array and shifts down the numbers.*/
void dec(int i) {
	char temp_buffer[16]={0};
	int size_of_right_part=sprintf(temp_buffer,"%d",(int)num_array[i + 1]);
	double _result =(double)num_array[i] +(((double)num_array[i + 1])/pow(10,size_of_right_part));
	sprintf(buffer_dec,"%lf",_result);

//	char str[]= {0};
//	str[i] = num_array[i] + num_array[i+1];
//  _result = strtod(str, &ptr);	//New number equals the number array index + the number array index plus 1.
//  num_array[i] = _result; //place result in array
//	sprintf(buffer_dec, "%f", num_array[i]);
  //shift back array by 1
  for (int index_shift = i + 1; index_shift <= num_array_index; index_shift++) {
    num_array[index_shift] = num_array[index_shift + 1];
    op_array[index_shift] = op_array[index_shift + 1];
  }
  op_array_index--; //Reduce operator index by 1
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
		else if(op_array[i] == 'p')
			printDisplay(buffer_pi);
		else if(op_array[i] == '.')
			printDisplay(buffer_dec);
		else
			printDisplay("Invalid");
}
	}
/* This function print the answer to the LCD screen*/
void printAnswer(void) {
	int revarray[16];		//Define reverse array
	int revarrayN = 0;	//Define reverse array index
	int negative = 0; //Define negative check. If 1 - Negative number, If 0 - Positive number
	
	
	moveDisplayCursor(0,1,0); //Move cursor to new line
	SendDisplayByte_data('='); //Print Equals symbol
	printDisplay(" "); //Print space
	
	
	//Check if number is negative
	if(num_array[0] < 0){
		num_array[0] = abs(num_array[0]);
		negative = 1;
		//SendDisplayByte_data('-');
	}
	
	
  int value1 = num_array[0]; //define value to split
  while (value1 > 0) { //This loops returns the value in seperate digits in reverse and outputs it to an array
    int digit = value1 % 10; 
		revarray[revarrayN] = digit; //Output digit to array
		revarrayN++; //Increase array index by 1
    value1 /= 10;
  }
	buffer_print();
	while (revarrayN != 0){ //This loop plays the array in reverse and prints the number to the lcd.
		char charvalue = revarray[revarrayN -1] + '0';
		//buffer_print();
		
		//SendDisplayByte_data((float)(charvalue)); //Print number to lcd
		if(revarray[revarrayN -1] == 0){
		}
	revarrayN--; //Decrease reverse array index by 1
	}
	if(num_array[0] == 0){ //if answer is zero then print zero.
		SendDisplayByte_data('0');
	}
	while (return_num() != '#'){ //If clear pressed exit loop
		
	}
	//while(return_num() == '#')
		//clearcalc();
	
}

void clearcalc(void){
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
		buffer_pi[i] = 0;
	}
}
