#include <EloquentTinyML.h>
#include "tflite-trained.h"

#define NUMBER_OF_INPUTS 936
#define NUMBER_OF_OUTPUTS 5
#define TENSOR_ARENA_SIZE 7744

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

#include "Wire.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

const float kTargetHz = 125;
const float kTargetMs = 1000.0/kTargetHz;

long t0;

//define LED Pin
#define PIN0 16
#define PIN1 17
#define PIN2 5
#define PIN3 18
#define PIN4 23
#define PIN5 19

int findMax(float output[]);
void ledMode(int label_num);
void ledSetup();

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin(0, 4, 400000);

    // initialize serial communication
    Serial.begin(115200);
    while (!Serial){
      delay(10);
    }

    // Print out if there is no sensor was detected
    if (!accel.begin()){
      Serial.println("NO SENSOR");
      while(1);
    }

    accel.setRange(ADXL345_RANGE_2_G);

    ml.begin(trained_tflite);

    ledSetup();
}

float input[NUMBER_OF_INPUTS] = {0};
float output[NUMBER_OF_OUTPUTS] = {0};
int pos = 0;

void loop() {
    // read raw accel measurements from device
    sensors_event_t event;
    accel.getEvent(&event);

    if (t0 + kTargetMs >= millis()) return;

    t0 = millis();

    input[pos] = event.acceleration.x;
    input[pos+1] = event.acceleration.y;
    input[pos+2] = event.acceleration.z;
    pos += 3;


    if (pos>=NUMBER_OF_INPUTS) {
      pos = 0;
      float predicted = ml.predict(input, output);
      char* labels[] = { "idle", "on", "off", "updown", "wave" };
      for (int i=0; i<NUMBER_OF_OUTPUTS; i++) {
        Serial.print(labels[i]);
        Serial.print(":");
        Serial.print(output[i]);
        Serial.print("; ");
      }
      Serial.println("=> Result: ");
      Serial.print(labels[findMax(output)]);
      ledMode(findMax(output));
      Serial.print("\t");
    }

}

void ledSetup(){
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(PIN5, OUTPUT);
}

void ledMode(int label_num){
  int pinArray[6] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5};
  switch (label_num)
  {
  case 0:
    for(int i = 0; i < 5; i++){
      digitalWrite(PIN0, HIGH);
      digitalWrite(PIN1, HIGH);
      digitalWrite(PIN2, HIGH);
      digitalWrite(PIN3, HIGH);
      digitalWrite(PIN4, HIGH);
      digitalWrite(PIN5, HIGH);
      delay(200);
      digitalWrite(PIN0, LOW);
      digitalWrite(PIN1, LOW);
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN3, LOW);
      digitalWrite(PIN4, LOW);
      digitalWrite(PIN5, LOW);
    }
    break;
  case 1:
      digitalWrite(PIN0, HIGH);
      digitalWrite(PIN1, HIGH);
      digitalWrite(PIN2, HIGH);
      digitalWrite(PIN3, HIGH);
      digitalWrite(PIN4, HIGH);
      digitalWrite(PIN5, HIGH);
    break;
  case 2:
      digitalWrite(PIN0, LOW);
      digitalWrite(PIN1, LOW);
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN3, LOW);
      digitalWrite(PIN4, LOW);
      digitalWrite(PIN5, LOW);
    break;
  case 3:
      for(int i = 0; i < 5; i++){
      digitalWrite(PIN0, HIGH);
      digitalWrite(PIN2, HIGH);
      digitalWrite(PIN4, HIGH);
      digitalWrite(PIN1, LOW);
      digitalWrite(PIN3, LOW);
      digitalWrite(PIN5, LOW);
      delay(200);
      digitalWrite(PIN0, LOW);
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN4, LOW);
      digitalWrite(PIN1, HIGH);
      digitalWrite(PIN3, HIGH);
      digitalWrite(PIN5, HIGH);
    }
    break;
  case 4:
      for(int i = 0; i < 5; i++){
      digitalWrite(pinArray[i], HIGH);
      delay(200);
      digitalWrite(pinArray[i], LOW);
    }
    break;

  default:
    break;
  }
}

int findMax(float output[]){

  int max = 0;
  for (int i = 0; i < 5; ++i) {
    if (output[max] < output[i])
        max = i;
  }
  
  return max;
}
