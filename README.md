# NodeMCU-ADXL345-Fall-Detector

This project utilizes the ADXL345 tilt sensor in combination with an ESP8266 microcontroller to detect falls. The ADXL345 sensor, primarily a tilt sensor, is repurposed here to detect sudden changes in acceleration that indicate a fall event. The code continuously monitors the sensor readings, calculating the magnitude of acceleration and its rate of change to identify potential falls.

## Hardware Requirements
- ESP8266 (NodeMCU)
- ADXL345 Sensor

## Setup Instructions
1. Wire the ADXL345 sensor to the ESP8266 according to your hardware setup.
2. Upload the provided code to the ESP8266 using the Arduino IDE or preferred platform.

## Code Explanation
- The code initializes the ADXL345 sensor and configures it to detect changes in acceleration.
- It continuously reads the sensor data, calculates the magnitude of the acceleration vector, and monitors the rate of change of this magnitude.
- If a significant change in magnitude (beyond a defined threshold) is detected with a substantial rate of change, and no fall has been detected within a cooldown period, the system flags a fall event.

## Cost-Effectiveness
This project showcases the utilization of the ADXL345, originally a tilt sensor, to detect falls. While dedicated fall sensors might be more expensive, the ADXL345, primarily intended for tilt sensing, can be repurposed to serve as a fall detector. This method offers a cost-effective solution for fall detection by leveraging a more affordable sensor, making it accessible for various applications.

Ensure the appropriate sensitivity adjustments and hardware configuration based on your specific use case. 
