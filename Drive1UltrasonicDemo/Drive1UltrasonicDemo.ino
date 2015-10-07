//Packages
#include <Arduino.h>

//Global Variable Declarations
	
	//PINS

		//Input Pins
			const int frontSonicInputPin = 31;//PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S ECHO HERE

		//Output Pins 
			const int frontSonicTriggerPin = 30;//PUT THE NUMBER OF THE PIN THAT IS CONNECTED TO THE SENSOR'S TRIGGER HERE

			const int leftMotorPin = 3;//LEFT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
			const int rightMotorPin = 2;//RIGHT MOTOR PIN HERE ---> NEEDS TO BE BETWEEN 2-13
	//GENERAL

		long frontReading;

void setup() {
	Serial.begin(9600);
	loadPins();
}

void loop() {
	frontReading = getSonicDistance(frontSonicInputPin, frontSonicTriggerPin);

	Serial.print("Front: ");
	Serial.println(frontReading);

	if(frontReading > 50){
		//go forward
		analogWrite(leftMotorPin, 255);
		analogWrite(rightMotorPin, 255);
	} else {
		analogWrite(leftMotorPin, 200);
    analogWrite(rightMotorPin, 1);
	}

  delay(300);

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
	long duration = pulseIn(echoPin, HIGH,38000);
	long distance = (duration*34029L)/2000000L;
	distanceCM = distance;
	if(distanceCM == 0){
		distanceCM = 400;
	}   
	return (double)distanceCM; 
}

