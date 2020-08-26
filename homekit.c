#include <homekit/homekit.h>
#include <homekit/characteristics.h>

#include "config.h"
#include "homekit.h"

CALLBACKS callbacks;

homekit_value_t switch1_on_get();
void switch1_on_set(homekit_value_t value);
homekit_value_t switch2_on_get();
void switch2_on_set(homekit_value_t value);
homekit_value_t switch3_on_get();
void switch3_on_set(homekit_value_t value);
homekit_value_t switch4_on_get();
void switch4_on_set(homekit_value_t value);
void identify(homekit_value_t _value);

homekit_characteristic_t cha_switch1_on = HOMEKIT_CHARACTERISTIC_(
    ON, 
    false,
    .setter=switch1_on_set,
    .getter=switch1_on_get
);

homekit_characteristic_t cha_switch2_on = HOMEKIT_CHARACTERISTIC_(
    ON, 
    false,
    .setter=switch2_on_set,
    .getter=switch2_on_get
);

homekit_characteristic_t cha_switch3_on = HOMEKIT_CHARACTERISTIC_(
    ON, 
    false,
    .setter=switch3_on_set,
    .getter=switch3_on_get
);

homekit_characteristic_t cha_switch4_on = HOMEKIT_CHARACTERISTIC_(
    ON, 
    false,
    .setter=switch4_on_set,
    .getter=switch4_on_get
);

// format: bool; HAP section 9.70; write the .setter function to get the switch-event sent from iOS Home APP.
homekit_characteristic_t cha_switch_on = HOMEKIT_CHARACTERISTIC_(ON, false);


homekit_accessory_t *homekit_accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_sensor, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch x4"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 1"),
            &cha_switch1_on,
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 2"),
            &cha_switch2_on,
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 3"),
            &cha_switch3_on,
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 4"),
            &cha_switch4_on,
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t homekit_server_config = {
    .accessories = homekit_accessories,
    .password = HOMEKIT_PASSWORD
};

homekit_value_t switch1_on_get(){
    cha_switch1_on.value.bool_value = callbacks.switch_on_get(1);
    return cha_switch1_on.value;
}

void switch1_on_set(homekit_value_t value){
    callbacks.switch_on_set(1, value.bool_value);
}

homekit_value_t switch2_on_get(){
    cha_switch2_on.value.bool_value = callbacks.switch_on_get(2);
    return cha_switch2_on.value;
}

void switch2_on_set(homekit_value_t value){
    callbacks.switch_on_set(2, value.bool_value);
}

homekit_value_t switch3_on_get(){
    cha_switch3_on.value.bool_value = callbacks.switch_on_get(3);
    return cha_switch3_on.value;
}

void switch3_on_set(homekit_value_t value){
    callbacks.switch_on_set(3, value.bool_value);
}

homekit_value_t switch4_on_get(){
    cha_switch4_on.value.bool_value = callbacks.switch_on_get(4);
    return cha_switch4_on.value;
}

void switch4_on_set(homekit_value_t value){
    callbacks.switch_on_set(4, value.bool_value);
}

void identify(homekit_value_t _value) {
    // nothing to do
}
  
void init_homekit(bool (*switch_on_get)(uint8_t id),
                  void (*switch_on_set)(uint8_t id, bool value)) {
                    
    callbacks.switch_on_get = switch_on_get;
    callbacks.switch_on_set = switch_on_set;

    arduino_homekit_setup(&homekit_server_config);
}
