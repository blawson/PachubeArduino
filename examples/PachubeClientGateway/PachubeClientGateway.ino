#include <SPI.h>
#include <Ethernet.h>
#include <Pachube.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x10, 0x8f};
char apiKey[] = "YOUR_API_KEY";
int feedId = 41549;
int datastreamId = 1;
IPAddress localIP(192,168,2,100);
IPAddress dnsServerIP(192,168,60,65); // Your DNS server IP - xxx,xxx,xxx,xxx
IPAddress gatewayIP(192,168,60,65); // Your gateway IP
IPAddress subnet(255,255,255,0);

PachubeClient client = PachubeClient(apiKey);

void setup()
{
    client.connectViaGateway(mac, localIP, dnsServerIP, gatewayIP, subnet);
}

void loop()
{
    // read the sensor
    int sensorReading = analogRead(A0);
        
    // send to the Pachube client
    client.updateFeed(feedId, datastreamId, sensorReading);
}
