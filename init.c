#include "init.h"
#include "operations.h"
#include "password.h"
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
unsigned static char keyp_num[4][4] = { 	  {'1', '2', '3', '+'},					//{1, 2, 3, A,
						  {'4', '5', '6', '-'},					// 4, 5, 6, B,
						  {'7', '8', '9', '.'},					// 7, 8, 9, C,
						  {'*', '0', '#', ' '}					// *, 0, #, D}
					};

unsigned static char keyp_num_s[4][4] = { 	  {'1', '2', '3', 'x'},					//{1, 2, 3, A,
						  {'4', '5', '6', '/'},					// 4, 5, 6, B,
						  {'7', '8', '9', 'E'},					// 7, 8, 9, C,
						  {'*', '0', '#', ' '}					// *, 0, #, D}	
					};
																		
unsigned static char icon_1[] = {0x04,0x0E,0x15,0x11,0x11,0x11,0x0A,0x04};
unsigned static char icon_2[] = {0x04,0x0A,0x11,0x15,0x15,0x11,0x0A,0x04};
unsigned static char icon_3[] = {0x04,0x0A,0x11,0x11,0x11,0x15,0x0E,0x04};
unsigned static char arrow[] = 	{0x08,0x04,0x02,0x1F,0x02,0x04,0x08,0x00};
unsigned static char pass_icon1[] = {0x00,0x04,0x0E,0x1B,0x11,0x1B,0x0E,0x04};
unsigned static char pass_icon2[] = 	{0x1F,0x1B,0x11,0x04,0x0E,0x04,0x11,0x1B};

static unsigned long index=0;

unsigned static char new_pwd[] = " ";
static char pwd[] = " ";



void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 		|= 0x1;    	// 1) A clock
  delay 		        = SYSCTL_RCGC2_R; 	//    delay          
  GPIO_PORTA_AMSEL_R 	        &= 0x00;        		// 2) disable analog function
  GPIO_PORTA_PCTL_R 	        &= 0x00000000;   		// 3) GPIO clear bit PCTL  
  GPIO_PORTA_DIR_R 		|= 0xC;          		// 4) PA2 and PA3 outputs  
  GPIO_PORTA_AFSEL_R 	        &= 0x00;        		// 5) no alternate function      
  GPIO_PORTA_DEN_R 		|= 0xC;           	// 6) enable digital pins PA2 and PA3 (RS and E resp)       
}

void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 		|= 0x2;     	// 1) B clock
  delay 		         = SYSCTL_RCGC2_R;  	//    delay          
  GPIO_PORTB_AMSEL_R 	        &= 0x00;        	 	// 2) disable analog function
  GPIO_PORTB_PCTL_R 	        &= 0x00000000;   		// 3) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R 		|= 0x0F;          	// 4) PB0-3 LCD outputs    
  GPIO_PORTB_AFSEL_R 	        &= 0x00;        		// 5) no alternate function      
  GPIO_PORTB_DEN_R 		|= 0x0F;          	// 6) enable digital pins PB0-3     
}

void PortD_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 		|= 0x8;     	// D clock
  delay 			= SYSCTL_RCGC2_R;  	//    delay
  GPIO_PORTD_LOCK_R		= 0x4C4F434B;				// unlock port D
  GPIO_PORTD_AMSEL_R 	        &= 0x00;        		// disable analog function
  GPIO_PORTD_PCTL_R 	        &= 0x00000000;   		// GPIO clear bit PCTL  
  GPIO_PORTD_DIR_R 		|= 0x0F;          	// PD0-3 outputs  (keypad cols as output to PD)
  GPIO_PORTD_AFSEL_R 	        &= 0x00;        		// no alternate function      
  GPIO_PORTD_DEN_R 		|= 0x0F;           	// enable digital pins PD0-3        
}

