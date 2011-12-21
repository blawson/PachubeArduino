#ifndef Pachube_h
#define Pachube_h

#include <Ethernet.h>
#include "Arduino.h"
#include "Time.h"

class PachubeClient 
{
  public:
    PachubeClient(byte macAddress[], char apiKey[], int feedId, int datastreamId);
    bool openConnection();
		void updateFeed(int dataToSend);
		void readFromFeed();
    bool closeConnection();
    int getLength(int data);
	private:
		void sendData(int dataToSend);
		byte *_macAddress[];
    char *_apiKey[];
    int _feedId;
};

#endif
