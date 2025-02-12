#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"

// PWM PARAMETERS
#define MAX_WRAP_VALUE 20000       // Maximum counter value for PWM wrap
#define CLOCK_DIVIDER 125.0f       // Clock divider for PWM frequency

const uint8_t PWM_PIN = 22;        // GPIO pin for PWM output

// Function prototypes
void initialize_pwm(void);
void set_pwm_level(uint16_t level);
void rotate_servo_0_to_180(void);
void rotate_servo_180_to_0(void);
static void button_irq_handler(uint gpio, uint32_t events);

int main() {
    stdio_init_all();              // Initialize standard I/O for debugging
    initialize_pwm();              // Set up PWM configuration

    // Initial servo rotations to predefined angles
    set_pwm_level(2400);           // Rotate servo to 180 degrees
    sleep_ms(5000);
    set_pwm_level(1470);           // Rotate servo to 90 degrees
    sleep_ms(5000);
    set_pwm_level(500);            // Rotate servo to 0 degrees
    sleep_ms(5000);

    // Continuous loop for smooth servo rotation
    while (true) {
        printf("Rotating from 0 to 180 degrees...\n");
        rotate_servo_0_to_180();
        printf("Rotating from 180 to 0 degrees...\n");
        rotate_servo_180_to_0();
    }
}

/**
 * Function: initialize_pwm
 * Configures the PWM module with a 50Hz frequency using the specified parameters.
 */
void initialize_pwm(void) {
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);                  // Enable PWM on the GPIO pin
    uint slice = pwm_gpio_to_slice_num(PWM_PIN);                // Get the PWM slice for the GPIO pin
    pwm_set_wrap(slice, MAX_WRAP_VALUE);                        // Set the wrap value for the PWM counter
    pwm_set_clkdiv(slice, CLOCK_DIVIDER);                       // Set the clock divider for 50Hz frequency
    pwm_set_enabled(slice, true);                               // Enable the PWM slice
}

/**
 * Function: set_pwm_level
 * Sets the duty cycle level for the PWM signal.
 * @param level: The desired duty cycle value (500 to 2400).
 */
void set_pwm_level(uint16_t level) {
    uint slice = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_set_gpio_level(PWM_PIN, level);                         // Set the PWM duty cycle level
}

/**
 * Function: rotate_servo_0_to_180
 * Smoothly rotates the servo motor from 0 to 180 degrees by incrementing the PWM duty cycle.
 */
void rotate_servo_0_to_180(void) {
    for (uint16_t step = 500; step <= 2400; step += 5) {        // Increment duty cycle from 500 to 2400
        set_pwm_level(step);
        sleep_ms(10);                                           // Small delay for smooth motion
    }
}

/**
 * Function: rotate_servo_180_to_0
 * Smoothly rotates the servo motor from 180 to 0 degrees by decrementing the PWM duty cycle.
 */
void rotate_servo_180_to_0(void) {
    for (uint16_t step = 2400; step >= 500; step -= 5) {        // Decrement duty cycle from 2400 to 500
        set_pwm_level(step);
        sleep_ms(5);                                            // Small delay for smooth motion
    }
}
