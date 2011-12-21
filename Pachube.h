#ifndef Pachube_h
#define Pachube_h

#include <Ethernet.h>
#include "Arduino.h"

class PachubeClient 
{
  public:
    PachubeClient(char apiKey[], int feedId, int datastreamId);
    bool connectWithMac(byte macAddress[]);
		void updateFeed(int dataToSend);
		void readFromFeed();
    bool closeConnection();
    int getLength(int data);
	private:
		void sendData(int dataToSend);
};

#endif
