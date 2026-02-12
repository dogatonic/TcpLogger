#include "TcpLogger.h"

/*
 * File: TcpLogger.cpp
 * Author: Tucker & GPT-5.2
 * Date: 2026-02-06
 *
 * Description:
 *   Simple TCP logger for ESP32/Arduino. Provides functions to start a
 *   WiFi server, accept a single logging client, and send formatted
 *   log messages over TCP. Main APIs:
 *     - LoggerBegin(port): start server on given port
 *     - LoggerEnabled(): check client connection
 *     - LoggerHandleClient(): accept/manage client connections
 *     - Loggerf(fmt, ...): printf-like logging to the connected client
 */

static WiFiServer logServer(23);
static WiFiClient logClient;

void LoggerBegin(uint16_t port){
	static bool started = false;
	if (started) return;
	started = true;

	// "first call wins" — config port once
	logServer = WiFiServer(port);
	logServer.begin();
	logServer.setNoDelay(true);
}

bool LoggerEnabled(){
	return logClient && logClient.connected();
}

void LoggerHandleClient(){
	if (!logClient || !logClient.connected()){
		if (logClient)
			logClient.stop();
		logClient = logServer.available();
		if (logClient){
			logClient.println("Connected to TCP logger");
			logClient.println(WiFi.localIP());
		}
	}
}

// this is a "take" on printf; it formats (fmt!) a string and sends it to the log client
void Loggerf(const char *fmt, ...){
	if (!LoggerEnabled())
		return;

	char buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	logClient.println(buf);
}
