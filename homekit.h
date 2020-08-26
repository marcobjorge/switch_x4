#pragma once

typedef struct _callbacks {
    bool (*switch_on_get)(uint8_t id);
    void (*switch_on_set)(uint8_t id, bool value);
} CALLBACKS;

void init_homekit(bool (*switch_on_get)(uint8_t id),
                  void (*switch_on_set)(uint8_t id, bool value));
