#include <stdint.h>

// Base addresses
#define SYSCTL_RCGC2_R       (*((volatile uint32_t *)0x400FE108))
#define GPIO_PORTF_DIR_R     (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_DEN_R     (*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTF_DATA_R    (*((volatile uint32_t *)0x400253FC))
#define GPIO_PORTF_PUR_R     (*((volatile uint32_t *)0x40025510))
#define GPIO_PORTF_LOCK_R    (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R      (*((volatile uint32_t *)0x40025524))

// Unlock key for GPIOLOCK
#define GPIO_LOCK_KEY        0x4C4F434B

// Macro for setting/clearing GPIO bits without affecting others
#define GPIO_PORTF_WRITE_BIT(bit_mask, value) \
    do { \
        if (value) \
            GPIO_PORTF_DATA_R |= (bit_mask); \
        else \
            GPIO_PORTF_DATA_R &= ~(bit_mask); \
    } while (0)

int main(void)
{
    volatile unsigned long delay;
    volatile long int x;
    long int wait = 675000;

    // Enable clock to Port F
    SYSCTL_RCGC2_R |= 0x00000020;

    // Allow time for clock to stabilize
    delay = SYSCTL_RCGC2_R;

    // Unlock PF0 (it is locked by default)
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R = 0x1F;           // Allow changes to PF4-0

    // Enable digital functionality
    GPIO_PORTF_DEN_R = 0x1F;

    // Set PF1, PF2, PF3 as output; PF0, PF4 as input
    GPIO_PORTF_DIR_R = 0x0E;

    // Enable pull-up resistors on PF0 and PF4
    GPIO_PORTF_PUR_R = 0x11;

    while (1)
    {
        // Both SW1 (PF4) and SW2 (PF0) pressed
        if (((GPIO_PORTF_DATA_R & 0x01) == 0) && ((GPIO_PORTF_DATA_R & 0x10) == 0))
        {
            GPIO_PORTF_WRITE_BIT(0x0E, 0); // Turn off all LEDs
            GPIO_PORTF_WRITE_BIT(0x08, 1); // Green LED on (PF3)
        }

        // Only SW1 (PF4) pressed
        else if ((GPIO_PORTF_DATA_R & 0x10) == 0)
        {
            GPIO_PORTF_WRITE_BIT(0x0E, 0);
            GPIO_PORTF_WRITE_BIT(0x02, 1); // Red LED on (PF1)
        }

        // Only SW2 (PF0) pressed
        else if ((GPIO_PORTF_DATA_R & 0x01) == 0)
        {
            GPIO_PORTF_WRITE_BIT(0x0E, 0);
            GPIO_PORTF_WRITE_BIT(0x04, 1); // Blue LED on (PF2)
        }

        // No buttons pressed
        else
        {
            GPIO_PORTF_WRITE_BIT(0x0E, 0); // All LEDs off
        }

        // Delay
        x = 0;
        while (x < wait) x++;
    }

    return 0;
}
