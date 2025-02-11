#include <stdio.h>         
#include "pico/stdlib.h"   
#include "hardware/pwm.h"  

#define PINO_SERVO 22 //pino onde o servo motor está conectado GPIO 22
#define PINO_LED   12 // Pino do LED RGB GPIO 12 Azul

// Definições do PWM para 50Hz período de 20m
const uint16_t PERIODO_PWM = 20000;  // Contador máximo do PWM para 20ms
const float DIVISOR_PWM = 125.0;      // Divisor de clock para gerar PWM de 50Hz

//Posições do servo motor em microssegundos
const uint16_t PULSO_180_GRAUS = 2400; // Pulso de 2.400µs → 180°
const uint16_t PULSO_90_GRAUS  = 1470; // Pulso de 1.470µs → 90°
const uint16_t PULSO_0_GRAUS   = 500;  // Pulso de 500µs → 0°

// Configurações da movimentação suave
const uint16_t INCREMENTO_PASSO = 5;   // Incremento/decremento do PWM (5µs por passo)
const uint16_t ATRASO_PASSO = 10;      // Tempo entre passos (10ms)

uint16_t posicao_servo = PULSO_0_GRAUS; // Começa em 0°
bool aumentando = true; // Direção inicial (0° → 180°)

// Configura PWM no Servo e no LED
void configurar_pwm() {
    // Configuração do Servo na GPIO 22
    gpio_set_function(PINO_SERVO, GPIO_FUNC_PWM);
    uint slice_servo = pwm_gpio_to_slice_num(PINO_SERVO);
    pwm_set_clkdiv(slice_servo, DIVISOR_PWM);
    pwm_set_wrap(slice_servo, PERIODO_PWM);
    pwm_set_gpio_level(PINO_SERVO, posicao_servo);
    pwm_set_enabled(slice_servo, true);

    //configuração do LED na GPIO 12
    gpio_set_function(PINO_LED, GPIO_FUNC_PWM);
    uint slice_led = pwm_gpio_to_slice_num(PINO_LED);
    pwm_set_clkdiv(slice_led, DIVISOR_PWM);
    pwm_set_wrap(slice_led, PERIODO_PWM);
    pwm_set_gpio_level(PINO_LED, 0);  //Começar apagado
    pwm_set_enabled(slice_led, true);
}

//ajusta a posição do servo e a intensidade do LED
void ajustar_servo_e_led(uint16_t largura_pulso) {
    pwm_set_gpio_level(PINO_SERVO, largura_pulso);

    // Ajusta o brilho do LED proporcionalmente à posição do servo
    uint16_t brilho_led = (largura_pulso - PULSO_0_GRAUS) * 10;
    pwm_set_gpio_level(PINO_LED, brilho_led);
}

// Movimentação contínua e suave entre 0° e 180°
void movimentar_servo_suavemente() {
    while (true) {
        ajustar_servo_e_led(posicao_servo);
        sleep_ms(ATRASO_PASSO); // Pequeno atraso para suavizar a movimentação

        //atualiza a posição do servo motor continuamente
        if (aumentando) {
            posicao_servo += INCREMENTO_PASSO;
            if (posicao_servo >= PULSO_180_GRAUS) {
                aumentando = false; // Alcançou 180°, começa a descer
            }
        } else {
            posicao_servo -= INCREMENTO_PASSO;
            if (posicao_servo <= PULSO_0_GRAUS) {
                aumentando = true; //alcançou 0°, começa a subir
            }
        }
    }
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa comunicação serial (opcional)
    
    configurar_pwm(); // Configura PWM no servo e no LED

    // Posições fixas iniciais
    ajustar_servo_e_led(PULSO_180_GRAUS);
    sleep_ms(5000); // Espera 5s em 180°

    ajustar_servo_e_led(PULSO_90_GRAUS);
    sleep_ms(5000); //espera 5s em 90°

    ajustar_servo_e_led(PULSO_0_GRAUS);
    sleep_ms(5000); //Espera 5s em 0°

    // Inicia movimentação contínua e suave entre 0° e 180°
    movimentar_servo_suavemente();

    return 0;
}
