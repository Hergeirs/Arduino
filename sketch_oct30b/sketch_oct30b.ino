#include "TemperatureSensor.h"
#include "SoilMoistureSensor.h"

#define moisture_input A0
#define divider_top 13
#define divider_bottom 12
SoilMoistureSensor soilReader(divider_top, divider_bottom, moisture_input);
TemperatureSensor tempReader(8, A1);

void setup()
{
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	delay(1000);
	Serial.begin(9600);
}

void loop(void)
{
	digitalWrite(4, LOW);
	delay(1000);

	while (Serial.available() == 0)
	{
		delay(1000);
	}
	static char a;
	while (Serial.available() && (a = Serial.read()))
		;
	const unsigned moisture = soilReader.readPercent();

	digitalWrite(4, HIGH);
	// Serial.print("Soil moisture: ");
	Serial.println(moisture);
	// Serial.print("temperature C: ");
	Serial.println(tempReader.readCelsius());
	delay(1000);
}

// 	//Read button state (pressed or not pressed?)
// 	const unsigned buttonState = digitalRead(buttonPin);

// 	//If button pressed...
// 	if (buttonState == LOW && lastState != buttonState) {

// 		delay(1000);
// 	}
// 	lastState = buttonState;

// toggles 0 to 1
void toggle(unsigned pinNumber)
{
	digitalWrite(pinNumber, !digitalRead(pinNumber));
}
void circularInc(unsigned &pinNum, const int min, const int max, const int inc = 1)
{
	pinNum = (pinNum - min + inc) % (max - min + 1) + min;
}