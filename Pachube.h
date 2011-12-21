#ifndef Pachube_h
#define Pachube_h

#include "Arduino.h"
#include "Ethernet.h"
#include "Time/Time.h"

class PachubeClient 
{
  public:
    PachubeClient(byte macAddress[], char apiKey[], int feedId, int datastreamId);
    ~PachubeClient();
    bool openConnection();
		void updateFeed(int dataToSend);
		void sendData(int dataToSend);
		void readFromFeed();
    bool closeConnection();
    int getLength(int data);
	private:
		byte *_macAddress[];
    char *_apiKey[];
    int _feedId;
    EthernetClient _client;
};

#endif