void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 		|= 0x10;     	// E clock
  delay 			= SYSCTL_RCGC2_R;  	//    delay          
  GPIO_PORTE_AMSEL_R 	        &= 0x00;        		// disable analog function
  GPIO_PORTE_PCTL_R 	        &= 0x00000000;   		// GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R 		|= 0x00;          	// PE0-3 inputs  (keypad rows as input from PE)
  GPIO_PORTE_AFSEL_R 	        &= 0x00;        		// no alternate function
  GPIO_PORTE_PDR_R 		|= 0x0F;           	// enable pulldown resistor on pins PE0-3 	
  GPIO_PORTE_DEN_R 		|= 0x0F;           	// enable digital pins PE0-3        
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R |= 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R &= ~0x11;          // 5.1) PF4,PF0 input,  
  GPIO_PORTF_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R |= 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R |= 0x1F;          // 7) enable digital pins PF4-PF0     
}


unsigned char return_num() {
	while(GPIO_PORTD_DATA_R & (1<<3) && GPIO_PORTE_DATA_R & (1<<3)) {										// while shifted (D is pressed)
		SysTick_Wait(8000000);
	for(unsigned char i=0; i<4; i++)												// check each row 0-3
	{
		GPIO_PORTD_DATA_R = (1<<i);			// row 1 scan when i = 0, row 2 (i=1)....row 4 (i=3)
		SysTick_Wait(8000000);										// 10ms delay
		
		for(unsigned char j=0; j<4; j++) {								// check cols
			if(GPIO_PORTE_DATA_R & (1 <<j)) {
					SysTick_Wait(240000000);
					//SendDisplayByte_data(keyp_num_s[j][i]);
					return keyp_num_s[j][i];													// returns the shifted keyp_num array element
			}
		}
	}	
}
	
	while(!(GPIO_PORTD_DATA_R & (1<<3) && GPIO_PORTE_DATA_R & (1<<3))) {						// while not shifted (D is not pressed)
		SysTick_Wait(8000000);
	for(unsigned char i=0; i<4; i++)												// check each row 0-3
	{
		GPIO_PORTD_DATA_R = (1<<i);			// row 1 scan when i = 0, row 2 (i=1)....row 4 (i=3)
		SysTick_Wait(8000000);										// 10ms delay
		
		for(unsigned char j=0; j<4; j++) {								// check cols
			if(GPIO_PORTE_DATA_R & (1 <<j)) {
					SysTick_Wait(240000000);
					//SendDisplayByte_data(keyp_num[j][i]);
					return keyp_num[j][i];													// returns the normal keyp_num array element
			}
		}
	}	
}
	}

unsigned char send_pass() {																	// same function but with the non shifted part for password as numbers are only needed for password
	while(!(GPIO_PORTD_DATA_R & (1<<3) && GPIO_PORTE_DATA_R & (1<<3))) {
		SysTick_Wait(8000000);
	for(unsigned char i=0; i<4; i++)												// check each row 0-3
	{
		GPIO_PORTD_DATA_R = (1<<i);			// row 1 scan when i = 0, row 2 (i=1)....row 4 (i=3)
		SysTick_Wait(8000000);										// 10ms delay
		
		for(unsigned char j=0; j<4; j++) {								// check cols
			if(GPIO_PORTE_DATA_R & (1 <<j)) {
					SysTick_Wait(240000000);
					SendDisplayByte_data(keyp_num[j][i]);
				return keyp_num[j][i];
			}
		}
	}	
}
}

	
void InitDisplayPort(void) {
	GPIO_PORTA_DATA_R = 0x0;								// clearing Ports A and B
	GPIO_PORTB_DATA_R = 0x0;
	SysTick_Wait(1280000); 									// 16ms delay after power on
	SendDisplayNibble_ins(0x3);
	SysTick_Wait(400000);										// 5ms del
	SendDisplayNibble_ins(0x3);
	SysTick_Wait(12000);										// 150us del
	SendDisplayNibble_ins(0x3);
	SysTick_Wait(2960);											// 37us del
	SendDisplayNibble_ins(0x2);
	//SysTick_Wait(2960);
	SendDisplayByte_ins(0x28);							// N = 1, F = 0 (2 disp lines, 5x8 dots) (0x02 + 0x08)
	SendDisplayByte_ins(0x08);
	SendDisplayByte_ins(0x01);
	SendDisplayByte_ins(0x07); 							// I/D = 1 (inc), S = 1 (shifting)
	}

