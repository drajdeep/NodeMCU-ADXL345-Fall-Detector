#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define ADXL345_ADDRESS (0x53) // ADXL345 I2C address

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Assign a unique ID

bool fallDetected = false;
unsigned long lastFallTime = 0;
unsigned long cooldownPeriod = 5000; // Cooldown period in milliseconds (adjust as needed)
float lastMagnitude = 0;
float rateOfChangeThreshold = 50.0; // Adjust this value based on sensitivity requirements

void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Wait for Serial Monitor

  // Initialize the ADXL345 sensor
  if (!accel.begin(ADXL345_ADDRESS))
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1)
      delay(10);
  }

  // Set accelerometer range (±2g, ±4g, ±8g, ±16g)
  accel.setRange(ADXL345_RANGE_2_G);

  Serial.println("ADXL345 found and initialized!");
}

void loop(void)
{
  // Read accelerometer data
  sensors_event_t event;
  accel.getEvent(&event);

  // Calculate the magnitude of the acceleration vector
  float magnitude = sqrt(event.acceleration.x * event.acceleration.x +
                         event.acceleration.y * event.acceleration.y +
                         event.acceleration.z * event.acceleration.z);

  // Calculate the rate of change of acceleration
  float rateOfChange = abs(magnitude - lastMagnitude);

  // Check if the magnitude exceeds a threshold and rate of change is significant
  float threshold = 10.0; // You may need to adjust this value based on your setup and sensitivity requirements

  if (magnitude > threshold && rateOfChange > rateOfChangeThreshold && !fallDetected && (millis() - lastFallTime) > cooldownPeriod)
  {
    Serial.println("Fall detected!");
    fallDetected = true;
    lastFallTime = millis(); // Record the time of the fall event
  }

  // Check if cooldown period has passed and reset the fallDetected flag
  if (fallDetected && (millis() - lastFallTime) > cooldownPeriod)
  {
    fallDetected = false;
  }

  lastMagnitude = magnitude; // Store the current magnitude for the next iteration
  delay(100); // Adjust the delay to set the sampling frequency. Currently set to 0.1 seconds.
}
