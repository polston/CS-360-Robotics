//Packages
#include <Arduino.h>

//Global Variable Declarations
	
	//PINS

		//Input Pins
			const int frontSonicInputPin =  //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE
			const int leftSonicInputPin =  //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE
			const int rightSonicInputPin =  //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE

		//Output Pins 
			const int frontSonicTriggerPin = //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE
			const int leftSonicTriggerPin = //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE
			const int rightSonicTriggerPin = //PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE

			const int leftMotorPin = //LEFT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
			const int rightMotorPin = //RIGHT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
	//GENERAL

		long frontReading;
		long leftReading;
		long rightReading;

void setup() {
	Serial.begin(9600);
	loadPins();
}

void loop() {
	frontReading = getSonicDistance(frontSonicInputPin, frontSonicTriggerPin);
	leftReading = getSonicDistance(leftSonicInputPin, leftSonicTriggerPin);
	rightReading = getSonicDistance(rightSonicInputPin, rightSonicTriggerPin);

	Serial.print("Front: ");
	Serial.print(frontReading);
	Serial.print(",\tLeft: ");
	Serial.print(leftReading);
	Serial.print(",\tRight: ");
	Serial.println(rightReading);

	if(frontReading > 50){
		//go forward
		analogWrite(leftMotorPin, 100);
		analogWrite(rightMotorPin, 100);
	} else {
		//turn whichever way has more space
		if(rightReading > leftReading){
			//turn right
			analogWrite(leftMotorPin, 50);
		} else{
			//turn left
			analogWrite(rightMotorPin, 50);
		}
	}

}



void loadPins(){
	//Input Pins
	pinMode(frontSonicInputPin, INPUT);
	pinMode(leftSonicInputPin, INPUT);
	pinMode(rightSonicInputPin, INPUT);

	//Output Pins
	pinMode(frontSonicTriggerPin, OUTPUT);
	pinMode(leftSonicTriggerPin, OUTPUT);
	pinMode(rightSonicTriggerPin, OUTPUT);
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

