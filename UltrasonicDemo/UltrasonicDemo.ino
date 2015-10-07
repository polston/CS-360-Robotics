//Packages
#include <Arduino.h>

//Global Variable Declarations
	
	//PINS

		//Input Pins
			const int sonicInputPin = 24;//PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE

		//Output Pins 
			const int sonicTriggerPin = 22;//PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE

	//GENERAL

		long reading;

void setup() {
	Serial.begin(9600);
	loadPins();
}

void loop() {
	reading = getSonicDistance(sonicInputPin, sonicTriggerPin);
	Serial.println(reading);	
  delay(200);

}



void loadPins(){
	//Input Pins
	pinMode(sonicInputPin, INPUT);

	//Output Pins
	pinMode(sonicTriggerPin, OUTPUT);
}

long getSonicDistance(int echoPin, int triggerPin){
	long distanceCM = 0;
	digitalWrite(triggerPin,HIGH);
	delayMicroseconds(300);
	digitalWrite(triggerPin,LOW);
	long duration = pulseIn(echoPin, HIGH,38000);
	long distance = (duration*34029L)/2000000L;
	distanceCM = distance;
	if(distanceCM == 0){
		distanceCM = 400;
	}   
	return (double)distanceCM; 
}

