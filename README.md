## Programa de Controle de LEDs com temporizador de um disparo (One Shot)

# Descrição

Este programa foi desenvolvido para um microcontrolador Raspberry Pi Pico e tem como objetivo controlar três LEDs vermelho, azul e verde, de forma sequencial. Ao pressionar o botão conectado ao GPIO 5 da BitDogLab, todos os LEDs são acesos simultaneamente, e um temporizador é ativado para desligá-los de maneira sequencial, com um intervalo de 3 segundos entre cada desligamento.

# Funcionalidade

1. Pressionamento do Botão
Quando o botão é pressionado, o sistema verifica se o temporizador está em execução. Se não estiver, ele inicia a sequência de ligar todos os LEDs e então começa a contagem do temporizador.
2. Sequenciamento dos LEDs
Quando o temporizador é iniciado, todos os LEDs acendem e, a cada 3 segundos, um LED é apagado na seguinte ordem: LED vermelho, LED azul e, por último, o LED verde.
O desligamento dos LEDs é realizado por meio de um temporizador que é reconfigurado a cada etapa, garantindo a sequência correta.
3. Reset do Sistema
Após o desligamento de todos os LEDs, o sistema é resetado, e a sequência poderá ser repetida caso o botão seja pressionado novamente.
4. Interrupção de Botão
A interrupção é configurada no pino do botão para detectar o pressionamento, garantindo que o sistema reaja rapidamente ao evento sem necessidade de polling contínuo.
5. Uso de tight_loop_contents()
A função tight_loop_contents() é chamada no loop principal para garantir que o processador continue executando sem entrar em estados de espera desnecessários. Isso permite que o sistema continue pronto para detectar a interrupção do botão e outras interrupções, mantendo a performance otimizada.

# Estrutura do Código

Definições dos Pinos: O código define os pinos para os LEDs (vermelho, azul, verde) e o botão.
- Variáveis Globais: As variáveis globais controlam o estado do temporizador (timer_running) e o passo atual na sequência de desligamento dos LEDs (step).
- Funções de Callback:
  
`button_callback()`: Esta função é chamada quando o botão é pressionado. Ela liga os LEDs e inicia o temporizador para desligá-los sequencialmente.

`turn_off_callback()`: Esta função é chamada pelo temporizador para desligar os LEDs de forma sequencial. Após o desligamento de todos os LEDs, ela reseta o sistema.

`turn_off_leds()`: Desliga todos os LEDs e reseta o estado global.

# Diagrama de Sequência

- Pressionamento do botão:
  
1 - Todos os LEDs são acesos.

2 - Um temporizador é iniciado.

3 - Desligamento sequencial dos LEDs:

4 - LED vermelho desliga após 3 segundos.

5 - LED azul desliga após mais 3 segundos.

6 - LED verde desliga após mais 3 segundos.

7 - Reset do sistema: Todos os LEDs estão apagados e o sistema é resetado para aguardar uma nova interação com o botão.
  
# Requisitos de Hardware

* Raspberry Pi Pico: Microcontrolador utilizado para controlar os LEDs e o botão.
  
* 3 LEDs (vermelho, azul, verde): Para visualização do processo de desligamento sequencial.

* 1 push button: Para iniciar a sequência de desligamento dos LEDs.
  
# Compilação e Execução

1- Certifique-se de que o Raspberry Pi Pico da BitDogLab está corretamente configurado para receber o programa.

2- Compile o código com o SDK do Raspberry Pi Pico, caso não seja iniciado automaticamente, importe um novo projeto na extensão do Raspberry Pi Pico presente no Visual Studio Code.

3- Carregue o código para a BitDogLab.

Ao pressionar o botão, os LEDs devem acender e desligar sequencialmente conforme o esperado.

# Observações
A função `tight_loop_contents()` é crucial para a operação eficiente do programa, garantindo que o processador esteja sempre pronto para reagir a interrupções, como o pressionamento do botão, sem desperdiçar ciclos de processamento.

# Autor

Desenvolvido por Arilson S. Oliveira, como prática pessoal e requisito de atividade avaliativa da Residência em Sistemas Embarcados Embarcatech, com foco em aprendizado da Raspberry Pi Pico W e placa BitDogLab.
