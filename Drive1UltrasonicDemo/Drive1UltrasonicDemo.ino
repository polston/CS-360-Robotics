//Packages
#include <Arduino.h>

//Global Variable Declarations
	
	//PINS

		//Input Pins
			const int frontSonicInputPin =  //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE

		//Output Pins 
			const int frontSonicTriggerPin = //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE

			const int leftMotorPin = //LEFT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
			const int rightMotorPin = //RIGHT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
	//GENERAL

		long frontReading;

void setup() {
	Serial.begin(9600);
	loadPins();
}

void loop() {
	frontReading = getSonicDistance(frontSonicInputPin, frontSonicTriggerPin);

	Serial.print("Front: ");
	Serial.print(frontReading);

	if(frontReading > 50){
		//go forward
		analogWrite(leftMotorPin, 100);
		analogWrite(rightMotorPin, 100);
	} else {
		analogWrite(leftMotorPin, 50);
	}

}



void loadPins(){
	//Input Pins
	pinMode(frontSonicInputPin, INPUT);

	//Output Pins
	pinMode(frontSonicTriggerPin, OUTPUT);
	pinMode(leftMotorPin, OUTPUT);
	pinMode(rightMotorPin, OUTPUT);
}

long getSonicDistance(int echoPin, int triggerPin){
	long distanceCM = 0;
	digitalWrite(triggerPin,HIGH);
	delayMicroseconds(300);
	digitalWrite(triggerPin,LOW);
	long duration = pulseIn(echoPin, HIGH,30000);
	long distance = (duration*34029L)/2000000L;
	distanceCM = distance;
	if(distanceCM == 0){
		distanceCM = 400;
	}   
	return (double)distanceCM; 
}

