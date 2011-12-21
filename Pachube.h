#ifndef Pachube_h
#define Pachube_h

#include <Ethernet.h>
#include "Arduino.h"

class PachubeClient 
{
  public:
    PachubeClient(char apiKey[]);
    bool connectWithMac(byte macAddress[]);
		void updateFeed(uint16_t feedId, uint16_t datastreamId, uint16_t dataToSend);
		void readFromFeed();
    bool closeConnection();
    int getLength(int data);
	private:
		void sendData(uint16_t feedId, uint16_t datastreamId, uint16_t dataToSend);
};

#endif
