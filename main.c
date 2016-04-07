#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

GPIO_InitTypeDef GPIO_InitStructure;

typedef enum {
	OUTPUT = 0, INPUT = 1
} direction;

typedef enum {
	HIGH = 0, LOW = 1
} status;

void pinMode(uint32_t Pin, direction d) {
	/*
	 * TODO: implement direction.
	 */
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void digitalWrite(uint32_t Pin, status s) {
	if (s == HIGH) {
		GPIOA->BSRR = Pin;
	} else {
		GPIOA->BRR = Pin;
	}
}

void delay(uint32_t nCount) {
	while (nCount != 0) {
		nCount--;
	}
}

int in1Pin = GPIO_Pin_0;
int in2Pin = GPIO_Pin_1;
int in3Pin = GPIO_Pin_2;
int in4Pin = GPIO_Pin_3;

int led = GPIO_Pin_4;

uint32_t stepDelay = 10000L;
uint32_t stopDelay = 1000000L;

void setup(void) {
	pinMode(led, OUTPUT);

	pinMode(in1Pin, OUTPUT);
	pinMode(in2Pin, OUTPUT);
	pinMode(in3Pin, OUTPUT);
	pinMode(in4Pin, OUTPUT);
}

void step1() {
	digitalWrite(in1Pin, LOW);
	digitalWrite(in2Pin, HIGH);
	digitalWrite(in3Pin, HIGH);
	digitalWrite(in4Pin, LOW);
	delay(stepDelay);

}
void step2() {
	digitalWrite(in1Pin, LOW);
	digitalWrite(in2Pin, HIGH);
	digitalWrite(in3Pin, LOW);
	digitalWrite(in4Pin, HIGH);
	delay(stepDelay);
}
void step3() {
	digitalWrite(in1Pin, HIGH);
	digitalWrite(in2Pin, LOW);
	digitalWrite(in3Pin, LOW);
	digitalWrite(in4Pin, HIGH);
	delay(stepDelay);
}
void step4() {
	digitalWrite(in1Pin, HIGH);
	digitalWrite(in2Pin, LOW);
	digitalWrite(in3Pin, HIGH);
	digitalWrite(in4Pin, LOW);
	delay(stepDelay);
}
void stopMotor() {
	digitalWrite(in1Pin, LOW);
	digitalWrite(in2Pin, LOW);
	digitalWrite(in3Pin, LOW);
	digitalWrite(in4Pin, LOW);
}

void loop(void) {
	for (int i=0; i<=50; i++){
	    step1();
	    step2();
	    step3();
	    step4();
	  }
	  stopMotor();

	  digitalWrite(led, HIGH);
	  delay(stopDelay);
	  digitalWrite(led, LOW);

	  for (int i=0; i<=50; i++){
	    step3();
	    step2();
	    step1();
	    step4();
	  }
	  stopMotor();

	  digitalWrite(led, HIGH);
	  delay(stopDelay);
	  digitalWrite(led, LOW);
}

int main(void) {
	setup();

	while (1) {
		loop();
	}
}
