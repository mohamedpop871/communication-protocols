#include "USART.h"


void INIT_UART(int BAUD){
	UBRR0 = (F_CPU/16/BAUD)-1;
	UCSR0B |= 1 << TXEN0;
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01;
}

void USART_TX(char data )
{
	/* Put data into buffer, sends the data */
	UDR0 = data;
	/* Wait for transmit flag */
	while ( !( UCSR0A & (1<<TXC0)) )
	;
	UCSR0A |= 1 << TXC0;
}

void USART_PRINTF(const char *str)
{
	int x =0;
	while (str[x]){
		USART_TX(str[x]);
		x++;
	}
}

void USART_PRINTN(uint8_t ch){
	char str[4];
	
	str[3] = '\0';
	int i;
	for(i = 0; i < 3; i++){
		switch (i){
			case 0 :
			{
				str[2-i] = (ch % 10) + 48;
			}
			break;
			case 1 :
			{
				str[2-i] = ((ch / 10) % 10 )+ 48;
			}
			break;
			case 2 :
			{
				str[2-i] = ((ch/100) % 10) + 48;
			}
			break;
		}
	}
	
	USART_PRINTF(str);
}

void USART_SET_BAUD(int BAUD_FN){
	UBRR0 = (F_CPU/16/BAUD_FN)-1;
}