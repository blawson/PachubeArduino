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
		void updateFeed(uint32_t feedId, char datastreamId[], double dataToSend);
    char * getFeed(uint32_t);
		void readFromFeed();
    bool closeConnection();
    int getLength(double data);
	private:
		void sendData(uint32_t feedId, char datastreamId[], double dataToSend);
};

#endif
