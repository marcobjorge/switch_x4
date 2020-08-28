#pragma once

typedef struct _callbacks {
    bool (*switch_on_get)(uint8_t id);
    void (*switch_on_set)(uint8_t id, bool value);
} CALLBACKS;

void init_homekit(bool (*switch_on_get)(uint8_t id),
                  void (*switch_on_set)(uint8_t id, bool value));
void switch1_on_update(bool value);
void switch2_on_update(bool value);
void switch3_on_update(bool value);
void switch4_on_update(bool value);
