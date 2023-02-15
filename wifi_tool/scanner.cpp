#include "Arduino.h"
#include <ESP8266WiFi.h>

#include "scanner.h"

extern "C" {
  #include "user_interface.h"
}

Scanner::Scanner() {
  this->result = "";
  this->state = false;
}

String Scanner::get_html() {
  return this->result;
}

void Scanner::toggle_state() {
  this->state = !this->state;
}

bool Scanner::get_state() {
  return this->state;
}

void Scanner::scan() {
  Serial.println("[+] Started Scanning...");
  this->toggle_state();

  WiFi.scanNetworks(true, true);
}
void Scanner::main() {
  if (WiFi.scanComplete() > 0 && this->state) {
      int8_t scan_state = WiFi.scanComplete();
      char buffer[160] = {0};
      this->result = "";

    	for (int8_t i = 0; i < scan_state; ++i) {
        String BSSID = WiFi.BSSIDstr(i);
        sprintf(buffer, "<tr><td>%s</td><td>%02X:%02X:%02X:%02X:%02X:%02X</td><td>%d</td><td>%d</td><td>%d</td><td>%s</td></tr>",\
        WiFi.SSID(i),

        BSSID[0],
        BSSID[1],
        BSSID[2],
        BSSID[3],
        BSSID[4],
        BSSID[5],

        WiFi.RSSI(i),
        WiFi.channel(i),
        WiFi.encryptionType(i),
        (WiFi.isHidden(i) ? "true" : "false"));

        this->result += String(buffer);
      }
      
      WiFi.scanDelete();
      this->toggle_state();
  }
}