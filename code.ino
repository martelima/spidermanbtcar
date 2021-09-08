/* 
  Descrição: Este é um código que possibilita o controle de um 
             carro bluetooth montado em arduino com uma shield 
             ponte H, através do protocolo serial
*/
/*
  É necessario incluir a biblioteca 'AFMotor' pois simplifica o 
  uso da Shield ponte H
*/

//#include <AFMotor.h>

//selecionamos os canais 3 e 4 para motor direito e esquerdo
//respectivamente

//AF_DCMotor motor_dir(3);
//AF_DCMotor motor_esq(4);

/*
  Aqui definimos a velocidade máxima dos motores porem isso 
  depende tambem da fonte de energia que esteja utilizando 
  para alimentar os motores, logo se o valor atribuido for 
  equivalente a 255, por PWM os motores receberão tensão 
  total da fonte que estiver utilizando.
*/
#include<Servo.h>
#include <AFMotor.h>

#define Pino_Buzzer 10

#define Meio 90
#define direita 65
#define esquerda 115
Servo meu_servo;
int posicao_servo = 0;


AF_DCMotor motor(1);

#define Fator_correcao_Tra 1
#define Pin_vel_motor_traseiro 10

int v = 0;
#define VmaxT 127

int vel_motor_traseiro = 127;

#define buzina 10
//variável que atribuimos a leitura Serial do módulo bluetooth
char state;

void setup() {
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  meu_servo.attach(9);
  pinMode(Pino_Buzzer, OUTPUT);

}
void loop() {
  // Atribui os valores da leitura serial na variável "state"
  if (Serial.available() > 0) {
    state  = Serial.read();
    Serial.write(state);
  }
  /*
    Aqui controlamos a velocidade que o carro bluetooth irá
    se locomover, portanto multiplicamos a velocidade maxima
    por valores decimais para reduzir proporcionamente as 
    velocidades dos motores direito e esquerdo. 
    
    Quando a variavel "state" assumir o caractere 7,através do meio 
    serial, as velocidades são correspondentes à 70% da velocidade 
    máxima dos motores
  */
  if (state == '0') {
    vel_motor_traseiro = 0;
  }
  else if (state == '1') {
    vel_motor_traseiro = VmaxT * 0.1;
  }
  else if (state == '2') {
    vel_motor_traseiro = VmaxT * 0.2;
  }
  else if (state == '3') {
    vel_motor_traseiro = VmaxT * 0.3;
  }
  else if (state == '4') {
    vel_motor_traseiro = VmaxT * 0.39; 
  }
  else if (state == '5') {
    vel_motor_traseiro = VmaxT * 0.5;
  }
  else if (state == '6') {
    vel_motor_traseiro = VmaxT * 0.6;
  }
  else if (state == '7') {
    vel_motor_traseiro = VmaxT * 0.7;
  }
  else if (state == '8') {
    vel_motor_traseiro = VmaxT * 0.78;
  }
  else if (state == '9') {
    vel_motor_traseiro = VmaxT * 0.9;
  }
  else if (state == 'q') {
    vel_motor_traseiro = VmaxT;
  }
  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    motor.setSpeed(vel_motor_traseiro ); //Define a velocidade maxima
    motor.run(FORWARD);

    meu_servo.write(Meio);
  }
  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    motor.setSpeed(vel_motor_traseiro ); //Define a velocidade maxima
    motor.run(FORWARD);
    meu_servo.write(esquerda);

  }
  else if (state == 'I') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
   motor.setSpeed(vel_motor_traseiro ); //Define a velocidade maxima
    motor.run(FORWARD);
    meu_servo.write(direita);
  }
  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
   motor.setSpeed(vel_motor_traseiro ); //Define velocidade baixa
   motor.run(BACKWARD);
   meu_servo.write(Meio);
  }
  else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
   motor.setSpeed(vel_motor_traseiro ); //Define velocidade baixa
   motor.run(BACKWARD);
  meu_servo.write(esquerda);
  }
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
   motor.setSpeed(vel_motor_traseiro ); //Define velocidade baixa
   motor.run(BACKWARD);
   meu_servo.write(direita);
  }
  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    motor.setSpeed(0);
    motor.run(RELEASE);
    meu_servo.write(esquerda);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    motor.setSpeed(0);
    motor.run(RELEASE);
    meu_servo.write(direita);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    motor.setSpeed(0);
    motor.run(RELEASE);
    meu_servo.write(Meio);
  }
  else if (state == 'W') {   // Se o estado recebido for igual a 'W', Farol dianteiro acende.
  }
  else if (state == 'w') {   // Se o estado recebido for igual a 'w', Farol dianteiro apaga.
  }
  else if (state == 'U') {   // Se o estado recebido for igual a 'U', Farol traseiro acende.
  }
  else if (state == 'u') {   // Se o estado recebido for igual a 'u', Farol traseiro apaga.
  }
  else if (state == 'V') {   // Se o estado recebido for igual a 'V', liga buzina.
      tone(Pino_Buzzer, 1661,500);   
  }
  else if (state == 'v') {   // Se o estado recebido for igual a 'v', desliga buzina.
      noTone(Pino_Buzzer);
  }
  else if (state == 'X') {   // Se o estado recebido for igual a 'X', Pisca alerta acende.
  }
  else if (state == 'x') {   // Se o estado recebido for igual a 'x', Pisca alerta apaga.
    
  }
}
