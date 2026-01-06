#include "keyhandler.h"

KeyMap g_keys = {0};

void poll_keys(void)
{
    for (int i = 0; i < 512; i++)
    {
        bool is_down = IsKeyDown(i);
        g_keys.pressed[i] = is_down && !g_keys.down[i];
        g_keys.down[i] = is_down;
    }
}

KeyMap* get_keymap(void)
{
    return &g_keys;
}