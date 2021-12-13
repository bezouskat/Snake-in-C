#include "state_settings.h"

void draw_settings_frame()
{
    set_color(RED);

    int i;

    for (i = 0; i <= SCREEN_WIDTH; ++i)
    {
        goto_xy(i, 0);
        putchar(FRAME);

        goto_xy(i, SCREEN_HEIGHT);
        putchar(FRAME);
    }

    for (i = 0; i <= SCREEN_HEIGHT; ++i)
    {
        goto_xy(0, i);
        putchar(FRAME);

        goto_xy(SCREEN_WIDTH, i);
        putchar(FRAME);
    }

    goto_xy(0, 0);
}

void draw_settings_title()
{
    set_color(WHITE);

    goto_xy(3, 2); printf("  __      _   _   _                  ");
    goto_xy(3, 3); printf(" / _\\ ___| |_| |_(_)_ __   __ _ ___  ");
    goto_xy(3, 4); printf(" \\ \\ / _ \\ __| __| | '_ \\ / _` / __| ");
    goto_xy(3, 5); printf(" _\\ \\  __/ |_| |_| | | | | (_| \\__ \\ ");
    goto_xy(3, 6); printf(" \\__/\\___|\\__|\\__|_|_| |_|\\__, |___/ ");
    goto_xy(3, 7); printf("                          |___/      ");
}

void settings_items()
{
    set_color(WHITE);

    goto_xy(30, 11); printf("Movement: <arrows> | <WSAD>");
    goto_xy(30, 13); printf("Pause:    <ESC>");
    goto_xy(30, 15); printf("Start Level:  %c %3d %c", 17, settings.start_level, 16);
    goto_xy(30, 17); printf("Start Length: %c %3d %c", 17, settings.start_length, 16);
}

void state_settings()
{
    int item = 15;

    clear_screen();
    draw_settings_frame();
    draw_settings_title();
    settings_items();

    goto_xy(26, item);
    printf("-->");

    goto_xy(3, 22);
    printf("Press <ESC> to return back to the menu...");

    while (true)
    {
        if (key_hit())
        {
            KeyButton key = get_key();

            if (key == KEY_UP || key == KEY_W)
            {
                if (item == 17)
                {
                    goto_xy(26, item);
                    printf("   ");
                    item -= 2;
                }

                goto_xy(26, item);
                printf("-->");
            }
            else if (key == KEY_DOWN || key == KEY_S)
            {
                if (item == 15)
                {
                    goto_xy(26, item);
                    printf("   ");
                    item += 2;
                }

                goto_xy(26, item);
                printf("-->");
            }
            else if (key == KEY_LEFT || key == KEY_A)
            {
                if (item == 15)
                {
                    if (settings.start_level > 1)
                    {
                        --settings.start_level;
                        goto_xy(30, 15);
                        printf("Start Level:  %c %3d %c", 17, settings.start_level, 16);
                    }
                }
                else if (item == 17)
                {
                    if (settings.start_length > 1)
                    {
                        --settings.start_length;
                        goto_xy(30, 17);
                        printf("Start Length: %c %3d %c", 17, settings.start_length, 16);
                    }
                }
            }
            else if (key == KEY_RIGHT || key == KEY_D)
            {
                if (item == 15)
                {
                    if (settings.start_level < 10)
                    {
                        ++settings.start_level;
                        goto_xy(30, 15);
                        printf("Start Level:  %c %3d %c", 17, settings.start_level, 16);
                    }
                }
                else if (item == 17)
                {
                    if (settings.start_length < 999)
                    {
                        ++settings.start_length;
                        goto_xy(30, 17);
                        printf("Start Length: %c %3d %c", 17, settings.start_length, 16);
                    }
                }
            }
            else if (key == KEY_ESC)
            {
                settings.current_state = MENU;
                return;
            }

            goto_xy(44, 22);
        }
    }
}
