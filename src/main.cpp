#include <Arduino.h>


#define PWM_IN_PIN 3
#define KILLSWITCH_PIN 2
#define GREEN_LED_PIN 4
#define RED_LED_PIN 5

volatile int pwm_value = 0;
volatile long prev_time = 0;
volatile long now = 0;
void rising();
void falling();

int counter = 0;

void setup() {
  // when pin D2 goes high, call the rising function
  pinMode(KILLSWITCH_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(KILLSWITCH_PIN, LOW);
  digitalWrite(GREEN_LED_PIN , LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(PWM_IN_PIN), rising, RISING);
  pwm_value = 0;
}

void loop() {

  if((pwm_value > 1500) && (pwm_value < 2500) && (micros() - prev_time < 50000)) {
    digitalWrite(KILLSWITCH_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN , HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    digitalWrite(KILLSWITCH_PIN, LOW);
    digitalWrite(GREEN_LED_PIN , LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
  delay(40);
}

void rising() {
  attachInterrupt(1, falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(1, rising, RISING);
  now = micros();
  if(now > prev_time) {
    pwm_value = micros()-prev_time;
  } else {
    pwm_value = micros()-prev_time-4294967295;
  }
}
