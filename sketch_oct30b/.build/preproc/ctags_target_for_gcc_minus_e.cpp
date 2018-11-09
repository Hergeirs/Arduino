# 1 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
# 1 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino"
# 2 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino" 2
# 3 "c:\\Users\\herge\\Documents\\Arduino\\sketch_oct30b\\sketch_oct30b.ino" 2




SoilMoistureSensor soilReader(13, 12, A0);
TemperatureSensor tempReader(8, A1);

void setup()
{
 pinMode(4, 0x1);
 digitalWrite(4, 0x1);
 delay(1000);
 Serial.begin(9600);
}

void loop(void)
{
 digitalWrite(4, 0x0);
 delay(1000);

 while (Serial.available() == 0)
 {
  delay(1000);
 }
 static char a;
 while (Serial.available() && (a = Serial.read()))
  ;
 const unsigned moisture = soilReader.readPercent();

 digitalWrite(4, 0x1);
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
