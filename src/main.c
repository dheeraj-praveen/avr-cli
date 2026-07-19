#include <avr/io.h>

#include <util/delay.h>

void USART_Init(void){

    UBRR0H = 0;

    UBRR0L = 103;

    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

}

void USART_Transmit(char data){

    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;

}

void USART_SendString(const char *p){

    while (*p){

        USART_Transmit(*p);

        p++;

    }

}

char USART_Receive(void){

    while (!(UCSR0A & (1 << RXC0)));

    return UDR0;

}

void Com_Prompt(void){

    USART_SendString("\n");

    USART_SendString(">");

}

int main(void){

    USART_Init();

    char buffer[32];

    uint8_t index = 0;

    Com_Prompt();

    while(1){

        char c = USART_Receive();

        if (c != '\r' && c != '\r\n'){

            buffer[index] = c;

            index += 1;

        }

        else{

            buffer[index] = '\0';

            USART_SendString("\r\n");

            USART_SendString(buffer);    
            
            USART_SendString("\r\n");

            index = 0;

            Com_Prompt();

        }


    }

    

    return 0;
}