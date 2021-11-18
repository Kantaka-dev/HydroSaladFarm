//#include <LiquidCrystal_I2C.h>
//#include <Time.h>

#define DEBUG 0

#define RELAY_PIN_SOLENOID_PLANTLAYER1  12
#define RELAY_PIN_SOLENOID_PLANTLAYER2  13
#define RELAY_PIN_SOLENOID_MIXTURE      7
#define RELAY_PIN_SOLENOID_WATERTANK    8

#define RELAY_PIN_PUMP                  52
#define PUMP_ON   0
#define PUMP_OFF  1

#define MOTOR_PIN_NUTRIENTA             9
#define MOTOR_PIN_NUTRIENTB             6
#define MOTOR_PIN_PHUP                  5
#define MOTOR_PIN_PHDOWN                3

#define LED_MANUALPUMP_STATE            47
#define LED_AUTOPUMP_STATE              49
#define SWITCH_MANUALPUMP_STATE         51
#define SWITCH_AUTOPUMP_STATE           53

#define LED_PLANTLIGHT                  2 

unsigned long timer_sec = 0;
unsigned long timer_prev = 0;
unsigned long controlTimeStamp = 0;

bool state_floodanddrain_Auto = 1;

/*========================================SETUP===================================================*/
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(LED_AUTOPUMP_STATE, OUTPUT);
  pinMode(LED_MANUALPUMP_STATE, OUTPUT);
  pinMode(SWITCH_AUTOPUMP_STATE, INPUT);
  pinMode(SWITCH_MANUALPUMP_STATE, INPUT);
  
  pinMode(RELAY_PIN_PUMP, OUTPUT);
  
  /*======================================DEBUG=====================================*/
  if (DEBUG)
  {
    Serial.begin(9600);
  }
  /*====================================end DEBUG===================================*/
}

/*=========================================LOOP===================================================*/
void loop() {
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second

  timer_sec = floor(millis()/1000);
//  timer_sec = millis();

  /*======================================DEBUG=====================================*/
  if (DEBUG)
  {
    if (timer_sec != timer_prev) {
      Serial.print("time : ");
      Serial.print(timer_hr()%24);
      Serial.print(" hr. ");
      Serial.print(timer_min()%60);
      Serial.print(" min. ");
      Serial.print(timer_sec%60);
      Serial.println(" second");
    }
    timer_prev = timer_sec;
  }
  /*====================================end DEBUG===================================*/

  // Control loop frequency 1Hz (every 1 sec)
  if (millis() - controlTimeStamp >= 1000)
  {
    if (!digitalRead(SWITCH_MANUALPUMP_STATE))                  // Manual Pump
    {
      digitalWrite(RELAY_PIN_PUMP, PUMP_ON);
      digitalWrite(LED_MANUALPUMP_STATE, !digitalRead(LED_MANUALPUMP_STATE));
      digitalWrite(LED_AUTOPUMP_STATE, 0);
    }
    else if (!digitalRead(SWITCH_AUTOPUMP_STATE))               // Auto Pump
    {
      FloodAndDrain(timer_min(), 60, 120, 4, RELAY_PIN_PUMP);
//      FloodAndDrain(timer_sec, 60, 120, 4, RELAY_PIN_PUMP);

      digitalWrite(LED_MANUALPUMP_STATE, 0);
    }
    else
    {
      digitalWrite(RELAY_PIN_PUMP, PUMP_OFF);
      digitalWrite(LED_AUTOPUMP_STATE, 0);
      digitalWrite(LED_MANUALPUMP_STATE, 0);
    }
    
    controlTimeStamp = millis();
  }
}


void FloodAndDrain(unsigned long timer, uint8_t flood_period, uint8_t drain_period, uint8_t sequence, uint8_t output_pump) 
{
// parameters unit in minute

  timer = timer % 1440;                                       // 1 day = 24 hrs = 1440 minutes
  
  if (timer <= (flood_period+drain_period)*sequence)          // DAY Time
  {
    if (timer%(flood_period+drain_period) <= flood_period) {    // Flooding time
      digitalWrite(RELAY_PIN_PUMP, PUMP_ON);
      digitalWrite(LED_AUTOPUMP_STATE, !digitalRead(LED_AUTOPUMP_STATE));
    }
    else {                                                      // Draining time
      digitalWrite(RELAY_PIN_PUMP, PUMP_OFF);
      digitalWrite(LED_AUTOPUMP_STATE, 0);
    }
  }
  else {                                                      // NIGHT Time
    digitalWrite(RELAY_PIN_PUMP, PUMP_OFF);
    digitalWrite(LED_AUTOPUMP_STATE, 1);
  }
}

unsigned long timer_min() {
  return floor(timer_sec/60);
}
unsigned long timer_hr() {
  return floor(timer_sec/360);
}
