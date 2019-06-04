#include <i2c_t3.h>
#include <VL53L1X.h>

#define SHTDWN_SENSOR_2   17 //
#define SHTDWN_SENSOR_3   3 //
#define SHTDWN_SENSOR_1   16 //


const int num_lecturas = 10;
int lecturas[num_lecturas];
int indexlectura=0;
int total = 0;
int promedio = 0;
int promedioaux = 0;

int lecturas1[num_lecturas];
int total1 = 0;
int promedio1 = 0;
int promedioaux1 = 0;


/*
 *     enum i2c_pins {I2C_PINS_16_17 = 0,      // 16 SCL0  17 SDA0
                   I2C_PINS_18_19,          // 19 SCL0  18 SDA0
                   I2C_PINS_22_23,          // 22 SCL1  23 SDA1
                   I2C_PINS_DEFAULT,
                   I2C_PINS_COUNT};
 */
VL53L1X sensor1(i2c_t3(0),I2C_PINS_18_19);
VL53L1X sensor2(i2c_t3(0),I2C_PINS_18_19);
VL53L1X sensor3(i2c_t3(1),I2C_PINS_22_23);


void setup()
{
  pinMode(SHTDWN_SENSOR_1,OUTPUT);
  pinMode(SHTDWN_SENSOR_2,OUTPUT);
  pinMode(SHTDWN_SENSOR_3,OUTPUT);
  
  Serial.begin(115200);
  delay(1000);
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  
  digitalWrite(SHTDWN_SENSOR_1, HIGH);
  digitalWrite(SHTDWN_SENSOR_2, LOW);
  digitalWrite(SHTDWN_SENSOR_3, LOW);
  
  delay(5);

  
  //sensor.init();
  sensor1.setTimeout(500);
  
  if (!sensor1.init())
  {
    Serial.println("Failed to detect and initialize sensor1!");
    while (1);
  }

  //sensor1.setAddress(0x30);
  
  /*digitalWrite(SHTDWN_SENSOR_1, HIGH);
  digitalWrite(SHTDWN_SENSOR_2, HIGH);
  delay(10);
  sensor1.init();
  
  sensor2.setTimeout(500);
  if (!sensor2.init())
  {
    Serial.println("Failed to detect and initialize sensor2!");
    while (1);
  }

  sensor2.setAddress(0x32);

  sensor3.setTimeout(500);
  if (!sensor3.init())
  {
    Serial.println("Failed to detect and initialize sensor3!");
    while (1);
  }

  //sensor3.setAddress(0x32);
  
  */
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  //digitalWrite(SHTDWN_SENSOR_1, HIGH);
  //digitalWrite(SHTDWN_SENSOR_2, LOW);
  sensor1.setDistanceMode(VL53L1X::Short);
  sensor1.setMeasurementTimingBudget(100000);

  /*//digitalWrite(SHTDWN_SENSOR_1, LOW);
  //digitalWrite(SHTDWN_SENSOR_2, HIGH);
  sensor2.setDistanceMode(VL53L1X::Short);
  sensor2.setMeasurementTimingBudget(100000);

  sensor3.setDistanceMode(VL53L1X::Short);
  sensor3.setMeasurementTimingBudget(100000);

  */
  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  digitalWrite(SHTDWN_SENSOR_1, HIGH);
  digitalWrite(SHTDWN_SENSOR_2, HIGH);
  sensor1.startContinuous(100);
  
  /*digitalWrite(SHTDWN_SENSOR_1, HIGH);
  digitalWrite(SHTDWN_SENSOR_2, HIGH);
  sensor2.startContinuous(100); 

  sensor3.startContinuous(100); 
  */
}

int valor_sensor = 0;
int valor_sensor1 = 0;

void loop()
{ 
  int i = 0;//sensor1.readRangeContinuousMillimeters()/10;
  delay(45);
  digitalWrite(SHTDWN_SENSOR_2, HIGH);
  int j = sensor2.read()/10;
  digitalWrite(SHTDWN_SENSOR_2, LOW);
  delay(45);
  int k = 0;//sensor3.readRangeContinuousMillimeters()/10;
  delay(45);
  Serial.print(i);
  Serial.print(",");
  Serial.print(j);
  Serial.print(",");
  Serial.println(k);
  if (sensor1.timeoutOccurred()) { Serial.println(" TIMEOUT 1"); }
  if (sensor2.timeoutOccurred()) { Serial.println(" TIMEOUT 2"); }
  if (sensor3.timeoutOccurred()) { Serial.println(" TIMEOUT 3"); }
  
//  delay(45);
}
