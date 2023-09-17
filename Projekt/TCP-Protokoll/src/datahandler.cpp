#include "datahandler.h"

#define SDP '\1'

uint8_t controlls[1];

int handle_incoming_packet(WiFiClient client)
{

    while (client.connected())
    {
        while (client.available() > 0)
        {
            client.read(controlls, 1);

            if (controlls[0] != SDP)
            {
                Serial.println("ERROR | Unkown Packet");

                while (client.available() > 0)
                    client.flush();
                break;
            }
        }
    }

    return 0;
}