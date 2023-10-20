#include "datahandler.h"

uint8_t controls[1];

void handle_incoming_packet(WiFiClient client)
{
    if (client.connected()) {
        Serial.println("[+] New connection");
        handshake(client);
    }

    char check = client.connected();

    while (check)
    {
        if (client.available())
        {
            client.read(controls, 1);

            if (controls[0] != __SDP)
            {
                Serial.println("ERROR | Unkown Packet");
                while (client.available() > 0)
                    client.flush();

                continue;
            } 

            read_packet(client);
        }
        if (!(check = client.connected())) {
            Serial.println("[-] Connection closed");
        }
    }
}

void write_packet(WiFiClient client, char type, void * data, size_t size) {
    Payload payload;
    payload.header.type = __SDP;
    payload.header.type = type;
    payload.header.dataOffset = (long)&payload.data - (long)&payload;
    memcpy(&payload.data, data, size);
    client.write((uint8_t *)&payload, sizeof(Payload));
    Serial.printf("%ld\n", ((long)&payload.data) - ((long)&payload));
}

void read_packet(WiFiClient client) {
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }
    Serial.println("");
}

void handshake(WiFiClient client) {
    Example data;
    data.a = 3.14;
    data.b = 2;
    write_packet(client, 0, (void*) &data, sizeof(data));
    Serial.println("Handshake completed");
}
