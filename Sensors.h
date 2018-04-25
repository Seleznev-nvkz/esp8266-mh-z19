#define DHT_PIN 14  // D5
#define MH_Z19_RX 13 // D7
#define MH_Z19_TX 12 // D6
#define DHT_VERSION DHT22

#include <SoftwareSerial.h>
#include <DHT.h>

class Sensors {
	public:
		Sensors();
		float get_temp();
		float get_hum();
		int get_co2();

	private:
		const byte co2_cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
		DHT *dht;
		SoftwareSerial *co2;
};