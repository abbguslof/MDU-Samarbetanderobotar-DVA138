#include "datahandler.h"

#define SDP 'a'

uint8_t controls[1];

void handle_incoming_packet(WiFiClient client)
{

    while (client.connected())
    {
        if (client.available())
        {
            client.read(controls, 1);

            if (controls[0] != SDP)
            {
                Serial.println("ERROR | Unkown Packet");
                while (client.available() > 0)
                    client.flush();

                continue;
            } 

            read_packet(client);
        }
    }
}

void read_packet(WiFiClient client) {
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }
    Serial.println("");
}
