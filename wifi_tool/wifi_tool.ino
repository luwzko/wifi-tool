#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// mods
#include "beaconspam.h"
#include "scanner.h"
#include "deauther.h"
// HTML page
#include "pages.h"

extern "C" {
  #include "user_interface.h"
}
 
#define SSID "tool"
#define PWD  "tool1234"

ESP8266WebServer server(80);
// modules
BeaconSpammer spammer;  
Scanner scanner;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  // disable software watchdog timer
  ESP.wdtDisable();
  
  if(WiFi.softAP(SSID, PWD)) {
    Serial.println("\n\nWebServer was created successfully!");
  } else {
    Serial.println("WebServer was not created successfully!");
  }
  // root page
  server.on("/", []() {
    server.send(200, "text/html", root_page); 
  });
  // Arm/setup spammer
  server.on("/spammer/arm", handleArmingSpammer);
  // Toggle Spammer [ON/OFF]
  server.on("/spammer/toggle", []() {
    spammer.toggle_state();
    server.sendHeader("Location", String("/"), true);
    server.send(302, "text/plain", "");
  });
  // Start scanner
  server.on("/scanner/start", []() {
    scanner.scan();
    server.sendHeader("Location", String("/"), true);
    server.send(302, "text/plain", "");
  });
  // GET html table of scanning results
  server.on("/scanner/results", []() {
    server.send(200, "text/plain", scanner.get_html());
  });

  server.begin();
}

void loop() {

  server.handleClient();

  spammer.main();
  scanner.main();
}

void handleArmingSpammer() { // handle for Spammer
  String ssid;
  uint8_t len = 0;
  uint8_t ap_count = 0;

  ssid.reserve(128);
  
  for(int i = 0; i < server.args(); ++i) {
    if (server.argName(i) == "ssid") {
      ssid = server.arg(i);
      len = ssid.length();
    }
    else if (server.argName(i) == "ap_count") {
      ap_count = server.arg(i).toInt();
    }
  }
  Serial.print("[+] Arming Beacon Spammer with ssid=");
  Serial.print(ssid);
  Serial.print(" with len=");
  Serial.print(len);
  Serial.print(" and ap_count=");
  Serial.println(ap_count);

  spammer.arm(ssid, len, ap_count);

  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}