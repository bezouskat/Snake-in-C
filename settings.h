#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>
#include "state.h"

typedef struct
{
    int start_length;
    int start_level;
    bool running;
    state current_state;
} Settings;

extern Settings settings;

#endif // SETTINGS_H
