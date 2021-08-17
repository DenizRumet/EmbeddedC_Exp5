/*
 */
#include <avr/io.h>
#include "LCDmodule.h"
#include <util/delay.h>
int main(void)
{
    DDRC |= 0xFC;
    DIDR0 |= 0x03;
    ADMUX = 0x01;
    ADMUX |= ((1<<ADLAR));
    ADCSRA |= 0x06;
    ADCSRA &= 0xDF;
    ADCSRA |= ((1<<ADEN));
    DDRB |=0xFF;

    int FLAG0=1;
    int FLAG1=1;
    unsigned char atten=1;

    //char  LCDtext[16];

    //unsigned short int result;


    //LCD_Init();
    //LCD_Clear();

    while(1){

    if (( PIND & _BV(PIND0) ) != 0x00){
            FLAG0=0;
        }
        if (( PIND & _BV(PIND1) ) != 0x00){
            FLAG1=0;
        }

         if((( PIND & _BV(PIND0) ) == 0x00) && FLAG0 == 0){
                if(atten>1){
        atten--;     }
        FLAG0=1;
         }

         if((( PIND & _BV(PIND1) ) == 0x00) && FLAG1 == 0){
                if(atten<6){
        atten++;     }
        FLAG1=1;
         }

        ADCSRA|=((1<<ADSC));


        //PORTB =ADCH;
        PORTB =ADCH>>(atten-1);



    }



    return 0;
}
