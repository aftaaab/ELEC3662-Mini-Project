// All port definitions
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
	
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_LOCK_R				(*((volatile unsigned long *)0x40007520))	
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

#define SYSCTL_RIS_R          	(*((volatile unsigned long *)0x400FE050))	
#define SYSCTL_RCC_R          	(*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         	(*((volatile unsigned long *)0x400FE070))	
#define NVIC_ST_CTRL_R        	(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      	(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     	(*((volatile unsigned long *)0xE000E018))


#define RS								 			(*((volatile unsigned long *)0x40004020))  //PA3 register select pin
#define EN  										(*((volatile unsigned long *)0x40004010))     //PA2 enable pin

#define PI 3.14159265358979



// function prototypes

void PortA_Init(void);
void PortB_Init(void);
void PortD_Init(void);
void PortE_Init(void);
void PortF_Init(void);
void InitDisplayPort(void);
void SendDisplayNibble_ins(unsigned long nibble);
void SendDisplayNibble_data(unsigned long nibble);
void SendDisplayByte_ins(unsigned long byte);
void SendDisplayByte_data(unsigned long byte);
unsigned long SendToDisplay(unsigned char data);
//void end_input(void);
void graphic_create(unsigned char *custom, char loc);
void load_graphic(void);
void pass_graphic(void);
void change_pass(void);
void arrow_graphic(void);
float calc(float n1, float n2, char function);
void identifyKey(char volatile key);
char returnNumber(char a, char b, char c);
void start(void);
void moveDisplayCursor(unsigned long X, unsigned long Y, unsigned long Z);
void printDisplay(char *word);
unsigned char keyp_scan(int shift);
unsigned char send_pass(void);
void disp_keypad(unsigned char tmp);
void Load_lcd(void);
void pass_lcd(void);
void clearDisplay(void);
void SysTick_Init(void);
void PLL_Init(void);
void SysTick_Wait(unsigned long long delay);
unsigned char enter_num(void);
void lcd_left(unsigned char L);
void lcd_right(unsigned char R);
void mess1(void);
void mess2(void);
unsigned long sec_num(void);
unsigned char return_num(void);
unsigned char return_pass(void);
void resp_time(unsigned long time);
void menu(void);
void operation(void);
void lcd_add(void);
void lcd_sub(void);
void lcd_mul(void);
void lcd_div(void);
void lcd_pow_ten(void);
void numprint(int num);
unsigned char keyp_shift(void);
void del_char(void);
void overwrite(void);
void move_cursor_dir(void);
void ask_pass(void);
void flash_pass(void);