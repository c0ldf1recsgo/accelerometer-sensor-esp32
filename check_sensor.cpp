#include "Wire.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

const float kTargetHz = 125;
const float kTargetMs = 1000.0/kTargetHz;

long t0;

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

}

void loop() {
    // read raw accel measurements from device
    sensors_event_t event;
    accel.getEvent(&event);

    if (t0 + kTargetMs >= millis()) return;

    t0 = millis();
    
    Serial.print("\t");
    Serial.print(event.acceleration.x);
    Serial.print("\t");
    Serial.print(event.acceleration.y);
    Serial.print("\t");
    Serial.println(event.acceleration.z);
}
