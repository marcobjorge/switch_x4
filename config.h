#pragma once

// DEBUG
#define DEBUG_LEVEL DBG_NONE
#define DEBUG_PORT 115200

// HOMEKIT
#define HOMEKIT_PASSWORD "111-11-111"
#define HOMEKIT_REPORT_PERIOD_MS 5000

// CONTROLLER
#define ACTUATOR_COUNT_MAX 4
#define ACTUATOR1_PIN D1
#define ACTUATOR2_PIN D2
#define ACTUATOR3_PIN D5
#define ACTUATOR4_PIN D7

// use this to disable some actuators if they are not used
#define ACTUATOR_COUNT_ACTUAL 2
