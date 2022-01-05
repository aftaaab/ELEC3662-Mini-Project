#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include "TExaS.h"
#include "TM4C123GH6PM.h"
#include "UART.h"
#include "operations.h"
#include "password.h"

int main(void){
	// initialisations
	PortA_Init();
	PortB_Init();
	PortD_Init();
	PortE_Init();
	PortF_Init();
	SysTick_Init();
  PLL_Init();
	eepromInit();
	InitDisplayPort();
	
	
		SendDisplayNibble_ins(0x2);
		SendDisplayByte_ins(0x22);
		SysTick_Wait(118000);				// 1475us delay
		SendDisplayByte_ins(0x0F);

			
			//pass_graphic();
			ask_pass();
			menu();
			//move_cursor_dir();
}
