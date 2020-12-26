
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// I2Cdev and ADXL345 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "ADXL345.h"

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

int16_t ax, ay, az;

#define SDA 0
#define SCL 4

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin(SDA, SCL, 400000);

    // initialize serial communication
    Serial.begin(115200);

    // Print out if there is no sensor was detected
    if (!accel.begin()){
      Serial.println("NO SENSOR");
      while(1);
    }
    else{
      Serial.println("ADXL345 connection successful");
    }


}

void loop() {
    // read raw accel measurements from device
    sensors_event_t event;
    accel.getEvent(&event);

    Serial.print("accel:\tX: ");
    Serial.print(event.acceleration.x);
    Serial.print("\tY: ");
    Serial.print(event.acceleration.y);
    Serial.print("\tZ: ");
    Serial.println(event.acceleration.z);

}
