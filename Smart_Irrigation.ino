#define BLYNK_TEMPLATE_ID "XXX-XXX-XXX"
#define BLYNK_DEVICE_NAME "XXX-XXX-XXX"


#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

int sensor_raw_data;
int mapped_data;
int pump;
int flag = 0;

SoftwareSerial esdata(3,4);
#define auth "XXX-XXX-XXX"
#define ssid "XXX-XXX-XXX"
#define pass "XXX-XXX-XXX"
BlynkTimer timer;

ESP8266 wifi(&esdata);

void myTimerEvent() {
  //Read Soil Moisture Value From Sensor
  sensor_raw_data = analogRead(A0);

  //Map values to desired range
  mapped_data=map(sensor_raw_data, 0, 1023, 100, 0);
  delay(2000);
  String sensor_value = String(mapped_data);
  Serial.print("Sensor Data: ");
  Serial.println(mapped_data);
  delay(2000);

  //Print the value to the Gauge on the Mobile Application
  Blynk.virtualWrite(V5, mapped_data);

  //Notify the user on whether to turn on/off the water pump based on the Soil Moisture Level
  if(mapped_data < 10 && flag == 0) {
    flag = 1;
    Blynk.logEvent("moisture_level_of_soil", "Soil Moisture Is Below 10%. Turn On Water Pump.");
    } else if(mapped_data >= 10 && flag == 1) {
      flag = 0;
      Blynk.logEvent("moisture_level_of_soil", "Soil Moisture Is Above 10%. Turn Off Water Pump.");
    }
}

// Enable the button to turn on/off the water pump
BLYNK_WRITE(V8) {
  int pinValue = param.asInt();
  if(pinValue == 1) {
    digitalWrite(8, HIGH);
    pump = 100;
    } else {
      digitalWrite(8, LOW);
    pump = 0;
   }
}

void setup() {
  Serial.begin(9600);
  esdata.begin(9600);
  Blynk.begin(auth, wifi, ssid, pass);
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);

  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
    Blynk.run();
    timer.run();
}