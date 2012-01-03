#include <SPI.h>
#include <Ethernet.h>
#include <Pachube.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x10, 0x8f};
char apiKey[] = "6w2RbSZZt2JNodrpeGkCbc5RbKL9XSg1cUgxCD732vM";
int feedId = 41549;
int datastreamId = 1;

PachubeClient client = PachubeClient(apiKey);

void setup()
{
  client.connectWithMac(mac);
}

void loop()
{
  // read the sensor
  int sensorReading = analogRead(A0);
  
  // send to the Pachube client
  client.updateFeed(feedId, datastreamId, sensorReading);
}
