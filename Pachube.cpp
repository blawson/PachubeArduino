extern "C" {
  #include "stdio.h"
}

#include "Arduino.h"
#include <Ethernet.h>
#include "Pachube.h"

char *_api;
long _lastConnMillis = 0;
bool lastConnected = false;
const int _interval = 10000;
EthernetClient _client;
char *_host = "api.pachube.com";
const int _port = 80;

PachubeClient::PachubeClient(char apiKey[])
{
  _api= apiKey;
}

bool PachubeClient::connectWithMac(byte macAddress[])
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

bool PachubeClient::connectWithIP(byte macAddress[], IPAddress localIP)
{
  Serial.begin(9600);

  Ethernet.begin(macAddress, localIP);

  if (_client.connect(_host, _port)) {
    return true;
  }
  else {
    Ethernet.begin(macAddress, localIP);
    return (_client.connect(_host, _port));
  }
}

bool PachubeClient::connectViaGateway(byte macAddress[], IPAddress localIP, IPAddress dnsServerIP, IPAddress gatewayIP, IPAddress subnet)
{
  Serial.begin(9600);

  Ethernet.begin(macAddress, localIP, dnsServerIP, gatewayIP, subnet);

  if (_client.connect(_host, _port)) {
    return true;
  }
  else {
    Ethernet.begin(macAddress, localIP, dnsServerIP, gatewayIP, subnet);
    return (_client.connect(_host, _port));
  }
}

void PachubeClient::updateFeed(uint32_t feedId, char datastreamId[], double dataToSend) {
  if (_client.available()) {
    char c = _client.read();
    Serial.print(c);
  }

  if (!_client.connected() && lastConnected) {
    Serial.println("disconnecting.\n");
    _client.stop();
  }

  if (!_client.connected() && (millis() - _lastConnMillis > _interval)) {
    sendData(feedId, datastreamId, dataToSend);
    _lastConnMillis = millis();
  }

  lastConnected = _client.connected();
}

char * PachubeClient::getFeed(uint32_t feedId) {
  int maxSize = 50;
  char response[maxSize];

  for(int i=0; i<sizeof(response); i++) {
    if (!_client.available()) {
      return response;
    }
    char c = _client.read();
  }
}

void PachubeClient::sendData(uint32_t feedId, char datastreamId[], double dataToSend)
{
  if (_client.connect("api.pachube.com", 80)) {
    Serial.println("Connecting to Pachube...");

    _client.print("PUT /v2/feeds/");
    _client.print(feedId);
    _client.print("/datastreams/");
    _client.print(datastreamId);
    _client.print(".csv HTTP/1.1\n");
    _client.print("Host: api.pachube.com\n");

    _client.print("X-PachubeApiKey: ");
    _client.print(_api);
    _client.print("\n");
    _client.print("Content-Length: ");

    int lengthOfData = getLength(dataToSend);
    _client.println(lengthOfData, DEC);

    _client.print("Content-Type: text/csv\n");
    _client.println("Connection: close\n");

    _client.print(dataToSend, DEC);
  }
}

int PachubeClient::getLength(double someValue) {
  // max of 64 characters
  char buffer [64];
  
  int length = sprintf(buffer, "%f.5", someValue);

  if (someValue < 0) {
    // added for the '-' symbol
    length = length+1;
  }

  return length+1;
}

void PachubeClient::readFromFeed()
{
}


