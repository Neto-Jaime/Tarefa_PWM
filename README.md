# 🚀 Controle de Servo Motor e LED RGB no Raspberry Pi Pico W  

# Nome: Jaime Neto
# Matricula: TIC370100555
# Grupo: 0
# Link do repósitorio: https://github.com/Neto-Jaime/Tarefa_PWM

Este projeto controla um **servo motor** e um **LED RGB** simultaneamente usando **PWM** no Raspberry Pi Pico W.  
O **servo motor oscila suavemente entre 0° e 180°**, enquanto o **LED RGB ajusta seu brilho proporcionalmente** à posição do servo.  

## 📷 **Demonstração do Projeto**  
➡ O servo **gira de 0° a 180°** e **volta suavemente para 0°**.  
➡ O LED **aumenta o brilho** conforme o servo **gira para 180°**.  
➡ O LED **diminui o brilho** conforme o servo **retorna para 0°**.  

---

## 📌 **Especificações Técnicas**
- **Microcontrolador:** Raspberry Pi Pico W  
- **PWM:** Configurado para **50Hz (20ms)** para controle do servo  
- **Servo Motor:** Conectado à **GPIO 22**  
- **LED RGB:** Conectado à **GPIO 12**  
- **Movimento do Servo:** Incrementos de **5µs a cada 10ms** para suavidade  
- **Brilho do LED:** Ajustado dinamicamente baseado no ângulo do servo  

---

## 📁 **Estrutura do Projeto**
📂 TarefaPWM/ ├── 📄 main.c # Código principal do projeto ├── 📄 CMakeLists.txt # Configuração de build com o Pico SDK ├── 📄 README.md # Documentação do projeto ├── 📂 build/ # Diretório para os arquivos compilados

## 🛠 **Requisitos**
✅ **Raspberry Pi Pico W**  
✅ **Pico SDK instalado** ([Guia de Instalação](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf))  
✅ **CMake e Make instalados**  

## 🚀 **Passo a Passo para Compilar e Rodar**
### **1️⃣ Clonar o Repositório**
```sh
git clone https://github.com/seu-usuario/tarefa-pwm-servo-led.git
cd tarefa-pwm-servo-led

2️⃣ Criar o Diretório de Build

rm -rf build
mkdir build
cd build

3️⃣ Configurar o Projeto com CMake

cmake ..
4️⃣ Compilar o Código

make
5️⃣ Enviar o Arquivo .uf2 para o Raspberry Pi Pico
Conecte o Pico W ao PC segurando o botão BOOTSEL.
Copie o arquivo gerado para a unidade do Pico:
cp TarefaPWM.uf2 /media/$USER/RPI-RP2

6️⃣ Verificar a Execução
O servo deve começar a se mover suavemente entre 0° e 180°.
O LED RGB deve aumentar e diminuir o brilho conforme o servo se move.
🎯 Configuração dos Pinos
Componente	Pino no Pico W
Servo Motor	GPIO 22
LED RGB	GPIO 12
🔬 Observações no BitDogLab
Ao testar no BitDogLab, o comportamento do LED RGB foi observado:
✔ A intensidade do LED muda conforme o movimento do servo.
✔ O LED e o servo estão sincronizados via PWM.
✔ Não há pisca-pisca abrupto, o brilho muda suavemente.