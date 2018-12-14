// ------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
// ------------------------------------------------

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Blink & AnalogRead
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
SemaphoreHandle_t xSemaphore;


// -------
// setup
// -------

void setup() {
  xSemaphore = xSemaphoreCreateMutex();
  // create first task
  xTaskCreate(
    TaskDigitalRead
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

void TaskDigitalRead(void *pvParameters) {
  (void) pvParameters;
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  // forever loop
  for (;;) {
    int sensorValue = digitalRead(2);  // read analog input A0
     /* Attempt to create a semaphore. */
    if( xSemaphore != NULL ) {
      if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) {
        /* We were able to obtain the semaphore and can now access the
        shared resource. */
        Serial.print("Reading Digital Input: ");
        Serial.println(sensorValue);       // send through serial port

        /* We have finished accessing the shared resource.  Release the
        semaphore. */
        xSemaphoreGive( xSemaphore );
      }
    }
    vTaskDelay(1);                     // one tick (smallest) delay
  }
}

// ------------------------
// second task: reading A0
// ------------------------

void TaskAnalogRead(void *pvParameters) {
  (void) pvParameters;
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  // forever loop
  for (;;) {
    int sensorValue = analogRead(A0);  // read analog input A0
     /* Attempt to create a semaphore. */
    if( xSemaphore != NULL ) {
      if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) {
        /* We were able to obtain the semaphore and can now access the
        shared resource. */
        Serial.print("Reading Analog Input: ");
        Serial.println(sensorValue);       // send through serial port

        /* We have finished accessing the shared resource.  Release the
        semaphore. */
        xSemaphoreGive( xSemaphore );
      }
    }
    vTaskDelay(1);                       // one tick (smallest) delay
  }
}
