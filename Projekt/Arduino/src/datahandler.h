#pragma once
#include <ESP8266WiFi.h>

typedef struct header {

    size_t size;
    char type;

} Header;

typedef struct payload { } Payload;

void handle_incoming_packet(WiFiClient client);
void read_packet(WiFiClient client);