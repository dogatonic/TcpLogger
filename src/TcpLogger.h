#pragma once

#include <WiFi.h>
#include <stdarg.h>

void LoggerBegin(uint16_t port = 23);
void LoggerHandleClient();
bool LoggerEnabled();
void Loggerf(const char *fmt, ...);
