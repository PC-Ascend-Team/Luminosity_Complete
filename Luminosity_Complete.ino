// Includes the libraries
//tada
#include <SparkFunTSL2561.h>
#include <Wire.h>

// Create an SFE_TSL2561 object, here called "light":

SFE_TSL2561 light;

// Global variables:

boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

void setup()
{
  // Initialize the Serial port:
  
  Serial.begin(9600);
  Serial.println("TSL2561 example sketch");

  light.begin();
  
  // If gain = false (0), device is set to low gain (1X)
  // If gain = high (1), device is set to high gain (16X)

  gain = 0;

  // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  // If time = 3, use manual start / stop to perform your own integration

  unsigned char time = 2;

  light.setTiming(gain,time,ms);

  // To start taking measurements, power up the sensor:
  
  light.setPowerUp();
  
  // The sensor will now gather light during the integration time.
}

void loop()
{

  
  // Once integration is complete, we'll retrieve the data.
  
  // Retrieve the data from the device:

  unsigned int data0, data1;
  
  if (light.getData(data0,data1))
  {
    
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
  
    double lux;    // Resulting lux value
    boolean good;  // True if neither sensor is saturated
    
    // Perform lux calculation:

    good = light.getLux(gain,ms,data0,data1,lux);
    
    // Print out the results:
    
    Serial.print("$, , , , , , , , , , , ,");
    Serial.print(data0);
    Serial.print(", ");
    Serial.print(data1);
    Serial.print(", ");
    Serial.print(lux);
    Serial.print("\n");
    
  }
  else
  {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    printError(error);
  }
}

void printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}