void SendDisplayNibble_ins(unsigned long nibble) {
	//nibble							= GPIO_PORTB_DATA_R&0xF0;						// stores DB7-4 nibble value
	RS = 0x00;														// RS = 0 PA3 (ins mode)
	GPIO_PORTA_DATA_R &= ~RS;
	GPIO_PORTB_DATA_R = nibble;
	EN = 0x04;														// setting EN PA2
	SysTick_Wait(36);												// pulse width duration 450ns (delay param = 36)
	EN = 0x00;													// clearing EN	
}
	

void SendDisplayNibble_data(unsigned long nibble) {
	//nibble						= GPIO_PORTB_DATA_R&0xF0;						// stores DB7-4 nibble value
	RS = 0x8;
	GPIO_PORTA_DATA_R |= RS;
	GPIO_PORTB_DATA_R = nibble;
	EN = 0x04;														// setting EN PA2
	SysTick_Wait(36);												// pulse width duration 450ns (delay param = 36)
	EN = 0x00;													// clearing EN	
}
	

void SendDisplayByte_ins(unsigned long byte){			// nib2 is lower order, nib1 is higher order bits
	//unsigned long byte 	= nibble_1 | (nibble_2 << 4); 			// byte = (nib2 nib1)
	unsigned long nibble_1 = (byte&0xF0) >> 4 ;
	unsigned long nibble_2 = byte&0x0F;	
	SysTick_Wait(2960);
	SendDisplayNibble_ins(nibble_1);
	SysTick_Wait(2400);
	SendDisplayNibble_ins(nibble_2);
}

void SendDisplayByte_data(unsigned long byte) {
	unsigned long nibble_1 = (byte&0xF0) >> 4 ;
	unsigned long nibble_2 = byte&0x0F;	
	SysTick_Wait(2960);
	SendDisplayNibble_data(nibble_1);
	SysTick_Wait(2400);
	SendDisplayNibble_data(nibble_2);
}

void printDisplay(char *word) {
	while((*word)!='\0') {
	SendDisplayByte_data(*word);
	SysTick_Wait(80000);					//1ms del
	word++;
	}
	SysTick_Wait(80000);
	SendDisplayByte_data(' ');
	SysTick_Wait(80000);
	SendDisplayByte_ins(0x10);	
}

void Load_lcd() {
			moveDisplayCursor(0,0,0);
			printDisplay("L"); SysTick_Wait(900000000);
			printDisplay("o"); SysTick_Wait(900000000);
			printDisplay("a"); SysTick_Wait(900000000);
			printDisplay("d"); SysTick_Wait(900000000);
			printDisplay("i"); SysTick_Wait(900000000);
			printDisplay("n"); SysTick_Wait(900000000);
			printDisplay("g"); SysTick_Wait(900000000);
			printDisplay(" "); SysTick_Wait(900000000);
}

void pass_lcd() {
			moveDisplayCursor(0,0,0);
			printDisplay("S"); SysTick_Wait(900000000);
			printDisplay("e"); SysTick_Wait(900000000);
			printDisplay("t"); SysTick_Wait(900000000);
			printDisplay("t"); SysTick_Wait(900000000);
			printDisplay("i"); SysTick_Wait(900000000);
			printDisplay("n"); SysTick_Wait(900000000);
			printDisplay("g"); SysTick_Wait(900000000);
			printDisplay(" "); SysTick_Wait(900000000);
}


void graphic_create(unsigned char *custom, char loc) {		//responsible for making a custom graphic which stores inside the CGRAM
	SendDisplayByte_ins(0x40+(loc*8));											// loc can take values from 0-8 and 0x40 is the first block in CGRAM for storing such custom elements
	for(int i=0; i<8; i++) {
		SendDisplayByte_data(custom[i]);
	}
}


