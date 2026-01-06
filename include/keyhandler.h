#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include "stdbool.h"

typedef struct {
    bool down[512];
    bool pressed[512];
} KeyMap;

KeyMap g_keys;

void poll_keys(void);
KeyMap* get_keymap(void);

#endif