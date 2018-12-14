// ------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
// ------------------------------------------------

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for PWM and Analog Read
void TaskPWM( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
SemaphoreHandle_t xSemaphore;
const int TRead = 40;  // in milliseconds 

// -------
// setup
// -------

void setup() {
  xSemaphore = xSemaphoreCreateMutex();
  // create first task
  xTaskCreate(
    TaskPWM
    ,  (const portCHAR *)"Blink"  // name
    ,  128                        // stack size
    ,  NULL
    ,  1                         // lower priority
    ,  NULL );
  // create second task
  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128 
    ,  NULL
    ,  2                         // higher priority
    ,  NULL );
  // now the task scheduler is automatically started

}

// ------
// loop
// ------

void loop() {
// empty!
}

// --------------------------
// first task: PWM signal
// --------------------------
int pwm_value = 0;
int pwm_pin = 9;
int encd_pin = 2;

void TaskPWM(void *pvParameters) {
  (void) pvParameters;
  
  pinMode(pwm_pin,OUTPUT);
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  // forever loop
  for (;;) {
   pwm_value = min(pwm_value+30,255);
    analogWrite(pwm_pin,pwm_value);
    vTaskDelay(4000/portTICK_PERIOD_MS); // wait for 4 seconds
  }
}


// ------------------------
// second task: reading Analog signal
// ------------------------

void TaskAnalogRead(void *pvParameters) {
  (void) pvParameters;
  
  int sigup = 0;
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS(TRead);
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  pinMode(encd_pin,INPUT_PULLUP);
  xLastWakeTime = xTaskGetTickCount(); // current tick count
  // forever loop
  for (;;) {
      vTaskDelayUntil(&xLastWakeTime,xPeriod);
      int sensorValue = digitalRead(encd_pin);  // read digital input 2
      sigup = pulseIn(encd_pin,HIGH);
      int TS = 4*sigup;
      int rpm = 60000000/TS;              //Formula TS = 60/N (SEC) (LAB 1)
      Serial.print("Encoder FanSpeed: ");
      Serial.print(rpm);
      Serial.print(" ");
      Serial.println(pwm_value);
  }
}
