#ifndef Pachube_h
#define Pachube_h

#include <Ethernet.h>
#include "Arduino.h"

class PachubeClient 
{
  public:
    PachubeClient(char apiKey[]);
    bool connectWithMac(byte macAddress[]);
    bool connectWithIP(byte macAddress[], IPAddress localIP);
    bool connectViaGateway(byte macAddress[], IPAddress localIP, IPAddress dnsServerIP, IPAddress gatewayIP, IPAddress subnet);
		void updateFeed(uint16_t feedId, uint16_t datastreamId, uint16_t dataToSend);
    char * getFeed(uint16_t);
		void readFromFeed();
    bool closeConnection();
    int getLength(int data);
	private:
		void sendData(uint16_t feedId, uint16_t datastreamId, uint16_t dataToSend);
};

#endif
