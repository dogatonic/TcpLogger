#pragma once

#include <Arduino.h>
#include <stdarg.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error "Unsupported platform: expected ESP32 or ESP8266"
#endif

void LoggerBegin(uint16_t port = 23);
void LoggerHandleClient();
bool LoggerEnabled();
void Loggerf(const char *fmt, ...);
