#ifndef scanner_h
#define scanner_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

class Scanner {
public:
  Scanner();
  void main();
  void scan();
  
  bool get_state();
  void toggle_state();
  String get_html();

private:
  String result;
  bool state;
};
#endif