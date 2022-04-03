#include <Servo.h>
const int buttonPin = 8; //pin for button

Servo servo_tube;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  servo_tube.attach(9);  // set the tube servo to digital pin 9
  servo_tube.write(0);  // set the starting position of the servo to 0
}

void loop() {
  int buttonState;  // local variable to hold the pushbutton states

  //read the digital state of buttonPin with digitalRead() function and store the value in buttonState variable
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  //if the button is pressed increment counter and wait a tiny bit to give us some time to release the button
  if (buttonState == HIGH) // When button is pressed rotate the tube and return tostarting position
  {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo_tube.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);   // takes 5ms for the servo to reach the position
    }
    
    delay(1000); //wait for 1 second to deposit candy
  
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo_tube.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5); // takes 5ms for the servo to reach the position
    }
    Serial.println(servo_tube.read());
    servo_tube.write(0);  // reset position to 0 if it got stuck
  }

  

}
