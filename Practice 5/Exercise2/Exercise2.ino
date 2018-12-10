// ------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
// ------------------------------------------------

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Blink & AnalogRead
void TaskPWM( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
SemaphoreHandle_t xSemaphore;


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
    ,  2                          // lower priority
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
// first task: Reading D0
// --------------------------
int pwm_value = 10;
int pwm_pin = 9;

void TaskPWM(void *pvParameters) {
  (void) pvParameters;
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  // forever loop
  for (;;) {
   pwm_value = min(pwm_value+30,255);
    analogWrite(pwm_pin,pwm_value);
    vTaskDelay(2000/portTICK_PERIOD_MS); // wait for 2 seconds
  }
}


// ------------------------
// second task: reading A0
// ------------------------

void TaskAnalogRead(void *pvParameters) {
  (void) pvParameters;
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  // forever loop
  for (;;) {
      int sensorValue = analogRead(A0);  // read analog input A0
      Serial.print("Encoder FanSpeed: ");
      Serial.print(sensorValue);
      Serial.print(" ");
      Serial.println(pwm_value);
      vTaskDelay(1);                       // one tick (smallest) delay
  }
}
