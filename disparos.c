// bibliotecs
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e do button
#define LED_BLUE  12
#define LED_RED   13
#define LED_GREEN 11
#define BUTTON    5

// Variáveis globais para controlar o estado do temporizador e a etapa do desligamento
volatile bool timer_running = false;
volatile int step = 0;

// Declaracao das funções de callback utilizando o int64_t turn_off_callback
void button_callback(uint gpio, uint32_t events);

// Função para desligar todos os LEDs e resetar o sistema
void turn_off_leds() {
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);

    timer_running = false;
    step = 0; // Reseta para próxima ativação
}

// Callback que chama pelo temporizador para desligar os LEDs na sequencia
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    // Array com a ordem de desligamento dos LEDs
    int leds[] = {LED_RED, LED_BLUE, LED_GREEN}; // (led 0, led 1, led 2)

    // Para verificar se ainda tem LEDs para desligar, inicia no step 0, com todos leds acesos
    if (step < 3) {
        gpio_put(leds[step], 0); // Desliga o LED correspondente
        step++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Agenda o próximo desligamento depois de 3sec.
    } else {
        turn_off_leds(); // confirma quetodos os LEDs estão desligados e reseta o sistema
    }

    return 0;
}

// Callback chama quando o botão for apertado
void button_callback(uint gpio, uint32_t events) {
    // Verifica se o temporizador não está em execução
    if (!timer_running) {
        timer_running = true;
        step = 0; // garante que a sequencia de desligamento funcione no leds[steps]
        
        // Liga todos os LEDs
        gpio_put(LED_RED, 1);
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_GREEN, 1);

        // Inicia o temporizador para desligar os LEDs sequencialmente
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}

int main() {
    // Inicializa a comunicação padrão
    stdio_init_all();

    // Inicializa os pinos dos LEDs e do botão
    gpio_init(LED_RED);
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);

    // Define os pinos dos LEDs como saída
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // configurando o pino do botão como entrada com pull-up para implementar o debounce
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    
    // Configura a interrupção para detectar o pressionamento do botão
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    // Loop principal (mantém o programa rodando)
    while (1) {
        tight_loop_contents(); //
    }
}
/* o uso de tight_loop_contents() é uma técnica comum para garantir que o 
processador não entre em estados de espera desnecessários, como aqueles 
causados por um delay ou um sleep. Isso permite que o processador continue 
pronto para executar interrupções, como a detecção do pressionamento do botão*/
