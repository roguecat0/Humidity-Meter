#include <DHT_U.h>
#include <DHT.h>

#define Type DHT11
int sensePin = 2;
DHT HT(sensePin, Type);
float humidity;
float tempC;
float tempF;
int setTime = 500;

// warning humidityes
float greenRange[2] = {35, 60};
float orangeRange[2] = {30, 70};

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  HT.begin();
  delay(setTime);
}
void loop()
{
  humidity = HT.readHumidity();
  tempC = HT.readTemperature(false);
  tempF = HT.readTemperature(true);
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(", Humidity: ");
  Serial.println(humidity);
  delay(1000);
}
