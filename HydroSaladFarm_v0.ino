#include <LiquidCrystal_I2C.h>

#define RELAY_PIN_SOLENOID_PLANTLAYER1 12
#define RELAY_PIN_SOLENOID_PLANTLAYER2 13
#define RELAY_PIN_SOLENOID_MIXTURE      7
#define RELAY_PIN_SOLENOID_WATERTANK    8
#define RELAY_PIN_PUMP                  4

#define MOTOR_PIN_NUTRIENTA             9
#define MOTOR_PIN_NUTRIENTB             6
#define MOTOR_PIN_PHUP                  5
#define MOTOR_PIN_PHDOWN                3

#define LED_PLANTLIGHT                  2 

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}