#include "ENGG1200.h"
/*
 * This file contains the actual code for the function prototypes
 * defined within ENGG1200.h; what this means is, when the Arduino IDE
 * goes to compile your code, it will first look at the .h file, and then 
 * here, to figure out what to do when you call the library functions
 * in your own sketch (the FDR.ino file). All functions are commented below
 */


bool radioNumber = 0; // Unique ID of radio

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10; in english, basically start using these pins for radio transmissions */
RF24 radio(9,10);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"}; // Used to store pipe addresses in setup; basically, computer version of a street address.

bool role = 1; // Used to control whether this node is sending or receiving. 0 = Receiver.


/*
 * Setup function to open the communication pipes between the FDR/FDT and Base Station.
 */
void setup_radio(void) {
    radio.begin();
    radio.openWritingPipe(addresses[1]); // Change these for base station
    radio.openReadingPipe(1,addresses[0]); // Change these for base station
}


/*
 * Transmission function. Pass it data, and it will send it to the 
 * base station. Place this inside a loop running at the rate
 * of transmission you think most appropriate.
 */
int transmit(Package data) {

    /*
    * Try to write the data down the pipe; 
    * if it fails, the if statement fires and reports an error;
    * if it succeeds, data has been sent. 
    */
    if (!radio.write(&data, sizeof(Package) )){ 
      Serial.print(F("Failed to send the following: "));
       Serial.println(data.x);
       Serial.println(data.y);
       Serial.println(data.z);
       return 0;
    } 

    return 1; // Return 1 (true) on success, 0 otherwise
    
    // We don't especially care to hear back from the base station;
    // as far as the FDR is concerned, it sent the data down the pipe.
}

int transmit_code(char* message) {
    if (!radio.write(message, sizeof(char) * 21)) {
        return 0;
    } else {

        return 1;
    }

}

void prep_data(Package* box, int16_t x, int16_t y, int16_t z, int16_t gx, 
        int16_t gy, int16_t gz, int16_t time) {
    box->x = x;
    box->y = y;
    box->z = z;
    box->gx = gx;
    box->gy = gy;
    box->gz = gz;
    box->timeVal = time;
}


