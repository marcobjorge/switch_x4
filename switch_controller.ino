#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <ESP8266WiFi.h>
#include <Arduino_DebugUtils.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi.h>

extern "C" {
  #include "config.h"
  #include "homekit.h"
}

const uint8_t ACTUATOR_COUNT = 4;
const uint8_t ACTUATOR_PINS[ACTUATOR_COUNT] = {ACTUATOR1_PIN, ACTUATOR2_PIN, ACTUATOR3_PIN, ACTUATOR4_PIN};

void init_debug() {
  Serial.begin(DEBUG_PORT);
  Debug.setDebugLevel(DEBUG_LEVEL);
}

void init_wifi() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (!WiFi.isConnected()) {
    Debug.print(DBG_VERBOSE, "WiFi connecting..."); 
    delay(250);
  }
  Debug.print(DBG_VERBOSE, "WiFi connected (IP is %s)", WiFi.localIP().toString().c_str());
}

void init_actuators(){
  for(uint8_t idx=0; idx<ACTUATOR_COUNT ; idx++){
    pinMode(ACTUATOR_PINS[idx], OUTPUT);
    digitalWrite(ACTUATOR_PINS[idx], HIGH);
  }
}

void setup() {
	init_debug();
	init_wifi();
  init_actuators();
  init_homekit(&switch_on_get, &switch_on_set);
}

void loop() {
	arduino_homekit_loop();

  delay(50);
}

volatile bool switch_on[] = {false, false, false, false};

bool switch_on_get(uint8_t id){
  return switch_on[id-1];
}  

void switch_on_set(uint8_t id, bool value){
  switch_on[id-1] = !switch_on[id-1];
  Debug.print(DBG_VERBOSE, "Set actuator %d to %d", id, switch_on[id-1]); 
  if(switch_on[id-1]){
    digitalWrite(ACTUATOR_PINS[id-1], LOW);
  } else {
    digitalWrite(ACTUATOR_PINS[id-1], HIGH);
  }
}
