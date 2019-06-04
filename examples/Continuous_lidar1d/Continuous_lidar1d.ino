/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/

#include <i2c_t3.h>
#include <VL53L1X.h>

int led = 13;
#define SENSOR_1 17
#define SENSOR_2 16

VL53L1X sensor1, sensor2, sensor3(i2c_t3(1),I2C_PINS_22_23);

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  
  pinMode(led,OUTPUT);
  pinMode(SENSOR_1,OUTPUT);
  pinMode(SENSOR_2,OUTPUT);

  //Wire.begin();
  //Wire.setClock(400000); // use 400 kHz I2C

  digitalWrite(SENSOR_1,LOW);
  digitalWrite(SENSOR_2,LOW);

  sensor3.setTimeout(500);
  if (!sensor3.init())
  {
    Serial.println("Failed to detect and initialize sensor 3!");
    while (1);
  }
  
  sensor3.setAddress(0x36);
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor3.setDistanceMode(VL53L1X::Short);
  sensor3.setMeasurementTimingBudget(33000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor3.startContinuous(40);
  
  
  digitalWrite(SENSOR_1,HIGH);

  
  sensor1.setTimeout(500);
  if (!sensor1.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  sensor1.setAddress(0x32);
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor1.setDistanceMode(VL53L1X::Long);
  sensor1.setMeasurementTimingBudget(33000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor1.startContinuous(40);

  
  digitalWrite(SENSOR_2,HIGH);
  sensor2.setTimeout(500);
  if (!sensor2.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    while (1);
  }
  sensor2.setAddress(0x34);
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor2.setDistanceMode(VL53L1X::Short);
  sensor2.setMeasurementTimingBudget(22000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor2.startContinuous(25);

  
  for (int i = 0; i < 3; ++i) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);               // wait for a second
  }
 
}

void loop()
{
  Serial.print(sensor1.read());
  if (sensor1.timeoutOccurred()) {
    Serial.print(" TIMEOUT 1");
    for (int i = 0; i < 10; ++i) {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(20);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(20);               // wait for a second
    }
  }

  Serial.print(",");
  Serial.print(sensor2.read());
  Serial.print(",");
  if (sensor2.timeoutOccurred()) {
    Serial.println(" TIMEOUT 2");
    for (int i = 0; i < 10; ++i) {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(20);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(20);               // wait for a second
    }
  }

  Serial.print(sensor3.read());
  Serial.println();
  if (sensor3.timeoutOccurred()) {
    Serial.println(" TIMEOUT 3");
    for (int i = 0; i < 10; ++i) {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(20);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(20);               // wait for a second
    }
  }
  /*Serial.println();
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(50);     */ 
  
  

  //delay(500);
  
}
