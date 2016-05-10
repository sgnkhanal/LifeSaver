/**
 * @Author- Sagun Khanal
 * This program listens to a seismic sensor connected to the Photon.
 * When a certain minimum data is read and meets our criteria, the data is published to 
 * the cloud. At the same time different alerts like Light, Buzzer are triggered.
 * 
 */

//for testing purpose this value was adjusted after recording various readings
//and subtracting the false alerts.
int minScale = 1500;
int measuredScale = 0;

// for now defaulted to my home residence in Nepal.
String location = "Kathmandu"; 

//define the pins for output
int buzzerPin = D7;
int turnLight = D7;

//define the pins for input
int quakeSensor = A0;
int safeButton = A5;

void setup() {
    pinMode(quakeSensor, INPUT);
    // pinMode(safeButton, INPUT);
    pinMode(turnLight, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
}

void loop() {
    
    //Safe button implementation
    // int safeButtonState=0;
    // safeButtonState = digitalRead(safeButton);
    
    if(digitalRead(safeButton)) {
        Spark.publish("safe", "Safe");
    }
    // safeButtonState = HIGH;
    
    //read the analog data
    measuredScale = (analogRead(quakeSensor));

    // //if data matches, do the following steps:-
    // // 1. Publish the event to the cloud
    // // 2. Turn the lights on
    // // 3. Turn the buzzer on
    // // 4. delay for 10 seconds and loop again.
    if(measuredScale > minScale) {
        //publish events when measured scale hits minimum scale.
        Spark.publish("alert", "Earthquake");
        Spark.publish("measuredScale", String(measuredScale));
        Spark.publish("location", location);

        // go in a loop for buzzer and light for about 10 seconds.
        for (int i=1; i<11; i++) {
            beep(50);
            delay(500);
            digitalWrite(turnLight, HIGH);
            delay(500);
            digitalWrite(turnLight, LOW);
            i = i++;
        }
        
    }
}   

//buzzer beep
void beep(unsigned char delayms){
  analogWrite(buzzerPin, HIGH);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(buzzerPin, HIGH);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
} 
