// ------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
// ------------------------------------------------

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Reference and for Control
void TaskReference( void *pvParameters );
void TaskFFControl( void *pvParameters );



const int TControl = 100;  // in milliseconds 
int ref = 2000; //reference value
int pwm_pin = 9;
int encd_pin = 3;
// -------
// setup
// -------

void setup() {

  // create first task
  xTaskCreate(
    TaskReference
    ,  (const portCHAR *)"Reference"  // name
    ,  128                        // stack size
    ,  NULL
    ,  2                         // lower priority
    ,  NULL );
  // create second task
  xTaskCreate(
    TaskFFControl
    ,  (const portCHAR *) "FFControl"
    ,  128 
    ,  NULL
    ,  1                         // higher priority
    ,  NULL );
  // now the task scheduler is automatically started
}

// ------
// loop
// ------

void loop() {
// empty!
}

//Task for getting the set point
void TaskReference(void *pvParameters) {
  (void) pvParameters;

  // forever loop
  while(1) {
         vTaskDelay(10000/portTICK_PERIOD_MS); // 10s delay
         
      if(ref==2000){
        ref = 3000;
      }
      else{
        ref = 2000;
      }

      }
   }

//Task for Feedforward control
void TaskFFControl(void *pvParameters) {
  (void) pvParameters;
  
  int pwm_value = 0;
  int sigup = 0;
  int rpm = 0;
  int TS = 0;
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS(TControl);
  
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  pinMode(encd_pin,INPUT_PULLUP);
  pinMode(pwm_pin,OUTPUT);
  xLastWakeTime = xTaskGetTickCount(); // current tick count
  
  // forever loop
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime,xPeriod);
      //Implementing feedforward control
       sigup = pulseIn(encd_pin,HIGH);
      TS = 4*sigup;
      rpm = 60000000/TS;
      pwm_value = map(ref, 0 ,9000, 0,255);
      analogWrite(pwm_pin,pwm_value);
      //Serial Monitor
      Serial.print("Ref / real rpm / pwm: ");
      Serial.print(ref);
      Serial.print(" ");
      Serial.print(rpm);
      Serial.print(" ");
      Serial.println(pwm_value);
      

  }
}
