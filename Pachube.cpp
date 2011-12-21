#include "Arduino.h"
#include "SPI.h"
#include "Ethernet.h"
#include "Pachube.h"

byte *mac;
char *apiKey;

PachubeClient::PachubeClient(byte *macAddress[], char *apiKey[], int feedId)
{
  _macAddress = macAddress;
  _apiKey = apiKey;
  _feedId = feedId;
}

PachubeClient::open()
{
  Serial.begin(9600);

  if (Ethernet.begin(_macAddress) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");

    throw;
}

PachubeClient::sendToFeed(int dataToSend)
{
  if (_client.connect("api.pachube.com", 80)) {
    Serial.println("Connecting to Pachube...");

    client.print("PUT /v2/"+_feedId+".csv HTTP/1.1\n");
    client.print("Host: www.pachube.com\n");

    client.print("X-PachubeApiKey: "+_apiKey+"\n");
    client.print("Content-Length: ");

    int lengthOfData = getLength(dataToSend);

    client.print("Content-Type: text/csv\n");
    client.println("Connection: close\n");

    client.println(dataToSend, DEC);
  }
  else {
    Serial.println("Connection failed.");
  }
}

int getLength(int someValue) {
  //there's at least one byte:
  int digits = 1;

  // continually divide the value by ten, 
  // adding one to the digit count for each
  // time you divide, until you're at 0:
  int dividend = someValue /10;

  while (dividend > 0) {
    dividend = dividend /10;
    digits++;
  }
  // return the number of digits:
  return digits;
}

PachubeClient::readFromFeed()
{

}

PachubeClient::~PachubeClient()
{
  // Close the socket
  _client.close();
}
