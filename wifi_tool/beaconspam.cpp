#include "Arduino.h"
#include "beaconspam.h"
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

BeaconSpammer::BeaconSpammer() {

	this->packet_size = sizeof(this->beacon_packet);

  this->ssid_length = 0;
  this->ap_count = 0;
  this->state = false;

	wifi_set_opmode(STATIONAP_MODE);
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
}

void BeaconSpammer::toggle_state() {
  //set state - toggle
  this->state = !this->state;
  Serial.println((this->state ? "[+] Toggled Spammer ON." : "[+] Toggled Spammer OFF."));
} 

bool BeaconSpammer::get_state() {
  //get state
  return this->state;
}

void BeaconSpammer::build_packet(uint8_t counter) {
  // important copying
  uint8_t ssid_copy[32] = {0};
  memcpy(ssid_copy, this->ssid, 32);

  // SRC ADDR and BSSID - random
  for (int i = 10; i <= 15; ++i) {
    this->beacon_packet[i] = this->beacon_packet[i + 6] = random(256);                     
  }
  // add space
  for(int i = 0; i < counter; ++i) {
    ssid_copy[i + this->ssid_length] = 0x20;
  }
  //copying ssid
  memcpy(this->beacon_packet + 38, ssid_copy, 32);
  
}
//arming method - settings
void BeaconSpammer::arm(String ssid, uint8_t ssid_length, uint8_t ap_count) {
  this->ap_count = ap_count;

  this->ssid_length = ssid_length;
  for(int i = 0; i < this->ssid_length; i++) {
    this->ssid[i] = ssid[i];
  }
}
//main part of class
void BeaconSpammer::main() {
  if (!this->state) return;

  for (int counter = 1; counter <= this->ap_count; counter++) {
    	this->build_packet(counter);
	    wifi_send_pkt_freedom(this->beacon_packet, this->packet_size, 1);
      delay(10);
	    wifi_send_pkt_freedom(this->beacon_packet, this->packet_size, 1);
	    delay(10);
      wifi_send_pkt_freedom(this->beacon_packet, this->packet_size, 1);
      delay(10);
      Serial.println(". ");
  }
}  