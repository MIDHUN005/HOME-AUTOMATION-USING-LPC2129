#include <LPC21xx.h> 
#define RS (1 << 16)     
#define EN (1 << 17)     
#define BLUETOOTH_TX_PIN (1 << 8)   
#define BLUETOOTH_RX_PIN (1 << 9)   
#define RELAY1_PIN (1 << 10)        
#define RELAY2_PIN (1 << 11)

#define M1 (1<<12)        
#define M2 (1<<13)

void motor_on(void)
{
	IOSET0=M1;
	IOCLR0=M2;
}   
void motor_off(void)
{
	IOCLR0=M1;
	IOCLR0=M2;
}    
void UART1_Init(void);
void UART1_SendChar(char c);
char UART1_ReceiveChar(void);
void LCD_Init(void);
void LCD_Command(char cmd);
void LCD_Char(char data);
void LCD_String(char *str);
void delay_ms(int delay);
void Relay_Control(char command);


int main(void) {
    char receivedChar;
    UART1_Init();
    LCD_Init();
    IODIR0 |= RELAY1_PIN | RELAY2_PIN |M1 |M2;
	IOSET0=	RELAY1_PIN | RELAY2_PIN |M1 |M2;
    LCD_String("Home Automation");
    delay_ms(2000);
    while (1) {
        receivedChar = UART1_ReceiveChar();  
        Relay_Control(receivedChar);
    }
}

void UART1_Init(void) {
    PINSEL0 |= (1 << 16) | (1 << 18);  
    U1LCR = 0x83;                      
    U1DLM = 0;                         
    U1DLL = 97;
    U1LCR = 0x03;                      
}

void UART1_SendChar(char c) {
    while (!(U1LSR & 0x20));           
    U1THR = c;
}

char UART1_ReceiveChar(void) {
    while (!(U1LSR & 0x01));           
    return U1RBR;
}

void LCD_Init(void) {
    IODIR0 |= 0xFF;  
    IODIR0 |= (1 << 16) | (1 << 17);   
    
    LCD_Command(0x01); 
    LCD_Command(0x02); 
    LCD_Command(0x0c);
    LCD_Command(0x38);
	LCD_Command(0x80);
}

void LCD_Command(char cmd) {
    IOCLR0 = 0xFF;        
    IOSET0 = cmd;        
    IOCLR0 = RS;          
    IOSET0 = EN; 
    delay_ms(1);
    IOCLR0 = EN;
	delay_ms(2);
}

void LCD_Char(char data) {
    IOCLR0 = 0xFF; 
    IOSET0 = data;
    IOSET0 = RS;
    IOSET0 = EN;
    delay_ms(1);
    IOCLR0 = EN;
	delay_ms(2);
}

void LCD_String(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}

void delay_ms(int delay) {
    T0PR = 15000 - 1;
    T0TCR = 0x02;       
    T0TCR = 0x01;       
    while (T0TC < delay);  
    T0TCR = 0x00;       
}

void Relay_Control(char command) {
    if (command == 'A') {
        IOCLR0 = RELAY1_PIN; 
        LCD_Command(0x01); 
        LCD_String("Relay 1 ON");
    } 
    else if (command == 'B') {
        IOSET0 = RELAY1_PIN; 
        LCD_Command(0x01); 
        LCD_String("Relay 1 OFF");
    } 
    else if (command == 'C') {
        IOCLR0 = RELAY2_PIN;
        LCD_Command(0x01); 
        LCD_String("Relay 2 ON");
    } 
    else if (command == 'D') {
        IOSET0 = RELAY2_PIN;
        LCD_Command(0x01);
        LCD_String("Relay 2 OFF");
    } 
	else if (command == 'E') {
        motor_on();
        LCD_Command(0x01);
        LCD_String("Motor ON");
    }
	else if (command == 'F') {
        motor_off();
        LCD_Command(0x01);
        LCD_String("Motor OFF");
    }
	else if (command>='G' && command<='Z')
	{
	 	LCD_Command(0x01); 
     	LCD_String("Invalid Command");
	}
}