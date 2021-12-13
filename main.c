#include <stdlib.h>
#include <time.h>

#include "settings.h"
#include "state_play.h"
#include "state_menu.h"
#include "state_settings.h"

Settings settings;

int main() {
    set_window_title("My Own Snake Game - Bezouska. T");
    set_window_size(609, 438);
    set_cursor_visible(FALSE);

    settings.start_length = 1;
    settings.start_level = 1;
    settings.running = true;
    settings.current_state = MENU;

    srand(time(NULL));

    while (settings.running)
    {
        switch (settings.current_state)
        {
            case MENU: state_menu(); break;
            case PLAY: state_play(); break;
            case SETTINGS: state_settings(); break;
        }
    }

    return 0;
}
