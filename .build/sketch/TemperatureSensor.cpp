#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const uint8_t pinTrigger, const uint8_t readPin)
	: readPin(readPin), triggerPin(pinTrigger)
{
	pinMode(triggerPin, OUTPUT);
	pinMode(readPin, INPUT);
	digitalWrite(triggerPin, HIGH);
}

const uint8_t TemperatureSensor::readCelsius()
{
	//getting the voltage reading from the temperature sensor
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(200);
	int reading = analogRead(readPin);
	digitalWrite(triggerPin, LOW);
	// converting that reading to voltage, for 3.3v arduino use 3.3
	double voltage = reading * 5.0; // * 0.0009775171;
	voltage /= 1024.0;
	return round((voltage - 0.5) * 100);

	return (voltage - 0.5) * 100; //converting from 10 mv per degree wit 500 mV offset
}