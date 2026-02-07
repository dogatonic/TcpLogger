# TcpLogger

Lightweight TCP logger for ESP32 using Arduino + PlatformIO.

Created with GPT 5.2 in February 2026.

## Why?

I am switching my Arduino projects over to EP32 and also to OTA updating. So I won't be able to use the beloved serial port for my debugging. In comes TCP logging. I can now use a printf style line printer that outputs over TCP. All I have to do is open a listener in a Terminal tab, and I can view the output.

With GPT's help, I have used code that avoids some pitfalls of earlier attempts at TCP logging. 

### Why this logger is better

- **No heap churn**
- **No temporary objects**
- **Safe to run for days/weeks**
- **Cleaner call site**

"You’ve basically just upgraded from “Arduino-style logging” to **embedded-grade logging**." - GPT

### Features:

- printf-style logging (`Loggerf`)
- zero heap allocation
- single TCP client
- safe for long runtimes

## Usage

```cpp
#include "TcpLogger.h"

void setup() {
  // connect WiFi first
  LoggerBegin(23);
}

void loop() {
  LoggerHandleClient();
  Loggerf("uptime=%lu", (unsigned long)millis());
}
