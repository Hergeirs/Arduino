#ifndef TEMPERATURESENSORH
#define TEMPERATURESENSORH
#include <Arduino.h>

class TemperatureSensor
{
private:
	const uint8_t triggerPin;
	const uint8_t readPin;

public:
	TemperatureSensor(const uint8_t pinTrigger, const uint8_t readPin);

	const uint8_t readCelsius();
};

#endif