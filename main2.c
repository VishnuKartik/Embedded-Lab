#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
 {
    SYSCTL_RCGC2_R |=   0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x1F;
    GPIO_PORTF_DEN_R  = 0x1E;
    GPIO_PORTF_DIR_R  = 0x0E;
    GPIO_PORTF_PUR_R  = 0x10;

    GPIO_PORTF_DATA_R = 0x0;
    long int x,counter=0;
    long int delay = 675000;


    GPIO_PORTF_DIR_R &= ~(0x11);
    GPIO_PORTF_DEN_R |= 0x11;



    while (1) {
        if ((GPIO_PORTF_DATA_R & 0x01) == 0) {
            if ((GPIO_PORTF_DATA_R & 0x01) == 0) {
                counter++;



                if (counter == 1) {
                    GPIO_PORTF_DATA_R = 0x02;
                    x=0;
                                                  while ( x < delay)
                                                  x ++ ;


                } else if (counter == 3) {
                    GPIO_PORTF_DATA_R = 0x08;
                    x=0;
                                                  while ( x < delay)
                                                  x ++ ;

                } else if (counter == 2) {
                    GPIO_PORTF_DATA_R = 0x04;
                    x=0;
                                                                      while ( x < delay)
                                                                      x ++ ;

                }
                else if (counter == 4) {
                                    GPIO_PORTF_DATA_R = 0x0A;
                                    x=0;
                                                                  while ( x < delay)
                                                                  x ++ ;

                                }
                else if (counter == 5) {
                                    GPIO_PORTF_DATA_R = 0x0C;
                                    x=0;
                                                                  while ( x < delay)
                                                                  x ++ ;

                                }
                else if (counter == 6) {
                                                    GPIO_PORTF_DATA_R = 0x06;
                                                    x=0;
                                                                                  while ( x < delay)
                                                                                  x ++ ;

                                                }

                else if (counter == 7) {
                                    GPIO_PORTF_DATA_R = 0x0E;
                                    x=0;
                                                                  while ( x < delay)
                                                                  x ++ ;

                                }
            }}
            else {
                                                                                                                                GPIO_PORTF_DATA_R = 0x00; // Turn off both LEDs
                                                                                                                                x=0;
                                                                                                                                                   while ( x < delay)               // Delay
                                                                                                                                             x ++ ;}
        if (counter > 7) {
                           counter = 0;
                       }

 }
 }
