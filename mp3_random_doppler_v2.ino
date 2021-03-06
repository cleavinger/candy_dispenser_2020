/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
 This example shows the basic function of library for DFPlayer.

 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int Sensor = 12;   // Doppler Input Pin
int LED = 13;     // Led pin for Indication
int flg = 0;  //Change doppler detection flag

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);



void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  pinMode (Sensor, INPUT);  //Define Doppler pin as input
  pinMode (LED, OUTPUT);    //Define Led as OUTPUT
  Serial.println("Waiting for motion");
  
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  randomSeed(analogRead(A0)); //get randomseed for random number
}

void loop()
{
   int val = digitalRead(Sensor); //Read Pin as input

 /*
  * Get current track playing and see if current track matches completed track
  * If it doesn't match then let it play, if it matches then move to next random
  * 
            if(myDFPlayer.readType()==DFPlayerPlayFinished && myDFPlayer.readCurrentFileNumber()==2) { 
              Serial.println(F("audio finished..."));
             
              myDFPlayer.loop(3);
              doCompletionCheck = false;
            }
            */

//Doppler Detection

  if((val > 0) && (flg==0))
     {
        digitalWrite(LED, HIGH);
        Serial.println("Motion Detected");
        flg = 1;
        int int_rand = random(1,1553);
        Serial.print("Doppler Playing: ");  //string here
        Serial.print(int_rand); //int here
        Serial.println();      //change line
    
        myDFPlayer.playMp3Folder(int_rand);
        delay(7000); //
        myDFPlayer.pause(); //stop the current track
        digitalWrite(LED, LOW);
        if (myDFPlayer.available()) {
          printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
        }
        delay(5000);// wait for the next search time

       digitalWrite(LED, LOW);
       flg = 0;

        }
      //static unsigned long timer = millis();
    
       
  

  
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
