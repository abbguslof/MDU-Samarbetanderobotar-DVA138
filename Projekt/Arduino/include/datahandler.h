#pragma once
#include <ESP8266WiFi.h>
#include "types.h"

#define __SDP '\3'

typedef struct header {
    char SDP = __SDP;
    char type;
    char dataOffset;

} Header;

typedef struct payload { 
    Header header;
    union datatypes {
        Example example;
    } data;
} Payload;

void handle_incoming_packet(WiFiClient client);
void read_packet(WiFiClient client);
void handshake(WiFiClient client);
