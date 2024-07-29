/**********************************************************************************************/
/*                                                                                            */
/*                                                                                            */
/*        motor.cpp                                    Author  : Luiz Felipe                  */
/*                                                     Email   :                              */
/*                                                     address : DF, BRAZIL                   */
/*        Created: 2023/02/26          by Luiz F.                                             */
/*        Updated: 2023/03/31          by Luiz F.                                             */
/*                                                                       All rights reserved  */
/**********************************************************************************************/

#include "motor.h"
#include <Arduino.h>

Motor::Motor(int pin_R, int pin_L, int enable_pin_r, int enable_pin_l, int channelR, int channelL) {
    this->pin_R = pin_R;
    this->pin_L = pin_L;
    this->enable_pin_r = enable_pin_r;
    this->enable_pin_l = enable_pin_l;
    this->channelR = channelR;
    this->channelL = channelL;

    // Definir pinos de enable como saída
    // pinMode(enable_pin_r, OUTPUT);
    // pinMode(enable_pin_l, OUTPUT);

    // Configurar os canais de PWM
    ledcAttachChannel(pin_R, PWM_MOTOR_FREQUENCY, PWM_MOTOR_RESOLUTION, channelR);
    ledcAttachChannel(pin_L, PWM_MOTOR_FREQUENCY, PWM_MOTOR_RESOLUTION, channelL);

    // Associar os pinos aos canais PWM
    ledcAttach(pin_R, PWM_MOTOR_FREQUENCY, PWM_MOTOR_RESOLUTION);
    ledcAttach(pin_L, PWM_MOTOR_FREQUENCY, PWM_MOTOR_RESOLUTION);
}

void Motor::moveForward(int speed, int direction) {
    /*
        Este método inicia o motor e define a velocidade e direção.
        - A velocidade é dada em um valor hexadecimal de 8 bits para modificar o duty cycle do motor.
        - A direção 'forward' é dada por um número, 1 para direção R e -1 para direção L.
    */
    if (direction == 1){
        // digitalWrite(enable_pin_r, HIGH);
        // digitalWrite(enable_pin_l, HIGH);
        // Move o motor para a direção R
        ledcWrite(pin_R, LOW);
        ledcWrite(pin_L, speed);        
    }
    else if (direction == -1) {
        // digitalWrite(enable_pin_r, HIGH);
        // digitalWrite(enable_pin_l, HIGH);
        // Move o motor para a direção L
        ledcWrite(pin_R, speed);
        ledcWrite(pin_L, LOW);              
    }
}

void Motor::stop() {
    // Este método para ambas as direções definindo o duty cycle como zero
    ledcWrite(pin_R, 0x00);
    ledcWrite(pin_L, 0x00);
}
