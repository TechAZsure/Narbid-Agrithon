#include <DHT.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define DHTPIN 2      
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_MOISTURE_PIN A0  
#define NPK_SENSOR_PIN A1      
#define PH_SENSOR_PIN A2      
#define WATER_LEVEL_PIN A3    


#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

struct SensorData {
  float temperature;
  float humidity;
  int soilMoisture;
  int npkValue;
  int phValue;
  int waterLevel;
};

SensorData data;

void setup() {
  Serial.begin(9600);
  dht.begin();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();
  data.soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  data.npkValue = analogRead(NPK_SENSOR_PIN);
  data.phValue = analogRead(PH_SENSOR_PIN);
  data.waterLevel = analogRead(WATER_LEVEL_PIN);

  radio.write(&data, sizeof(SensorData));

  delay(2000); 
}
