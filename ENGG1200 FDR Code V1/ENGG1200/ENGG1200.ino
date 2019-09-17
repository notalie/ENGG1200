#include "ENGG1200.h"
#include "RF24.h" // Unavoidable due to the way Arduino loves to link files; if this was just a normal compiler it'd be possible :)))))
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>


/*
 * This code is written by ENGG1200 course staff. Any issues with this code, including any overlooked bugs
 * or inconsistencies, please email uqjmacd9@uq.edu.au and an update will be released as soon as possible.  
 * As with any software, there may be bugs; welcome to software engineering! :)
 */

 
// All the offsets you need
int xOffset = 0, yOffset = 0, zOffset = 0 * mod_offset, xGyro = 0, yGyro = 0,zGyro = 0;
int buttonPin = 13;
int16_t ax, ay, az;
int16_t gx, gy, gz;
MPU6050 accelgyro; // This is the name of your accelerometer.

Package data_package; // refer to this with an & in front when prepping data, without otherwise


char teamCode[20] = "PUT YOUR TEAM HERE"; // Max 20 chars 


// Setup function, initalizes your FDR/FDT to be set up to transmit data. Pipes configured for transmitting only.
void setup() {
  Serial.begin(9600); // Open the serial monitor at this baud rate.
  Wire.begin();
  accelgyro.initialize();
  accelgyro.setXGyroOffset(xGyro);
  accelgyro.setYGyroOffset(yGyro);
  accelgyro.setZGyroOffset(zGyro); 
  accelgyro.setXAccelOffset(xOffset);
  accelgyro.setYAccelOffset(yOffset);
  accelgyro.setZAccelOffset(zOffset);
  
  setup_radio(); // Call library method to initalize the RF transmitter on the FDR
  
  // EXAMPLE USAGE OF TRANSMISSION BELOW
  // prep_data(&data_package, ax, ay, az, gx, gy, gz, 100);
  // transmit(data_package);
  transmit_code(teamCode);

}


// Remember, the base station will not start receiving until you send your access code. 


void loop() {
    
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Use this line of code to make the variables equal to what the accelerometer is currently reading
   prep_data(&data_package, ax, ay, az, gx, gy, gz, millis()/1000); // This line of codes prepares the data by updating the variable "data_package" to contain the readings of the accelerometer and current time
   transmit(data_package); // This line of code sends the data to the base station, returns 0 on success and 1 if it's not

   // The rest is up to you to determine how to calculate flight time, determine launch and land, and convert time to binaey and display on the LEDS + transmit at required freq. Good luck!
}

// Angle of attack is 5 - check ax, ay or az
// If not landed and positive acceleration - set in flight
// If in flight and not landed - transmit
// If not landed and negative acceleration - set landed
// Delay

/* The below code is an example of how one would do the button code for their FDR.
 *  You place the required functionality in the relevant IF statements for what you want the FDR
 *  to do when you have held and released the button after a set amount of time. 
 */

int buttonState = 0, lastState = 0; // Used to determine if pressed or not
int pressTime, releaseTime;



void button_press(void) {
  
  buttonState = digitalRead(buttonPin); // Read the current button value
  
  if (buttonState != lastState) { // Check if it is now different than last time?
    
      lastState = buttonState; // If so, update last state
      
      if (buttonState) { // If we just turned on, record time
        pressTime = millis();
      } else { // If we just let go, record time
        releaseTime = millis();

        if (releaseTime - pressTime < 1000) { // Determine length and do something based on these
          // Do something for short press; transmit team coords?
        } else if (releaseTime - pressTime > 1000 && releaseTime - pressTime < 5000) {
          // Do Something for medium press
        } // ??? How would you add more button press times? Look at above code for hints!
      }
  }
}