void start() {
	clearDisplay();
	printDisplay("LCD Calculator");
	moveDisplayCursor(0,1,0);
	printDisplay("by - Aftab M");
	SendDisplayByte_ins(0xC);
	resp_time(100);
}

void arrow_graphic() {					// displays an arrow 
	//SendDisplayByte_ins(0xC);
	//clearDisplay();
	graphic_create(arrow, 3);			// loc is 3, hence the location is 0x64
	
	SendDisplayByte_ins(0x80);		// cursor goes to home
	SendDisplayByte_data(3);			// displays the arrow stored at loc = 3
	SysTick_Wait(40000000);				// random amount of delay
	
}

void load_graphic() {
	SendDisplayByte_ins(0xC);			//disp on, cursor off
	clearDisplay();
	graphic_create(icon_1, 0);		// three custom characters for an animation sequence at loc = 0,1 and 2
	graphic_create(icon_2, 1);
	graphic_create(icon_3, 2);
	
	for(int i=0; i<3; i++) {			// loop for displaying the sequence
		Load_lcd();
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(0);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(1);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(2);
		SysTick_Wait(40000000);
		
		
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(2);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(1);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(0);
		SysTick_Wait(40000000);
}
}

void pass_graphic() {								//same as prev function
	SendDisplayByte_ins(0xC);
	clearDisplay();
	graphic_create(pass_icon1, 4);
	graphic_create(pass_icon2, 5);
	//graphic_create(icon_3, 2);
	
	for(int i=0; i<3; i++) {
		pass_lcd();
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(4);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(5);
		SysTick_Wait(40000000);
	
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(5);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(4);
		SysTick_Wait(40000000);
		
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(4);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(5);
		SysTick_Wait(40000000);
		
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(5);
		SysTick_Wait(40000000);
		SendDisplayByte_ins(0x88);
		SendDisplayByte_data(4);
		SysTick_Wait(40000000);
}
}

void moveDisplayCursor(unsigned long X, unsigned long Y, unsigned long Z) { 		// x are cols and y are the 2 rows (0 and 1) on the LCD 16x2 and Z remains 0
	SendDisplayByte_ins((0x80 + X + (Y*40)) - Z);
	SysTick_Wait(4000000); 						// 50m del
}

void clearDisplay() {
	SendDisplayByte_ins(0x01);				// clear
	SysTick_Wait(128000); 					// 1.6ms del
	SendDisplayByte_ins(0x02);				// home
	SysTick_Wait(128000);
}


//void move_cursor_dir() {
//		return_num();
//	  while(1){
//		SW1 = GPIO_PORTF_DATA_R&0x10; // PF4 into SW1
//		SW2 = GPIO_PORTF_DATA_R&0x01; // PF0 into SW2
//			SendDisplayByte_ins(0xE);			//cursor on
//			while(SW1 == 0x00){
//			if(SW1 == 0x00) {
//			SysTick_Wait(40000000);				//500ms del
//			SendDisplayByte_ins(0x10);															// move cursor left (dir 0)
//			//printDisplay(" ");
//			SysTick_Wait(40000000);				//500ms del
//			}
//		}
//			while(SW2 == 0x00){
//			if(SW2 == 0x00){
//			SysTick_Wait(40000000);				//500ms del
//			SendDisplayByte_ins(0x14);															// move cursor right (dir 1)
//			//printDisplay(" ");
//			SysTick_Wait(40000000);				//500ms del
//	}
//}
//  }
//}


//void lcd_left(unsigned char L) {
//	unsigned char count;
//	for(count=0; count<L; count++) {
//		SysTick_Wait(24000000);
//		SendDisplayByte_ins(0x18);
//		SysTick_Wait(24000000);			//300ms del
//	}
//}

//void lcd_right(unsigned char R) {
//	unsigned char count;
//	for(count=0; count<R; count++) {
//		SendDisplayByte_ins(0x1C);
//		SysTick_Wait(24000000);			//300ms del
//	}
//}

