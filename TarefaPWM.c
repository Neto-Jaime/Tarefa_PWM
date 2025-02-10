#include <stdio.h>         // Biblioteca padrão da linguagem C
#include "pico/stdlib.h"   // Biblioteca do SDK do Raspberry Pi Pico
#include "hardware/pwm.h"  // Biblioteca para controle de PWM

#define SERVO_PIN 22 // Pino onde o servo motor está conectado (GPIO 22)
#define LED_PIN 12   // Pino do LED RGB (GPIO 12)

// Definições do PWM para 50Hz (período de 20ms)
const uint16_t WRAP_PERIOD = 20000;  // Contador máximo do PWM para 20ms
const float PWM_DIVISER = 125.0;      // Divisor de clock para gerar PWM de 50Hz

// Posições do servo motor
const uint16_t SERVO_180_DEGREES = 2400; // Pulso de 2.400µs → 180°
const uint16_t SERVO_90_DEGREES  = 1470; // Pulso de 1.470µs → 90°
const uint16_t SERVO_0_DEGREES   = 500;  // Pulso de 500µs → 0°

// Suavidade do movimento
const uint16_t STEP_SIZE = 5;  // Incremento/decremento do PWM (5µs por passo)
const uint16_t STEP_DELAY = 10; // Tempo entre passos (10ms)

uint16_t servo_level = SERVO_0_DEGREES; // Começa em 0°
bool moving_up = true; // Direção inicial (0° → 180°)

// Configura PWM no Servo e no LED
void pwm_setup() {
    // Configuração do Servo (GPIO 22)
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(slice_servo, PWM_DIVISER);
    pwm_set_wrap(slice_servo, WRAP_PERIOD);
    pwm_set_gpio_level(SERVO_PIN, servo_level);
    pwm_set_enabled(slice_servo, true);

    // Configuração do LED (GPIO 12)
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_led = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_clkdiv(slice_led, PWM_DIVISER);
    pwm_set_wrap(slice_led, WRAP_PERIOD);
    pwm_set_gpio_level(LED_PIN, 0);  // Começa apagado
    pwm_set_enabled(slice_led, true);
}

// Ajusta a posição do servo e a intensidade do LED
void set_servo_and_led(uint16_t pulse_width) {
    pwm_set_gpio_level(SERVO_PIN, pulse_width);

    // Ajusta o LED proporcionalmente à posição do servo
    uint16_t led_brightness = (pulse_width - SERVO_0_DEGREES) * 10;
    pwm_set_gpio_level(LED_PIN, led_brightness);
}

// Movimentação contínua e suave entre 0° e 180°
void move_servo_smoothly() {
    while (true) {
        set_servo_and_led(servo_level);
        sleep_ms(STEP_DELAY); // Pequeno atraso para suavizar a movimentação

        // Atualiza a posição do servo motor continuamente
        if (moving_up) {
            servo_level += STEP_SIZE;
            if (servo_level >= SERVO_180_DEGREES) {
                moving_up = false; // Alcançou 180°, começa a descer
            }
        } else {
            servo_level -= STEP_SIZE;
            if (servo_level <= SERVO_0_DEGREES) {
                moving_up = true; // Alcançou 0°, começa a subir
            }
        }
    }
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa comunicação serial (opcional)
    
    pwm_setup(); // Configura PWM no servo e no LED

    // Posições fixas iniciais
    set_servo_and_led(SERVO_180_DEGREES);
    sleep_ms(5000); // Espera 5s em 180°

    set_servo_and_led(SERVO_90_DEGREES);
    sleep_ms(5000); // Espera 5s em 90°

    set_servo_and_led(SERVO_0_DEGREES);
    sleep_ms(5000); // Espera 5s em 0°

    // Inicia movimentação contínua e suave entre 0° e 180°
    move_servo_smoothly();

    return 0;
}
