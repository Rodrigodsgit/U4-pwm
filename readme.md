<table align="center">
  <tr>
    <td><img src="image.png" width="100"></td>
    <td align="center">
      <b>Embarca Tech - CEPEDI</b><br>
      Capacitação Inicial em Sistemas Embarcados<br>
      U1 - Microcontroladores <br>
      <b>Discente - Rodrigo Damasceno Sampaio (Grupo 9)</b>
    </td>
    <td><img src="image2.png" width="100"></td>
  </tr>
</table>

## 🌟 Projeto: PWM

Este projeto demonstra o uso do módulo PWM (Pulse Width Modulation) presente no microcontrolador RP2040 do Raspberry Pi Pico W para controlar um servomotor simulado no ambiente Wokwi . Além disso, o projeto explora o comportamento de um LED RGB conectado à GPIO 12 durante a operação do PWM.

## PWM (Pulse Width Modulation)
O PWM é uma técnica amplamente utilizada para controlar a potência entregue a dispositivos eletrônicos, como LEDs, motores e servomotores. Ele funciona alternando rapidamente entre dois estados (alto e baixo) e ajustando a proporção de tempo em que o sinal permanece em nível alto (Duty Cycle).

### Parâmetros Importantes do PWM

- Frequência : Define quantas vezes o sinal se repete por segundo. Para servomotores, a frequência típica é 50Hz (período de 20ms).

- Duty Cycle : Representa a fração de tempo em que o sinal está em nível alto. É expresso em porcentagem ou em unidades de tempo (µs).

### Cálculo da Frequência e Duty Cycle
Para gerar um sinal PWM com frequência de 50Hz no RP2040:

1. O período total do sinal é calculado como:

   $$ T = \frac{1}{f} = \frac{1}{50} = 20 \text{ ms} $$

2. O valor máximo do contador (**WRAP**) é definido como:

   $$ \text{WRAP} = \frac{\text{Clock do Sistema}}{\text{Divisor} \times f} $$

   O clock do sistema do RP2040 é **125 MHz**, e o divisor foi escolhido como **125.0**, devido as solicitações para utilizar os correspondentes ciclos ativos e duty cycle.

   $$ \text{WRAP} = \frac{125 \text{ MHz}}{125 \times 50} = 20000 $$

Para controlar o ângulo do servomotor:

- 0° : Duty Cycle de 500 µs .
- 90° : Duty Cycle de 1470 µs .
- 180° : Duty Cycle de 2400 µs .

Esses valores são convertidos para níveis PWM usando a fórmula:

$$
\text{Nível PWM} = \frac{\text{Duty Cycle} \times \text{WRAP}}{\text{Período Total}}
$$

## Estrutura do Código

### 📌 Funções Principais

#### 🔹 `initialize_pwm()`
> Configura o módulo PWM com frequência de **50Hz** e **WRAP** de **20000**.

#### 🔹 `set_pwm_level(uint16_t level)`
> Define o nível de **duty cycle** para o PWM.

#### 🔹 `rotate_servo_0_to_180()`
> Move o braço do **servomotor** suavemente de **0° a 180°**.

#### 🔹 `rotate_servo_180_to_0()`
> Move o braço do **servomotor** suavemente de **180° a 0°**.

#### 🔹 `button_irq_handler()`
> Trata as **interrupções** dos botões **A e B**.

---

### Movimentação Suave do Servomotor
O braço do servomotor foi programado para mover-se suavemente entre 0° e 180°, incrementando o duty cycle em passos de 5 µs com um atraso de 10 ms entre cada passo. Isso resultou em um movimento fluido, igual visto no vidéo de demonstração.

### Comportamento do LED RGB
Durante a operação do PWM, o LED RGB conectado à GPIO 12 exibiu um comportamento interessante:

Quando o duty cycle era ajustado para valores baixos (0°), o LED emitia uma luz tênue.
Quando o duty cycle aumentava (180°), a intensidade da luz aumentava proporcionalmente.

--- 

## 🚀 Como Rodar o Projeto

### 📌 **1️⃣ Clonar o Repositório**
```bash
git clone https://github.com/Rodrigodsgit/U4-pwm.git
cd semaforo
```

### 📌 **2️⃣ Configurar o Ambiente**
Instale a extensão da Raspberry Pi Pico Project no VsCode  

### 📌 3️⃣ Compilar o Código
Através da extensão, use o acesso rapido e clique em "Compile Project"

### 📌 4️⃣ Rode o Código
Através da extensão, use o acesso rapido e clique em "Run Project (USB)"

## 🚀 Video Demonstração


[🎥 Assista ao vídeo](hhttps://youtu.be/IOD3ry44Uro)