void mess1() {
	clearDisplay();
	printDisplay("Select mode:");
	//SendDisplayByte_ins(0xC);
	resp_time(16);
}

void mess2() {
	clearDisplay();
	printDisplay("1-> Arithmetic");
	SysTick_Wait(24000000);
	moveDisplayCursor(0,1,0);
	printDisplay("2-> Set Pass");
	SysTick_Wait(24000000);
	SendDisplayByte_ins(0xC);
}

void resp_time(unsigned long time) {
	for(unsigned long i=0; i<time; i++) {
		SysTick_Wait(240000000); // 3s del
	}
}

void menu() {
	unsigned char md;
	mess1();
	SysTick_Wait(240000000);
	clearDisplay();
	SysTick_Wait(240000000);
	mess2();
	resp_time(10);
	md = return_num();
	
	switch(md) {
		case '1': 
			clearDisplay();
			arrow_graphic(); SendDisplayByte_ins(0xE); main_calc();//operation();
			break;
			
		case '2':
			clearDisplay();
			printDisplay("Change Password: ");
			moveDisplayCursor(0,1,0);
			SendDisplayByte_ins(0xE);
			change_pass();
			break;
	
}
	}

void change_pass() {
		char new_pass[4];
		unsigned long new_word=0;
		int fg=0;
		while(fg == 0) {
			for(index=0; index<4; index++) {
			new_pass[index] = send_pass(); 
			new_pwd[index] = new_pass[index];
				if(index == 3)
				{fg=1;}
			}
		}
						
		for(int i=0; i<4; i++) {
			new_word += (unsigned long)(pow(10, (4-i-1)) * (new_pwd[i] - '0'));
		}

			resp_time(50);
			eeSetPass((int)new_word);
			resp_time(1);
			clearDisplay();
			SendDisplayByte_ins(0xC);
			pass_graphic();
			clearDisplay();
			printDisplay("Password Set!");
			moveDisplayCursor(0,1,0);
			printDisplay("New Pass: ");
			printDisplay(new_pwd);
	}
	
void ask_pass() {
	char pass[4];
	unsigned long word=0;
	BEGIN:
	printDisplay("Enter Password: ");
	moveDisplayCursor(0,1,0);
		int fg=0;
		while(fg == 0) {
			resp_time(1);
			for(index=0; index<4; index++) {
			pass[index] = send_pass(); 
			pwd[index] = pass[index];
				if(index == 3)
				{fg=1;}
			}
		}
		
		for(int i=0; i<4; i++) {
		 resp_time(1);
			word += (unsigned long)(pow(10, (4-i-1)) * (pwd[i] - '0'));  		// converting string to int
		}
		
		if(word == eeGetPass()) {
			clearDisplay();
			SysTick_Wait(40000);
			start();
			load_graphic();
	}
	else {
		fg = 0;
		clearDisplay();
		resp_time(10);
		printDisplay("Wrong!!");
		//clearDisplay();
		resp_time(10);
		clearDisplay();
		goto BEGIN;
	}
}
	

	
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R |= 0x00FFFFFF;        // max reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it             
  NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock (EN (bit 0) and CLK_SRC (bit 2) set)
}

void PLL_Init(void){
																								// 0) Use RCC2
  SYSCTL_RCC2_R |=  0x80000000;  								// USERCC2
																								// 1) bypass PLL while initializing
  SYSCTL_RCC2_R |=  0x00000800;  								// BYPASS2, PLL bypass
																								// 2) select the crystal value and oscillator source
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   	// clear XTAL field, bits 10-6
                 + 0x00000540;   								// 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  								// configure for main oscillator source
																								// 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~0x00002000;
																								// 4) set the desired system divider
  SYSCTL_RCC2_R |= 0x40000000;   								// use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      							// configure for 80 MHz clock 
																								// 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&0x00000040)==0){}  				// wait for PLLRIS bit
																								// 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~0x00000800;
}

// The delay parameter is in units of the 80 MHz core clock (12.5 ns)
void SysTick_Wait(unsigned long long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
