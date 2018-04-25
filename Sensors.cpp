#include "Sensors.h"

Sensors::Sensors() {
	co2 = new SoftwareSerial(MH_Z19_RX, MH_Z19_TX);
	dht = new DHT(DHT_PIN, DHT_VERSION);
	
	dht->begin();
	co2->begin(9600);
}

float Sensors::get_temp() {
	return dht->readTemperature();
}

float Sensors::get_hum() {
	return dht->readHumidity();
}

int Sensors::get_co2() {
  byte response[9];
  co2->write(co2_cmd, 9);
  while (co2->available() > 0 && (unsigned char)co2->peek() != 0xFF) {
    co2->read();
  }

  memset(response, 0, 9);
  co2->readBytes(response, 9);

  if (response[1] != 0x86) {
    //Serial.println(response[1]);
    //Serial.println("Invalid CO2 response");
    return -1;
  }

  byte crc = 0;
  for (int i = 1; i < 8; i++) {
    crc += response[i];
  }
  crc = 255 - crc + 1;

  if (response[8] == crc) {
    int high = (int)response[2];
    int low = (int)response[3];
    int ppm = (256 * high) + low;
    return ppm;
  } else {
    //Serial.println("Broken CRC");
    return -1;
  }
}