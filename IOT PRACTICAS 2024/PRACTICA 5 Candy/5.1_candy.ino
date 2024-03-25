#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "IoT";
const char* pass = "1t3s0IoT23";
WiFiClient client;

unsigned long myChannelNumber = 2481160;
const char* myWriteAPIKey = "KFYG4Q8I00E4ZRAL";

int number1 = random(0, 50);
int number2 = random(0, 50);
String myStatus = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  Serial.println();
  Serial.print("Wait for WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);

  if (number1 > number2) {
    myStatus = "field1 is greater than field2";
  } else if (number1 < number2) {
    myStatus = "field1 is less than field2";
  } else {
    myStatus = "field1 equals field2";
  }

  ThingSpeak.setStatus(myStatus);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.print("Response code: ");
  Serial.println(x);

  if (x == 200) {
    Serial.println("ThingSpeak Channel update successful.");
  } else {
    Serial.println("Problem updating channel.");
  }

  number1++;
  if (number1 > 99) {
    number1 = 0;
  }
  number2 = random(0, 100);

  delay(20000); // Wait 20 seconds to update the channel again
}
