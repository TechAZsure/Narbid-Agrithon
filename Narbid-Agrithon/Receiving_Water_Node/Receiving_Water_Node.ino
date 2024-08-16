#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  pinMode(5, OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(SensorData));

    Serial.print("Temperature: ");
    Serial.println(data.temperature);
    Serial.print("Humidity: ");
    Serial.println(data.humidity);
    Serial.print("Soil Moisture: ");
    Serial.println(data.soilMoisture);
    Serial.print("NPK Value: ");
    Serial.println(data.npkValue);
    Serial.print("pH Value: ");
    Serial.println(data.phValue);
    Serial.print("Water Level: ");
    Serial.println(data.waterLevel);

    if (data.soilMoisture < 300) { 
      digitalWrite(5,HIGH);
    }

    if (data.npkValue < 500) { 
      digitalWrite(4, HIGH));
    }

    radio.stopListening();
    radio.write(&data, sizeof(SensorData));
    radio.startListening();
  }
}
