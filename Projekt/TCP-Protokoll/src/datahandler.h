#pragma once
#include <ESP8266WiFi.h>

typedef struct header {

    size_t size;
    char type;

} Header;

typedef struct payload { } Payload;

int handle_incoming_packet(WiFiClient client);