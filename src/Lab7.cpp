/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Akash/IoTCamp2023/Lab7/src/Lab7.ino"
void setup();
void loop();
#line 1 "c:/Users/Akash/IoTCamp2023/Lab7/src/Lab7.ino"
#define BLYNK_TEMPLATE_ID "TMPL2lYCBJQ1V"
#define BLYNK_TEMPLATE_NAME "Lab7p"
#define BLYNK_AUTH_TOKEN "CK-__y-DL25k1Hxk8ZO9ua2ptkYXTKti"

#include "oled-wing-adafruit.h"
#include "blynk.h"
#define TMP36 A4
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
bool buttonPressed = false;
bool pushSent = false;
// setup() runs once, when the device is first turned on.
void setup()
{

  // Put initialization like pinMode and begin functions here.
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(TMP36, INPUT);
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.display();
  Blynk.begin(BLYNK_AUTH_TOKEN);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  Blynk.run();
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  uint64_t reading = analogRead(TMP36);
  double voltage = (reading * 3.3) / 4095.0;
  double temperatureC = (voltage - 0.5) * 100;
  double temperatureF = (temperatureC * 9 / 5) + 32;
  display.println("Celcius " + String(temperatureC, 2));
  display.println("Fahrenheit " + String(temperatureF, 2));
  display.display();
  delay(100);
  if (display.pressedA() && !pushSent) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Push Sent");
    Blynk.logEvent("notifyphone", "Hey, Blynk push here!");
    display.display();
    pushSent = true;
    delay(5000);
  }
  if (pushSent) {
    pushSent = false;
  }
}

BLYNK_WRITE(V0)
{
	Serial.println("Button Tapped");
	if (param.asInt() == 1)
	{
    Blynk.logEvent("notifyPhone", "Hey, Blynk push here!");
	}
}