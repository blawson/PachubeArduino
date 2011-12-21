#include "Arduino.h"
#include <Ethernet.h>
#include "Pachube.h"
#include "Time.h"

char *_api;
uint16_t _feed;
uint16_t _datastream;
long _lastConnMillis = 0;
bool lastConnected = false;
const int _interval = 10000;
EthernetClient _client;

PachubeClient::PachubeClient( char apiKey[], int feedId, int datastreamId)
{
  _api= apiKey;
  _feed = feedId;
  _datastream = datastreamId;
}

bool PachubeClient::openConnectionFromMac(byte macAddress[])
{
  Serial.begin(9600);

  if (Ethernet.begin(macAddress) == 0) {
    delay(1000);

    if (Ethernet.begin(macAddress) == 0) {
      Serial.println("Failed to configure Ethernet");
      return false;
    }
  }
  return true;
}

void PachubeClient::updateFeed(int dataToSend) {
  if (_client.available()) {
    char c = _client.read();
    Serial.print(c);
  }

  if (!_client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    _client.stop();
  }

  if (!_client.connected() && (millis() - _lastConnMillis > _interval)) {
    sendData(dataToSend);
    _lastConnMillis = millis();
  }

  lastConnected = _client.connected();
}

void PachubeClient::sendData(int dataToSend)
{
  if (_client.connect("api.pachube.com", 80)) {
    Serial.println("Connecting to Pachube...");

    _client.print("PUT /v2/feeds/");
    _client.print(_feed);
    _client.print("/datastreams/");
    _client.print(_datastream);
    _client.print(".csv HTTP/1.1\n");
    _client.print("Host: api.pachube.com\n");

    _client.print("X-PachubeApiKey: ");
    _client.print(_api);
    _client.print("\n");
    _client.print("Content-Length: ");

    int lengthOfData = getLength(dataToSend);
    time_t _time = now();
    _client.println(lengthOfData, DEC);

    _client.print("Content-Type: text/csv\n");
    _client.println("Connection: close\n");

    Serial.println(_time);

    _client.print(dataToSend, DEC);
    _client.print(",");
    _client.println(year(_time));
    _client.print("-");
    _client.print(month(_time));
    _client.print("-");
    _client.print(day(_time));
    _client.print("T");
    _client.print(hour(_time));
    _client.print(":");
    _client.print(minute(_time));
    _client.print(":");
    _client.print(second(_time));
    _client.print("Z");
  }
}

int PachubeClient::getLength(int someValue) {
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

void PachubeClient::readFromFeed()
{

}

