#define moisture_input A0
#define divider_top 13
#define divider_bottom 12



class SoilMoistureReader {
	private:
		const byte upper_pin_;
		const byte lower_pin_;
		const byte analog_pin_;

	public:
		SoilMoistureReader(const byte upperPin, const byte lowerPin, const byte analogPin)
		:upper_pin_(upperPin), lower_pin_(lowerPin),analog_pin_(analogPin)
		{
			pinMode(upperPin, OUTPUT);
			digitalWrite(upperPin, LOW);

			pinMode(lowerPin, OUTPUT);
			digitalWrite(lowerPin, LOW);
			pinMode(analogPin, INPUT);
		}

		unsigned read() {
			unsigned reading;
			// drive a current through the divider
			digitalWrite(upper_pin_,LOW);
			digitalWrite(lower_pin_,HIGH);
			// wait a moment for capacitance effects to settle
			delay(1);
			// take a reading takes 100 microseconds to complete read.
			reading=analogRead(analog_pin_);

			// reverse the current
			digitalWrite(upper_pin_,HIGH);
			digitalWrite(lower_pin_,LOW);

			// give it as long time as the original current
			delayMicroseconds(1100);

			// stop the current
			digitalWrite(divider_bottom,LOW);

			return reading;
		}

		const byte readPercent() {
			return (read() / 1023.0) * 100;
		}
};

class TemperatureSensor {
	private:
		const byte triggerPin;
		const byte readPin;


	public:
		TemperatureSensor(const byte pinTrigger, const byte readPin)
		: readPin(readPin), triggerPin(pinTrigger)
		{
			pinMode(triggerPin, OUTPUT);
			pinMode(readPin, INPUT);
			digitalWrite(triggerPin, HIGH);
		}

		const double readCelsius() {

			//getting the voltage reading from the temperature sensor
			digitalWrite(triggerPin, HIGH);
			delayMicroseconds(125);
			int reading = analogRead(readPin);
			digitalWrite(triggerPin, LOW);
			// converting that reading to voltage, for 3.3v arduino use 3.3
			double voltage = reading * 5.0;
			voltage /= 1024.0;

			// now print out the temperature
			double temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
																										//to degrees ((voltage - 500mV) times 100)
			return temperatureC;
		}
};



SoilMoistureReader soilReader(divider_top,divider_bottom,moisture_input);
TemperatureSensor tempReader(8, A1);


void setup () {
	// soilReader = SoilMoistureReader();
	Serial.begin(9600);
}


void loop (void) {


	const unsigned moisture=soilReader.readPercent(); // assign the result of SoilMoisture() to the global variable 'moisture'
	Serial.print("Soil moisture: ");
	Serial.print(moisture); // print the analogical measurement of the experiment
	Serial.println();

	Serial.print("temperature C: ");
	Serial.print(tempReader.readCelsius()); // print the analogical measurement of the experiment

	// later i will improve here a calculation for derive Soil Moisture in %
	Serial.println();
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
void toggle(unsigned pinNumber) {
  digitalWrite(pinNumber, !digitalRead(pinNumber));
}
void circularInc(unsigned& pinNum, const int min, const int max, const int inc = 1) {
	  pinNum = (pinNum-min+inc)%(max-min+1) + min;
}