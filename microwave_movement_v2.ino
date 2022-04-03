int Sensor = 2;   //Input Pin
int LED = 13;     // Led pin for Indication
 
int flg = 0;  //Change detection flag
void setup() {
  Serial.begin(9600);
  pinMode (Sensor, INPUT);  //Define Pin as input
  pinMode (LED, OUTPUT);    //Led as OUTPUT
  Serial.println("Waiting for motion");
}
 
void loop() {
     int val = digitalRead(Sensor); //Read Pin as input
     
     if((val > 0) && (flg==0))
     {
        digitalWrite(LED, HIGH);
        Serial.println("Motion Detected");
        flg = 1;
     }
 
     if(val == 0)
     {
        digitalWrite(LED, LOW);
        flg = 0;
     }  
     delay(100);
}
