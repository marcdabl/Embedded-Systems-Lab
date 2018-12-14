// ------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
// ------------------------------------------------
//Exercise 5 PID

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// define two tasks for Reference and for Control
void TaskReference( void *pvParameters );
void TaskFFControl( void *pvParameters );



const int TControl = 100;  // in milliseconds 
int ref = 2000;     //reference value
int pwm_pin = 9;    //PWM pin
int encd_pin = 3;   //Reading encoder pin
int error_map = 0;  //Error mapped to pwm values
unsigned long lastTime;   //last time we measured the time from the beginning of the execution
double errSum;            //Acumulated error
double lastErr;           //last error
double kp=0.5, ki=0.0001, kd=0.01;        //Proportional, integral and proportional constant
double Output;            //Output from PID
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

//Task for PID Control
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
      //Time from previous calculus
      unsigned long  now = millis();
      double timeChange = (double)(now-lastTime);

      //Error variables
      double error = ref - rpm;
      errSum += (error*timeChange);
      double dErr = (error-lastErr)/timeChange;

      //Output PID
      Output = kp*error + ki*errSum + kd*dErr;
      Output = map(Output, 0 ,9000, 0,255);
      //Saving some variables for future computations
      lastErr = error;
      lastTime = now;

      //System and Serial monitor
      pwm_value = pwm_value+Output;
      pwm_value = min(pwm_value,255);
      pwm_value = max(pwm_value,0);
      analogWrite(pwm_pin,pwm_value);
      //Serial Monitor
      Serial.print("Ref / real rpm / pwm: ");
      Serial.print(ref);
      Serial.print(" ");
      Serial.print(rpm);
      Serial.print(" ");
      Serial.print(Output);
      Serial.print(" ");
      Serial.println(pwm_value);
      

  }
}
