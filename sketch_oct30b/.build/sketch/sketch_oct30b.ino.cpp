#include <Arduino.h>
#line 1 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
#line 1 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
#define moisture_input A0
#define divider_top 13
#define divider_bottom 12



class SoilMoistureReader {
  private:
    const byte pinUpper;
    const byte pinLower;
    const byte analogPin;

  public:
    SoilMoistureReader(const byte upperPin, const byte lowerPin, const byte pinAnalog)
    :pinUpper(upperPin), pinLower(lowerPin),analogPin(pinAnalog)
    {
      pinMode(pinUpper, OUTPUT);
      digitalWrite(pinUpper, LOW);

      pinMode(pinLower, OUTPUT);
      digitalWrite(pinLower, LOW);
      pinMode(analogPin, INPUT);
    }

    const unsigned read() {
      unsigned reading;
      // drive a current through the divider in one direction
      digitalWrite(pinUpper,LOW);
      digitalWrite(pinLower,HIGH);

      // wait a moment for capacitance effects to settle
      delay(1);

      // take a reading takes 100 microseconds to complete read.
      reading=analogRead(analogPin);

      // reverse the current
      digitalWrite(pinUpper,HIGH);
      digitalWrite(pinLower,LOW);

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

    const double readCelcius() {

      //getting the voltage reading from the temperature sensor
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(125);
      int reading = analogRead(readPin);
      digitalWrite(triggerPin, LOW);
      // converting that reading to voltage, for 3.3v arduino use 3.3
      double voltage = reading * 5.0;
      voltage /= 1024.0;

      // print out the voltage
      Serial.print(voltage); Serial.println(" volts");

      // now print out the temperature
      double temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                    //to degrees ((voltage - 500mV) times 100)
      return temperatureC;


      // digitalWrite(triggerPin, HIGH);
      // delay(1000);
      // const unsigned reading = analogRead(readPin);
      // // converting that reading to voltage, for 3.3v arduino use 3.3
      // float voltage = reading * 5.0;
      // voltage /= 1024.0;
      // // Get Temperature;
      // return (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
    }
};



SoilMoistureReader soilReader(divider_top,divider_bottom,moisture_input);
TemperatureSensor tempReader(8, A1);


#line 107 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
void setup();
#line 114 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
void loop(void);
#line 107 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
void setup () {
  // soilReader = SoilMoistureReader();
  Serial.begin(9600);
  noTone(2);
}


void loop (void) {


  const unsigned moisture=soilReader.readPercent(); // assign the result of SoilMoisture() to the global variable 'moisture'
  Serial.print("Soil moisture: ");
  Serial.print(moisture); // print the analogical measurement of the experiment
  Serial.println();

  Serial.print("temperature C: ");
  Serial.print(tempReader.readCelcius()); // print the analogical measurement of the experiment

  // later i will improve here a calculation for derive Soil Moisture in %
  Serial.println();
  delay(1000);
}


















































// // #include <boarddefs.h>
// // #include <ir_Lego_PF_BitStreamEncoder.h>
// #include <IRremote.h>
// // #include <IRremoteInt.h>

// #define MOISTURE A2
// #define TEMP A0
// #define LIGHT A1

// // #define IR 13

// // IRrecv receiver(IR);
// // decode_results results;


// void setup() {
//   //Input or output?
//   pinMode(MOISTURE,INPUT);
//   pinMode(TEMP,INPUT);
//   pinMode(LIGHT,INPUT);
//   // receiver.enableIRIn();
//   // receiver.blink13(true);
//   Serial.begin(9600);
// }




// inline float readTemperature(const byte pin = TEMP){
//  //getting the voltage reading from the temperature sensor

//   const byte reading = analogRead(pin);
//   // converting that reading to voltage, for 3.3v arduino use 3.3
//   float voltage = reading * 5.0;
//   voltage /= 1024.0;

//   // Get Temperature;
//   return (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
// }

// inline unsigned readMoisture(const byte pin = MOISTURE, const byte triggerPin = MOISTURE_TRIGGER) {
//   digitalWrite(triggerPin,HIGH);
//   const byte reading = analogRead(pin);
//   delay(500);
//   digitalWrite(triggerPin,LOW);
//   return 1023 - reading;
// }

// inline unsigned readLight(const byte pin) {
//   return analogRead(pin);
// }



// void loop() {

//   // converting that reading to voltage, for 3.3v arduino use 3.3
//   const auto temp = readTemperature(TEMP);
//   const auto moist = readMoisture(MOISTURE);
//   const auto light = readLight(LIGHT);

//   Serial.print(temp); Serial.println(" degrees C");

//   Serial.print(moist); Serial.println(" something humidity");

//   Serial.print(light); Serial.println(" something light");
//   // if (receiver.decode(&results)){
//   //         Serial.print("IR code Received: "); Serial.println(results.value, HEX);
//   //         receiver.resume();
//   // }
//   Serial.println("...");
//   delay(500);
// }






















//   // //Read button state (pressed or not pressed?)
//   // const unsigned buttonState = digitalRead(buttonPin);

//   // //If button pressed...
//   // if (buttonState == LOW && lastState != buttonState) {

//   //       delay(1000);
//   // }
//   // lastState = buttonState;
// // toggles 0 to 1
// void toggle(unsigned pinNumber) {
//   digitalWrite(pinNumber, !digitalRead(pinNumber));
// }
// void circularInc(unsigned& pinNum, const int min, const int max, const int inc = 1) {
//       pinNum = (pinNum-min+inc)%(max-min+1) + min;
// }
