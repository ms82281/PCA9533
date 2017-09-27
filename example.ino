// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCA9533

#include <Wire.h>
#include <PCA9533.h>

PCA9533 pca9533;                              // construct a new PCA9533 instance

void setup()
{
  // Initialise I2C communication
  Wire.begin(12,14);
  // Initialise serial communication
  Serial.begin(115200);
  delay(300);
  Serial.println("Starting device");
  // Setup PCA9533 and do some initial tests
  Serial.println("Setup LED Controller");
  // make sure device testing starts with default settings
  pca9533.init();
  Serial.println("Running init tests");
  Serial.print("Checking I2C Bus: ");
  Serial.println(pca9533.ping());
  pca9533.setMode(ALL_ON);
  delay(1000);
  pca9533.setMode(ALL_OFF);
  delay(1000);
  // Setup PCA9533 to our HW Environment
  Serial.println("Resuming normail boot");
  pca9533.setPSC(REG_PSC0, 0);
  pca9533.setPSC(REG_PSC1, 0);
  pca9533.setMode(IO0, LED_MODE_PWM0);
  pca9533.setMode(IO1, LED_MODE_PWM1);
  pca9533.setMode(IO2, LED_MODE_ON);
  pca9533.setMode(IO3, LED_MODE_OFF);
}

void loop()
{
  // Test LED1
  Serial.println("Testing LED1 from 0% to 100% in 25% steps");
  pca9533.setMode(IO2, LED_MODE_ON);
  pca9533.setMode(IO3, LED_MODE_OFF);
  // Set PWM to 0%
  Serial.println("LED1 = 0");
  pca9533.setPWM(REG_PWM0, 0);
  delay(2000);
  Serial.println("LED1 = 25");
  pca9533.setPWM(REG_PWM0, 64);
  delay(2000);
  Serial.println("LED1 = 50");
  pca9533.setPWM(REG_PWM0, 128);
  delay(2000);
  Serial.println("LED1 = 75");
  pca9533.setPWM(REG_PWM0, 192);
  delay(2000);
  Serial.println("LED1 = 100");
  pca9533.setPWM(REG_PWM0, 255);
  delay(2000);
  Serial.println("LED1 = 0");
  pca9533.setPWM(REG_PWM0, 0);
  delay(20);

  // Test LED2
  Serial.println("Testing LED2 from 0% to 100% in 25% steps");
  pca9533.setMode(IO2, LED_MODE_OFF);
  pca9533.setMode(IO3, LED_MODE_ON);
  Serial.println("LED2 = 0");
  pca9533.setPWM(REG_PWM1, 0);
  delay(2000);
  Serial.println("LED2 = 25");
  pca9533.setPWM(REG_PWM1, 64);
  delay(2000);
  Serial.println("LED2 = 50");
  pca9533.setPWM(REG_PWM1, 128);
  delay(2000);
  Serial.println("LED2 = 75");
  pca9533.setPWM(REG_PWM1, 192);
  delay(2000);
  Serial.println("LED2 = 100");
  pca9533.setPWM(REG_PWM1, 255);
  delay(2000);
  Serial.println("LED2 = 0");
  pca9533.setPWM(REG_PWM1, 0);
  delay(20);
}  
