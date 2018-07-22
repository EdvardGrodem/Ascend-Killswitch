#include <Arduino.h>


#define PWM_IN_PIN 3
#define KILLSWITCH_PIN 2

bool let_signal_pass;

volatile int pwm_value = 0;
volatile long prev_time = 0;
volatile long now = 0;
void rising();
void falling();

void setup() {
  Serial.begin(115200);
  // when pin D2 goes high, call the rising function
  let_signal_pass = false;
  attachInterrupt(digitalPinToInterrupt(PWM_IN_PIN), rising, RISING);
  pwm_value = 0;
}

void loop() {
  if((pwm_value > 1500) && (pwm_value < 2500) && (micros() - prev_time < 50000)) {
    digitalWrite(KILLSWITCH_PIN, HIGH);
  } else {
    digitalWrite(KILLSWITCH_PIN, LOW);
  }
}

void rising() {
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(0, rising, RISING);
  now = micros();
  if(now > prev_time) {
    pwm_value = micros()-prev_time;
  } else {
    pwm_value = micros()-prev_time-4294967295;
  }
}
